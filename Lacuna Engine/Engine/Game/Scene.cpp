#include "Scene.h"

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > scene
LE::Scene::Scene(std::string name)
	: name(std::move(name))
{
}
LE::Scene::~Scene()
{
}
void LE::Scene::buildScene(Log& l, std::string& projectDir, Import& projectImport)
{
	glewInit(); // ?

	// gen
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &fboTexture);

	// init objects
    fs::current_path(projectDir);
	std::string scene  = projectImport.getImport(projectImport.scenes, name+".les").path;
    std::string script = projectImport.getImport(projectImport.scenes, name+".lua").path;
	if (scene == "?" || script == "?") // no import
	{ // TO:DO: if no script then continue code ?
		unbuildScene(l);
		return;
	}

		json = getJSON(scene);

		loadLuaFile(script);
		states[0]->func("init");

	//
	l.push("i1", "Scene builded");
}
void LE::Scene::unbuildScene(Log& l)
{
	glDeleteTextures(1, &fboTexture);
	glDeleteFramebuffers(1, &fbo);

	// deinit
	for (size_t i = 0; i < states.size(); i++)
		states[i]->del();
	states.clear();

	for (size_t i = 0; i < textures.size(); i++)
	{
		textures[i].del();
	}
	textures.clear();
	objects.clear();

	c.clear(); //

	shaderManager.clear();

	//
	l.push("i1", "Scene unbuilded");
}
std::vector<LE::Object>& LE::Scene::getObjects()
{
	return objects;
}
LE::mi LE::Scene::searchObject(std::string name)
{
	for_er(i, 0, i < objects.size(), i++, objects[i].name == name, i);
	return -1;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > require
int LE::Scene::le_requireHere(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	std::cout << "!> file require here" << std::endl;

	return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > keyboard (key)
int LE::Scene::le_key_code(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | key name
	luaFuncParam(l, "s");
		
		//
		lua_pushstring(l, std::to_string( getKeyNum(p.get_s(0)) ).c_str());
		return 1;
}
int LE::Scene::le_key_pressed(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | key code
	luaFuncParam(l, "f");
		
		//
		int p2Buffer = p.get_f(0);
		int key = s->k.searchKey(p2Buffer);
		if (key == -1)
		{
			s->k.keys.emplace_back(Keyboard::Key(p2Buffer));
			lua_pushboolean(l, 0);
		}
		else
		if (s->k.keys[key].pressed)
		{
			s->k.keys[key].pressed = false;
			lua_pushboolean(l, 1);
		}
		else
			lua_pushboolean(l, 0);

	return 1;
}
// TO:DO: pressed / released / and ... ?
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > ui
int LE::Scene::le_ui_windowBegin(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | window name
	luaFuncParam(l, "ss");

		//
		ImGui::Begin(p.get_s(0).c_str(), NULL, convertToImGuiFlags(p.get_s(1)));

	return 0;
}
int LE::Scene::le_ui_windowEnd(lua_State* l)
{
		//
		ImGui::End();

	return 0;
}
int LE::Scene::le_ui_setWindowPos(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | window name
	luaFuncParam(l, "ff");

		//
		ImGui::SetWindowPos( ImVec2(p.get_f(0), p.get_f(1)) );

	return 0;
}
int LE::Scene::le_ui_setWindowSize(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | window name
	luaFuncParam(l, "ff");

		ImGui::SetWindowSize( ImVec2(p.get_f(0), p.get_f(1)) );

	return 0;
}
int LE::Scene::le_ui_image(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | window name
	luaFuncParam(l, "fff");

		//
		int t = p.get_f(0);
		if (t > 0)
		{
			size_t w = p.get_f(1);
			if (w > s->c[s->cCurrent].w) w = s->c[s->cCurrent].w;
			size_t h = p.get_f(2);
			if (h > s->c[s->cCurrent].h) h = s->c[s->cCurrent].h;
			ImGui::Image(ImTextureID(t), ImVec2(w, h));
		}

	return 0;
}
int LE::Scene::le_ui_findImage(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | window name
	luaFuncParam(l, "s");

		//
		mi i = searchTexture(s->textures, p.get_s(0)).value;
		if (i > -1)
		{
			size_t w = s->textures[i].w;
			if (w > s->c[s->cCurrent].w) w = s->c[s->cCurrent].w;
			size_t h = s->textures[i].h;
			if (h > s->c[s->cCurrent].h) h = s->c[s->cCurrent].h;
			ImGui::Image(ImTextureID(s->textures[i.value].num), ImVec2(w, h));
		}

	return 0;
}
int LE::Scene::le_ui_text(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | text
	luaFuncParam(l, "s");

		//
		ImGui::Text(p.get_s(0).c_str());

	return 0;
}
int LE::Scene::le_ui_centerText(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | text
	luaFuncParam(l, "sffff");

		//
		ImGuiContext& g = *GImGui;
		ImFont* font = g.Font;
		ImVec2 textSize = font->CalcTextSizeA(g.FontSize, FLT_MAX, 0, p.get_s(0).c_str());

		// centred
		ImVec2 textPos;
		textPos.x = p.get_f(1) + (p.get_f(3) - textSize.x) * 0.5f;
		textPos.y = p.get_f(2) + (p.get_f(4) - textSize.y) * 0.5f;

		//
		ImGui::GetCurrentWindow()->DrawList->AddText(font, g.FontSize, textPos, ImGui::GetColorU32(ImGuiCol_Text), p.get_s(0).c_str());

	return 0;
}
int LE::Scene::le_ui_button(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | text
	luaFuncParam(l, "sff");

		//
		bool result = ImGui::Button(p.get_s(0).c_str(), ImVec2(p.get_f(1), p.get_f(2)));
		if (result)
		{
			lua_pushinteger(l, result);
			return 1;
		}

	return 0;
}
int LE::Scene::le_ui_setCursorPos(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | text
	luaFuncParam(l, "ff");

		//
		ImGui::SetCursorPos(ImVec2(p.get_f(0), p.get_f(1)));

	return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > camera
int LE::Scene::le_camera_new(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | x | y | w | h
	luaFuncParam(l, "ffff");
		
		//
		if (!s->c.size())
			s->cCurrent = 0;
		s->c.emplace_back( Camera(-p.get_f(0), -p.get_f(1), p.get_f(2), p.get_f(3)));
		
	// return cameras vector num
	lua_pushstring(l, std::to_string(s->c.size()-1).c_str());
	return 1;
}
int LE::Scene::le_camera_current(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | num
	luaFuncParam(l, "f");
		
		//
		s->cCurrent = p.get_f(0);

	return 0;
}
int LE::Scene::le_camera_move(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | num | set/move | x | y
	luaFuncParam(l, "fsff");
	std::string p1 = toLowerCase(p.get_s(1));
		
		//
		int cBuffer = p.get_f(0);
		if (p1 == "set")
		{
			s->c[cBuffer].x = -p.get_f(2);
			s->c[cBuffer].y = -p.get_f(3);
		}
		else
		if (p1 == "move")
		{
			s->c[cBuffer].x += -p.get_f(2);
			s->c[cBuffer].y += -p.get_f(3);
		}

	return 0;
}
int LE::Scene::le_camera_size(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | num | x | h
	luaFuncParam(l, "fff");
		
		//
		int cBuffer = p.get_f(0);
		s->c[cBuffer].w = p.get_f(1);
		s->c[cBuffer].h = p.get_f(2);

	return 0;
}
int LE::Scene::le_camera_speed(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | num | speed
	luaFuncParam(l, "ff");
		
		//
		int cBuffer = p.get_f(0);
		s->c[cBuffer].speed = p.get_f(1);

	return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > shader
int LE::Scene::le_shader_new(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | path | type
	luaFuncParam(l, "ss");
		
		//
		size_t sh = s->shaderManager.createShader(p.get_s(0), p.get_s(1));
	
	lua_pushstring(l, std::to_string(sh).c_str());
	return 1;
}
int LE::Scene::le_shader_attach(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | program num | shader num
	luaFuncParam(l, "ff");
		
		//
		s->shaderManager.attachShader( p.get_f(0), p.get_f(1) );

	return 0;
}
int LE::Scene::le_shader_delete(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | shader num
	luaFuncParam(l, "f");
		
		//
		s->shaderManager.deleteShader( p.get_f(0) );

	return 0;
}
int LE::Scene::le_shader_program_new(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));
		
		//
		size_t p = s->shaderManager.createProgram();

	lua_pushstring(l, std::to_string(p).c_str());
	return 1;
}
int LE::Scene::le_shader_program_use(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | program num
	luaFuncParam(l, "f");

		//
		s->shaderManager.useProgram( p.get_f(0) );

	return 0;
}
int LE::Scene::le_shader_program_delete(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | program num
	luaFuncParam(l, "f");

		//
		s->shaderManager.deleteProgram( p.get_f(0) );

	return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > texture
int LE::Scene::le_texture_new(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | texture path | texture color
	luaFuncParam(l, "ss");
		
		//
		s->textures.emplace_back(loadTexture(p.get_s(0), "Texture"));
		s->textures.back().addColor(p.get_s(1));

	lua_pushinteger(l, s->textures.back().num);
	return 1;
}
int LE::Scene::le_texture_rotate(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | texture num | degree
	luaFuncParam(l, "fs");
		
		//
		const mi t = searchTexture(s->textures, p.get_f(0));
		s->textures[t].rotate( p.get_f(1) );

	return 0;
}
int LE::Scene::le_texture_flip(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | texture num | axis
	luaFuncParam(l, "fs");
		
		//
		const mi t = searchTexture(s->textures, p.get_f(0));
		bool mode = 0;
			 if (p.get_s(1) == "h" || p.get_s(1) == "horizontal") mode = 0;
		else if (p.get_s(1) == "v" || p.get_s(1) == "vertical")   mode = 1;
		s->textures[t].flip(mode);

	return 0;
}
int LE::Scene::le_texture_find(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | texture name
	luaFuncParam(l, "s");

	lua_pushinteger(l, getTextureNum(s->textures, p.get_s(0)));
	return 1;
}
int LE::Scene::le_texture_tile_new(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | texture num | tile value | degree
	luaFuncParam(l, "fsf");
		
		//
		const mi t = searchTexture(s->textures, p.get_f(0));
		s->textures[t].tilemap.emplace_back( LE::Texture::Tile(p.get_s(1)) );

		auto& tile = s->textures[t].tilemap.back();
		tile.degree = p.get_f(2);

	lua_pushinteger(l, s->textures[t].tilemap.size()-1);
	return 1;
}
int LE::Scene::le_texture_tile_size(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | texture num
	luaFuncParam(l, "f");
		
		//
		lua_pushinteger(l, s->textures[searchTexture(s->textures, p.get_f(0))].tilemap.size());
		return 1;
}
int LE::Scene::le_texture_tile_rotate(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | texture num | tile num | degree
	luaFuncParam(l, "fff");
		
		//
		s->textures[searchTexture(s->textures, p.get_f(1))].tilemap[p.get_f(1)].degree = p.get_f(2);

	return 0;
}
int LE::Scene::le_texture_tile_flip(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	//
	return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > object
int LE::Scene::le_object_new(lua_State* l)
{
	// Get a pointer to the scene
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | object name | x | y | w | h
	luaFuncParam(l, "sffff");
		
		// Check if an object with the same name already exists
		for_er(i, 0, i < s->objects.size(), ++i, s->objects[i].name == p.get_s(0), 0);

		// Add the new object to the scene
		s->objects.emplace_back(p.get_s(0), p.get_f(1), p.get_f(2), p.get_f(3), p.get_f(4));
	
	return 0;
}
int LE::Scene::le_object_texture_set(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | object name | texture num
	luaFuncParam(l, "sf");
		
		//
		const mi o = s->searchObject( p.get_s(0) );
		if (o) s->objects[o].textures.emplace_back( p.get_f(1) );
		
	return 0;
}
int LE::Scene::le_object_texture_draw(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | object name | texture num
	luaFuncParam(l, "sf");
		
		//
		s->objects[s->searchObject(p.get_s(0))].drawRect(s->c[s->cCurrent], s->textures[ searchTexture(s->textures, p.get_f(1)) ], -1);

	return 0;
}
int LE::Scene::le_object_tile_draw(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | object name | texture num | tile num
	luaFuncParam(l, "sff");
		
		//
		s->objects[s->searchObject(p.get_s(0))].drawRect(s->c[s->cCurrent], s->textures[searchTexture(s->textures, p.get_f(1))], p.get_f(2));

	return 0;
}
int LE::Scene::le_object_move(lua_State* l)
{
    lua_getglobal(l, luaEngineAccessor);
    Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | name | x | y
	luaFuncParam(l, "sff");
		
		// Get object index
		const mi o = s->searchObject(p.get_s(0));
		Object& obj = s->objects[o];

		// Get x and y offsets
		float xOffset = p.get_f(1);
		float yOffset = p.get_f(2);
		
		// Update object position
		obj.x += xOffset;
		obj.y += yOffset;

	//
    return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > random int/float
int LE::Scene::le_random_int(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// table | min num | max num
	luaFuncParam(l, "ff");
		
		//
		lua_pushinteger(l, getRandomInt(p.get_f(0), p.get_f(1)));
		return 1;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > oct <-> hex
int LE::Scene::LE_OctToHex(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	if (lua_gettop(l) != 3) return 0; // error lua func
	std::string p2 = lua_tostring(l, 2); // number

	lua_pushstring(l, octToHex(p2).c_str());
	return 1;
	*/
}
int LE::Scene::LE_HexToOct(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	if (lua_gettop(l) != 3) return 0; // error lua func
	std::string p2 = lua_tostring(l, 2); // number

	lua_pushstring(l, hexToOct(p2).c_str());
	return 1;
	*/
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > color
int LE::Scene::LE_NewRGB(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	if (lua_gettop(l) < 2 || lua_gettop(l) > 3) return 0; // error lua func
	std::string p2 = lua_tostring(l, 2); // color

	// get color
	std::string Color = "";
	std::vector<std::string> CT = colorType(p2);
	if (CT[0] == "RGB" || CT[0] == "RGBA" || 
		CT[0] == "RGB_F" || CT[0] == "RGBA_F" ||
		CT[0] == "HEX")
	{
		std::vector<float> C = convertColor(p2);

		C[0] = fc(C[0]);
		Color.append(std::to_string(C[0])); Color+=",";
		C[1] = fc(C[1]);
		Color.append(std::to_string(C[1])); Color+=",";
		C[2] = fc(C[2]);
		Color.append(std::to_string(C[2]));
	}
	else return 0;

	lua_pushstring(l, Color.c_str());
	return 1;
	*/
}
int LE::Scene::LE_NewRGB_F(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	if (lua_gettop(l) < 2 || lua_gettop(l) > 3) return 0; // error lua func
	std::string p2 = lua_tostring(l, 2); // color

	// get color
	std::string Color = "";
	std::vector<std::string> CT = colorType(p2);
	if (CT[0] == "RGB" || CT[0] == "RGBA" ||
		CT[0] == "RGB_F" || CT[0] == "RGBA_F" || 
		CT[0] == "HEX")
	{
		std::vector<float> C = convertColor(p2);

		Color.append(std::to_string(C[0])); Color+=",";
		Color.append(std::to_string(C[1])); Color+=",";
		Color.append(std::to_string(C[2]));
	}
	else return 0;

	lua_pushstring(l, Color.c_str());
	return 1;
	*/
}
int LE::Scene::LE_NewRGBA(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	if (lua_gettop(l) < 2 || lua_gettop(l) > 4) return 0; // error lua func
	std::string p2 = lua_tostring(l, 2); // color

	// get color
	std::string Color = "";
	std::vector<std::string> CT = colorType(p2);
	if (CT[0] == "RGB" || CT[0] == "RGBA" ||
		CT[0] == "RGB_F" || CT[0] == "RGBA_F" || 
		CT[0] == "HEX")
	{
		std::vector<float> C = convertColor(p2);

		C[0] = fc(C[0]);
		Color.append(std::to_string(C[0])); Color+=",";
		C[1] = fc(C[1]);
		Color.append(std::to_string(C[1])); Color+=",";
		C[2] = fc(C[2]);
		Color.append(std::to_string(C[2]));

		if ((CT[0] == "RGBA" || CT[0] == "RGBA_F" || CT[0] == "HEX") && C.size() == 4)
		{
			C[3] = fc(C[3]);
			Color += ",";
			Color.append(std::to_string(C[3]));
		}
	}
	else return 0;

	lua_pushstring(l, Color.c_str());
	return 1;
	*/
}
int LE::Scene::LE_NewRGBA_F(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	if (lua_gettop(l) < 2 || lua_gettop(l) > 4) return 0; // error lua func
	std::string p2 = lua_tostring(l, 2); // color

	// get color
	std::string Color = "";
	std::vector<std::string> CT = colorType(p2);
	if (CT[0] == "RGB" || CT[0] == "RGBA" ||
		CT[0] == "RGB_F" || CT[0] == "RGBA_F" || 
		CT[0] == "HEX")
	{
		std::vector<float> C = convertColor(p2);

		Color.append(std::to_string(C[0])); Color+=",";
		Color.append(std::to_string(C[1])); Color+=",";
		Color.append(std::to_string(C[2]));

		if ((CT[0] == "RGBA" || CT[0] == "RGBA_F" || CT[0] == "HEX") && C.size() == 4)
		{
			Color += ",";
			Color.append(std::to_string(C[3]));
		}
	}
	else return 0;

	lua_pushstring(l, Color.c_str());
	return 1;
	*/
}
int LE::Scene::LE_NewHEX(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	if (lua_gettop(l) < 2 || lua_gettop(l) > 4) return 0; // error lua func
	std::string p2 = lua_tostring(l, 2); // color

	// get color
	std::string Color = "#";
	std::vector<std::string> CT = colorType(p2);
	if (CT[0] == "RGB" || CT[0] == "RGBA" ||
		CT[0] == "RGB_F" || CT[0] == "RGBA_F")
	{
		std::vector<float> C = convertColor(p2);
		C[0] = fc(C[0]); Color.append(octToHex(std::to_string(C[0])));
		C[1] = fc(C[1]); Color.append(octToHex(std::to_string(C[1])));
		C[2] = fc(C[2]); Color.append(octToHex(std::to_string(C[2])));

		if ((CT[0] == "RGBA" || CT[0] == "RGBA_F") && C.size() == 4)
		{
			C[3] = fc(C[3]);
			Color.append(octToHex(std::to_string(C[3])));
		}
	}
	else return 0;

	lua_pushstring(l, Color.c_str());
	return 1;
	*/
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > random color
int LE::Scene::LE_RandomRGB(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	std::string p2 = "";
	if (lua_gettop(l) >= 3) p2 = lua_tostring(l, 2); // min/max 1
	std::string p3 = "";
	if (lua_gettop(l) >= 4) p3 = lua_tostring(l, 3); // min/max 2
	std::string p4 = "";
	if (lua_gettop(l) >= 5) p4 = lua_tostring(l, 4); // min/max 3

	std::vector<std::string> C1;
	if (p2 != "") C1 = splitString(p2, ':');
	else { C1.push_back("0"); C1.push_back("255"); }
	std::vector<std::string> C2;
	if (p3 != "") C2 = splitString(p3, ':');
	else { C2.push_back("0"); C2.push_back("255"); }
	std::vector<std::string> C3;
	if (p4 != "") C3 = splitString(p4, ':');
	else { C3.push_back("0"); C3.push_back("255"); }

	std::string Color = std::to_string(getRandomInt( atoi(C1[0].c_str()), atoi(C1[1].c_str()) )) + ", " +
						std::to_string(getRandomInt( atoi(C2[0].c_str()), atoi(C2[1].c_str()) )) + ", " +
						std::to_string(getRandomInt( atoi(C3[0].c_str()), atoi(C3[1].c_str()) ));
	lua_pushstring(l, Color.c_str());

	return 1;
	*/
}
int LE::Scene::LE_RandomRGB_F(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	std::string p2 = "";
	if (lua_gettop(l) >= 3) p2 = lua_tostring(l, 2); // min/max 1
	std::string p3 = "";
	if (lua_gettop(l) >= 4) p3 = lua_tostring(l, 3); // min/max 2
	std::string p4 = "";
	if (lua_gettop(l) >= 5) p4 = lua_tostring(l, 4); // min/max 3

	std::vector<std::string> C1;
	if (p2 != "") C1 = splitString(p2, ':');
	else { C1.push_back("0"); C1.push_back("1"); }
	std::vector<std::string> C2;
	if (p3 != "") C2 = splitString(p3, ':');
	else { C2.push_back("0"); C2.push_back("1"); }
	std::vector<std::string> C3;
	if (p4 != "") C3 = splitString(p4, ':');
	else { C3.push_back("0"); C3.push_back("1"); }

	std::string Color = std::to_string(getRandomFloat( atof(C1[0].c_str()), atof(C1[1].c_str()) )) + ", " +
						std::to_string(getRandomFloat( atof(C2[0].c_str()), atof(C2[1].c_str()) )) + ", " +
						std::to_string(getRandomFloat( atof(C3[0].c_str()), atof(C3[1].c_str()) ));
	lua_pushstring(l, Color.c_str());

	return 1;
	*/
}
int LE::Scene::LE_RandomRGBA(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	std::string p2 = "";
	if (lua_gettop(l) >= 3) p2 = lua_tostring(l, 2); // min/max 1
	std::string p3 = "";
	if (lua_gettop(l) >= 4) p3 = lua_tostring(l, 3); // min/max 2
	std::string p4 = "";
	if (lua_gettop(l) >= 5) p4 = lua_tostring(l, 4); // min/max 3
	std::string p5 = "";
	if (lua_gettop(l) >= 6) p5 = lua_tostring(l, 5); // min/max 4

	std::vector<std::string> C1;
	if (p2 != "") C1 = splitString(p2, ':');
	else { C1.push_back("0"); C1.push_back("255"); }
	std::vector<std::string> C2;
	if (p3 != "") C2 = splitString(p3, ':');
	else { C2.push_back("0"); C2.push_back("255"); }
	std::vector<std::string> C3;
	if (p4 != "") C3 = splitString(p4, ':');
	else { C3.push_back("0"); C3.push_back("255"); }
	std::vector<std::string> C4;
	if (p5 != "") C4 = splitString(p5, ':');
	else { C4.push_back("0"); C4.push_back("255"); }

	std::string Color = std::to_string(getRandomInt( atoi(C1[0].c_str()), atoi(C1[1].c_str()) )) + ", " +
						std::to_string(getRandomInt( atoi(C2[0].c_str()), atoi(C2[1].c_str()) )) + ", " +
						std::to_string(getRandomInt( atoi(C3[0].c_str()), atoi(C3[1].c_str()) )) + ", " +
						std::to_string(getRandomInt( atoi(C4[0].c_str()), atoi(C4[1].c_str()) ));
	lua_pushstring(l, Color.c_str());

	return 1;
	*/
}
int LE::Scene::LE_RandomRGBA_F(lua_State* l)
{
	/*
	lua_getglobal(l, luaEngineAccessor);
	Scene* S = static_cast<Scene*>(lua_touserdata(l, -1));

	// p1 = table
	std::string p2 = "";
	if (lua_gettop(l) >= 3) p2 = lua_tostring(l, 2); // min/max 1
	std::string p3 = "";
	if (lua_gettop(l) >= 4) p3 = lua_tostring(l, 3); // min/max 2
	std::string p4 = "";
	if (lua_gettop(l) >= 5) p4 = lua_tostring(l, 4); // min/max 3
	std::string p5 = "";
	if (lua_gettop(l) >= 6) p5 = lua_tostring(l, 5); // min/max 4

	std::vector<std::string> C1;
	if (p2 != "") C1 = splitString(p2, ':');
	else { C1.push_back("0"); C1.push_back("1"); }
	std::vector<std::string> C2;
	if (p3 != "") C2 = splitString(p3, ':');
	else { C2.push_back("0"); C2.push_back("1"); }
	std::vector<std::string> C3;
	if (p4 != "") C3 = splitString(p4, ':');
	else { C3.push_back("0"); C3.push_back("1"); }
	std::vector<std::string> C4;
	if (p5 != "") C4 = splitString(p5, ':');
	else { C4.push_back("0"); C4.push_back("1"); }

	std::string Color = std::to_string(getRandomFloat( atof(C1[0].c_str()), atof(C1[1].c_str()) )) + ", " +
						std::to_string(getRandomFloat( atof(C2[0].c_str()), atof(C2[1].c_str()) )) + ", " +
						std::to_string(getRandomFloat( atof(C3[0].c_str()), atof(C3[1].c_str()) )) + ", " +
						std::to_string(getRandomFloat( atof(C4[0].c_str()), atof(C4[1].c_str()) ));
	lua_pushstring(l, Color.c_str());

	return 1;
	*/
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > sleep / pause
int LE::Scene::le_sleep(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	int p2 = 0.0f;
	if (lua_gettop(l) >= 3) p2 = atoi(lua_tostring(l, 2)); // time ms
	else return 0; // error lua func

	//std::this_thread::sleep_for(std::chrono::seconds(1));

	// TO:DO: return result ?
	//lua_pushboolean(l, true);
	return 0;
}
// > PAUSE
int LE::Scene::le_pause(lua_State* l)
{
	lua_getglobal(l, luaEngineAccessor);
	Scene* s = static_cast<Scene*>(lua_touserdata(l, -1));

	if (lua_gettop(l) <= 0) return 0; // error lua func
	if (lua_gettop(l) >= 2 && lua_isstring(l, 2)) {
		std::cout << lua_tostring(l, 2);
	}

	std::cin.get();

	return 0;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > scene / json
void LE::Scene::le_scene_getName(lua_State* l, std::string globalName, std::string variableName)
{
	std::vector<std::string> globalNameParts = luaParts(globalName);
	lua_getglobal(l, globalNameParts[0].c_str());

	for (auto part = std::next(globalNameParts.begin()); part != globalNameParts.end(); ++part)
		lua_getfield(l, -1, part->c_str());

	//
	lua_pushstring(l, json.getName(variableName).c_str());

	lua_setfield(l, -2, variableName.c_str());
	lua_pop(l, static_cast<int>(globalNameParts.size()));
}
void ConvertJsonToLuaTable(lua_State* l, cJSON* json) {
	if (json->type == cJSON_Array) {
		// Convert JSON array to Lua table
		lua_newtable(l);

		int index = 1;
		cJSON* item = json->child;
		while (item != NULL) {
			// Convert each item in the JSON array
			if (item->type == cJSON_Array || item->type == cJSON_Object) {
				ConvertJsonToLuaTable(l, item);
			}
			else {
				if (item->type == cJSON_String) {
					lua_pushstring(l, item->valuestring);
				}
				else {
					const char* value = cJSON_Print(item);
					lua_pushstring(l, value);
					cJSON_free((void*)value);
				}
			}

			lua_rawseti(l, -2, index);

			item = item->next;
			index++;
		}
	}
	else if (json->type == cJSON_Object) {
		// Convert JSON object to Lua table
		lua_newtable(l);

		cJSON* field = json->child;
		while (field != NULL) {
			const char* fieldName = field->string;

			if (field->type == cJSON_Array || field->type == cJSON_Object) {
				ConvertJsonToLuaTable(l, field);
			}
			else {
				const char* value = cJSON_Print(field);
				lua_pushstring(l, value);
				cJSON_free((void*)value);
			}

			lua_setfield(l, -2, fieldName);

			field = field->next;
		}
	}
}
void LE::Scene::le_scene_getArray(lua_State* l, std::string globalName, std::string arrayName)
{
	std::vector<std::string> globalNameParts = luaParts(globalName);
	lua_getglobal(l, globalNameParts[0].c_str());

	for (auto part = std::next(globalNameParts.begin()); part != globalNameParts.end(); ++part)
		lua_getfield(l, -1, part->c_str());

	// Create a new Lua table to store the result
	lua_newtable(l);
	std::vector<cJSON*> result = json.getArray(arrayName);

	for (size_t i = 0; i < result.size(); ++i) {
		cJSON* item = result[i];

		// Create a new Lua table for the current item
		lua_newtable(l);

		// Iterate over the fields in the JSON object
		cJSON* field = item->child;
		while (field != NULL) {
			// Convert the field name to a string
			const char* fieldName = field->string;

			// Push the field name onto the Lua stack
			lua_pushstring(l, fieldName);

			// Push the field value onto the Lua stack
			if (field->type == cJSON_Array || field->type == cJSON_Object) {
				// If the field value is an array or an object, recursively convert it to a Lua table
				ConvertJsonToLuaTable(l, field);
				lua_settable(l, -3); // Set the key-value pair in the Lua table
			}
			else {
				// Otherwise, convert the field value to a string
				if (field->type == cJSON_String) {
					lua_pushstring(l, field->valuestring);
				}
				else {
					const char* fieldValue = cJSON_Print(field);
					lua_pushstring(l, fieldValue);
					cJSON_free((void*)fieldValue);
				}
				lua_settable(l, -3); // Set the key-value pair in the Lua table
			}

			// Move to the next field
			field = field->next;
		}

		// Set the item in the main Lua table
		lua_rawseti(l, -2, i + 1);
	}

	lua_setfield(l, -2, arrayName.c_str());
	lua_pop(l, static_cast<int>(globalNameParts.size()));
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > c++ to lua func
void LE::Scene::registerEngineMethods(lua_State* l)
{
	// --
	std::cout << "registerEngineMethods =======\n";
	std::cout << "scene debug lua stack: " << lua_gettop(l) << "\n";

	luaTable(l, "le");
		luaFunction(l, "le", "requireHere", le_requireHere);

		//
		luaTable(l, "le", "key");
			luaFunction(l, "le.key", "code",    le_key_code);
			luaFunction(l, "le.key", "pressed", le_key_pressed);

		//
		luaTable(l, "le", "ui");
			luaFunction(l, "le.ui", "windowBegin", le_ui_windowBegin);
			luaFunction(l, "le.ui", "windowEnd",   le_ui_windowEnd);
			luaFunction(l, "le.ui", "setWindowPos", le_ui_setWindowPos);
			luaFunction(l, "le.ui", "setWindowSize", le_ui_setWindowSize);
			luaFunction(l, "le.ui", "image", le_ui_image);
			luaFunction(l, "le.ui", "findImage", le_ui_findImage);
			luaFunction(l, "le.ui", "text", le_ui_text);
			luaFunction(l, "le.ui", "centerText", le_ui_centerText);
			luaFunction(l, "le.ui", "button", le_ui_button);
			luaFunction(l, "le.ui", "setCursorPos", le_ui_setCursorPos);

		//
		luaTable(l, "le", "camera");
			luaFunction(l, "le.camera", "new",     le_camera_new);
			luaFunction(l, "le.camera", "current", le_camera_current);
			luaFunction(l, "le.camera", "move",    le_camera_move);
			luaFunction(l, "le.camera", "size",    le_camera_size);
			luaFunction(l, "le.camera", "speed",   le_camera_speed);

		//
		luaTable(l, "le", "shader");
			luaFunction(l, "le.shader", "new",    le_shader_new);
			luaFunction(l, "le.shader", "attach", le_shader_attach);
			luaFunction(l, "le.shader", "delete", le_shader_delete);

			luaTable(l, "le.shader", "program");
				luaFunction(l, "le.shader.program", "new",    le_shader_program_new);
				luaFunction(l, "le.shader.program", "use",    le_shader_program_use);
				luaFunction(l, "le.shader.program", "delete", le_shader_program_delete);

		//
		luaTable(l, "le", "texture");
			luaFunction(l, "le.texture", "new",    le_texture_new);
			luaFunction(l, "le.texture", "rotate", le_texture_rotate);
			luaFunction(l, "le.texture", "flip",   le_texture_flip);
			luaFunction(l, "le.texture", "find", le_texture_find);

			luaTable(l, "le.texture", "tile");
				luaFunction(l, "le.texture.tile", "new",    le_texture_tile_new);
				luaFunction(l, "le.texture.tile", "size",   le_texture_tile_size);
				luaFunction(l, "le.texture.tile", "rotate", le_texture_tile_rotate);
				luaFunction(l, "le.texture.tile", "flip",   le_texture_tile_flip);

		//
		luaTable(l, "le", "object");
			luaFunction(l, "le.object", "new",  le_object_new);
			luaFunction(l, "le.object", "move", le_object_move);

			luaTable(l, "le.object", "texture");
				luaFunction(l, "le.object.texture", "set",  le_object_texture_set);
				luaFunction(l, "le.object.texture", "draw", le_object_texture_draw);

			luaTable(l, "le.object", "tile");
			luaFunction(l, "le.object.tile", "draw", le_object_tile_draw);

		//
		luaTable(l, "le", "random");
			luaFunction(l, "le.random", "int", le_random_int);
			//LUA_Function(l, "le.random", "float", le_random_float);
		
		//luaFunction(l, "le", "OctToHex", LE_OctToHex);
		//luaFunction(l, "le", "HexToOct", LE_HexToOct);

		//luaFunction(l, "le", "NewRGB",    LE_NewRGB);
		//luaFunction(l, "le", "NewRGB_F",  LE_NewRGB_F);
		//luaFunction(l, "le", "NewRGBA",   LE_NewRGBA);
		//luaFunction(l, "le", "NewRGBA_F", LE_NewRGBA_F);
		//luaFunction(l, "le", "NewHEX",    LE_NewHEX);

		//luaFunction(l, "le", "RandomRGB",    LE_RandomRGB);
		//luaFunction(l, "le", "RandomRGB_F",  LE_RandomRGB_F);
		//luaFunction(l, "le", "RandomRGBA",   LE_RandomRGBA);
		//luaFunction(l, "le", "RandomRGBA_F", LE_RandomRGBA_F);

		luaFunction(l, "le", "sleep", le_sleep);
		luaFunction(l, "le", "pause", le_pause);

		luaTable(l, "le", "scene");
			le_scene_getName(l, "le.scene", "name");
			le_scene_getArray(l, "le.scene", "objects");

	std::cout << "scene debug lua stack: "<< lua_gettop(l) << "\n";
	std::cout << "=============================\n";
	// --
}
void LE::Scene::loadLuaFile(std::string scenePath)
{
	// TO::DO: Clear back ?
	states.emplace_back(new State());

	lua_pushlightuserdata(states[0]->getLuaState(), this);
    lua_setglobal(states[0]->getLuaState(), luaEngineAccessor);

    registerEngineMethods(states[0]->getLuaState());

	states[0]->loadFile(scenePath.c_str());

	// --
	std::cout << scenePath << std::endl;
}