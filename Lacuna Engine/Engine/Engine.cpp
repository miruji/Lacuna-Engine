#include "Engine.h"

LE::Engine::Engine()
{
	l.push("ls", "[Engine started]"); 

    //
	engine_dir          = getRootPath();
	engine_projectsDir  = engine_dir+"\\projects\\";
	engine_dataDir      = engine_dir+"\\data\\";
    engine_templatesDir = engine_dataDir+"templates\\";
}
LE::Engine::~Engine()
{
    stop();
}
void LE::Engine::save()
{
    engine_started = false;
    l.saveFile();
}
void LE::Engine::start(char start_engineMode, std::string start_projectPath, std::string start_resolutionMode, size_t start_w, size_t start_height)
{
    if (start_engineMode == 'E')
        this->engine_mode = 0;
    else
    if (start_engineMode == 'G')
        this->engine_mode = 1;

    this->start_projectPath = start_projectPath;
    this->start_resolutionMode = start_resolutionMode;
    this->start_w = start_w;
    this->start_h = start_h;

    pushInitState("data\\core\\init.lua", engine_states); // engine lua init
    useEngineScript(0);

    if (!engine_states.empty()) engine_started = true;
    if (engine_started)
    {
        //
        if (this->engine_mode == 0)
        {
            l.push("c", "");

            engine_editor->createRender(true, true);
            engine_editor->loadGUIIcons();
            engine_editor->rendering();

            if (!engine_editor->started)
            {
                engine_editor->mergeLog(l);
                engine_editor->mergeScriptOutput(so);

                engine_editor->closeRender();
            }
            
            //std::thread Thread(&Engine::EditorThread, this);
            //Thread.detach();
            // --
        }
        else
        if (this->engine_mode == 1)
        {
            l.push("c", "");

            engine_game->createRender(false, false);
            engine_game->rendering();

            if (!engine_game->started)
            {
                engine_game->mergeLog(l);
                engine_game->mergeScriptOutput(so);

                engine_game->closeRender();
            }

            //std::thread Thread(&Engine::EditorThread, this);
            //Thread.detach();
            // --
        }
    }
    //
    stop();
}
void LE::Engine::stop()
{
    if (engine_started)
    {
        engine_started = false;

        if (engine_mode == 0)
        {
            if (engine_editor->started)
                engine_editor->closeRender();
        }
        else 
        if (engine_mode == 1)
        {
            if (engine_game->started)
                engine_game->closeRender();
        }

        glfwTerminate();
    }
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// push state to back in vector
void LE::Engine::pushInitState(const char* fileName, std::vector<State*>& states)
{
	states.emplace_back(new State());
    lua_State* ls = states[states.size()-1]->getLuaState();

	lua_pushlightuserdata(ls, this);
    lua_setglobal(ls, luaEngineAccessor);
    registerEngineMethods(ls);

	if ( states[states.size()-1]->loadFile(fileName) == 0 )
    {
        std::string initStrMode;
        if (engine_mode == 0)
            initStrMode = "le:editor("+start_resolutionMode+", "+std::to_string(start_w)+", "+std::to_string(start_h)+")";
        else
        if (engine_mode == 1)
        {
            initStrMode = "le:game(\""+start_projectPath+"\", "+start_resolutionMode+", "+std::to_string(start_w)+", "+std::to_string(start_h)+")";

            std::vector<std::string> initStrModeVector = splitString(initStrMode, '\\');
            initStrMode = "";
            for (size_t i = 0; i < initStrModeVector.size(); i++)
            {
                if (i+1 != initStrModeVector.size())
                    initStrMode += initStrModeVector[i]+"\\\\";
                else
                    initStrMode += initStrModeVector[i];
            }
        }

        std::string initStr = getFileReplaceAll(engine_dataDir+"core\\init.lua", "le:start()", initStrMode);
        if ( luaL_dostring(ls, initStr.c_str()) == 0 ) // if ok start
        {
        }
        //
    }
}
// open engine init file
void LE::Engine::useEngineScript(size_t stateID)
{
    engine_version = engine_states[stateID]->str("engine_version");

    engine_states[stateID]->func("init");
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int LE::Engine::nearestWidth(size_t value)
{
    std::vector<int> width = {4096, 3840, 3440, 2560, 2048, 1920, 1680, 1440, 1400, 1366, 1280, 1152, 1024, 854, 800, 768, 640, 480, 384, 352, 320};
    size_t nearest = NULL, nearestI = NULL;
    for (size_t i = 0; i < width.size(); i++)
    {
        int iValue = width[i] - value;
        iValue = abs(iValue);

        if (nearest > iValue || nearest == NULL)
        {
            nearest = iValue;
            nearestI = i;
        }
        if (width[nearestI] == value)
            break;
    }
    return width[nearestI];
}
int LE::Engine::nearestHeight(size_t value)
{
    std::vector<int> height = {2160, 2048, 1600, 1546, 1440, 1200, 1080, 1050, 1024, 960, 900, 864, 854, 800, 768, 720, 600, 576, 480, 320, 288, 240, 200};
    size_t nearest = NULL, nearestI = NULL;
    for (size_t i = 0; i < height.size(); i++)
    {
        int iValue = height[i] - value;
        iValue = abs(iValue);

        if (nearest > iValue || nearest == NULL)
        {
            nearest = iValue;
            nearestI = i;
        }
        if (height[nearestI] == value)
            break;
    }
    return height[nearestI];
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int LE::Engine::le_log(lua_State* l)
{
    lua_getglobal(l, luaEngineAccessor);
    Engine* e = static_cast<Engine*>(lua_touserdata(l, -1));

    // p1 = table
    std::string p2 = lua_tostring(l, 2); // log type
    std::string p3 = lua_tostring(l, 3); // text

    if (p2 != "") e->l.push(p2, p3);

    return 0;
}
std::vector<size_t> LE::Engine::resizeStartResolution(bool mode, size_t w, size_t h)
{
    // --
    if (w < 320 || h < 200) // min resolution for all mode
        { w = 320; h = 200; }

    if (!mode) // no free resolution mode
    {
        // --
        w = nearestWidth(w);
        h = nearestHeight(h);

        std::vector<std::string> nearestResolution;
        int nearestHeight1 = NULL, nearestHeight2 = NULL;
        size_t nearestHeightI = NULL;

        for (size_t i = 0; i < engine_windowResolutions.size(); i++)
        {
            nearestResolution = splitString(engine_windowResolutions[i], 'x');
            // nearest height
            if (w == atoi(nearestResolution[0].c_str()) )
            {
                nearestHeight2 = abs(atof(nearestResolution[1].c_str()) - h);
                if (nearestHeight1 > nearestHeight2 || nearestHeight1 == NULL)
                {
                    nearestHeight1 = nearestHeight2;
                    nearestHeightI = i;
                }
                if ( h == atoi( splitString(engine_windowResolutions[nearestHeightI], 'x')[1].c_str() ) )
                    break;
                // --
            }
            //
        }
        if (nearestHeightI != NULL)
            h = atoi( splitString(engine_windowResolutions[nearestHeightI], 'x')[1].c_str() );
        // --
    }

    return {w, h};
}
int LE::Engine::le_editor(lua_State* l)
{
    lua_getglobal(l, luaEngineAccessor);
    Engine* e = static_cast<Engine*>(lua_touserdata(l, -1));

    // p1 = table
    bool p2   = lua_toboolean(l, 2); // mode
    size_t p3 = lua_tointeger(l, 3); // w
    size_t p4 = lua_tointeger(l, 4); // h
    // TO:DO: if no p2/p3/p4 and more ..

    // --
    std::vector<size_t> resolution = e->resizeStartResolution(p2, p3, p4);
    p3 = resolution[0];
    p4 = resolution[1];

    // create render window
    std::vector<std::string> engine_data = { 
        e->engine_version,
        e->engine_dir,
        e->engine_projectsDir,
        e->engine_dataDir,
        e->engine_templatesDir
    };
    e->engine_editor = new LE::Editor("Lacuna Engine", p3, p4, engine_data); // engine editor
    e->l.push("i1", "Created editor: [Lacuna Engine], Width: ["+std::to_string(p3)+"], Height: ["+std::to_string(p4)+"]");

    // --
    return 0;
}
int LE::Engine::le_game(lua_State* l)
{
    lua_getglobal(l, luaEngineAccessor);
    Engine* e = static_cast<Engine*>(lua_touserdata(l, -1));

    // p1 = table
    std::string p2 = lua_tostring(l, 2);  // game path
    bool p3        = lua_toboolean(l, 3); // mode
    size_t p4      = lua_tointeger(l, 4); // w
    size_t p5      = lua_tointeger(l, 5); // h
    // TO:DO: if no p2/p3/p4/p5 and more ..

    // --
    std::vector<size_t> resolution = e->resizeStartResolution(p3, p4, p5);
    p4 = resolution[0];
    p5 = resolution[1];

    // create render window
    std::vector<std::string> engine_data = { 
        e->engine_version,
        e->engine_dir,
        e->engine_projectsDir,
        e->engine_dataDir
    };
    e->engine_game = new LE::Game("~", p4, p5, p2, engine_data); // engine editor
    e->l.push("i1", "Created game: Width: ["+std::to_string(p4)+"], Height: ["+std::to_string(p5)+"]"+", Path: ["+p2+"]");

    // --
    return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// reqiaster c++ func
void LE::Engine::registerEngineMethods(lua_State* l)
{
    luaTable(l, "le");
        
        luaFunction(l, "le", "log", le_log);
        luaFunction(l, "le", "editor", le_editor);
        luaFunction(l, "le", "game", le_game);
}