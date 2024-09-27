#include "ShaderManager.h"

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > shader manager
LE::ShaderManager::ShaderManager()
{
}
LE::ShaderManager::~ShaderManager()
{
    clear();
}
void LE::ShaderManager::clear()
{
    while (shaders.size() != 0)
        deleteShader(0);
    shaders.clear();

    while (programs.size() != 0)
        deleteProgram(0);
    programs.clear();
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > shader
LE::ShaderManager::Shader::Shader(const std::string filePath, const std::string type)
{
    const char* f = joinStringVector( getFileStrings(filePath) ).c_str();

    if (type == "fragment")
        num = glCreateShader(GL_FRAGMENT_SHADER);
    else
    if (type == "vertex")
        num = glCreateShader(GL_VERTEX_SHADER);

    if (num == 0)
    {
        fprintf(stderr, " Error creating vertex shader.\n");
    }
    glShaderSource(num, 1, &f, NULL);
}
LE::ShaderManager::Shader::~Shader()
{
}
void LE::ShaderManager::Shader::compile()
{
    glCompileShader(num);

    GLint errors;
    GLchar log[2000];

    //
    glGetShaderiv(num, GL_COMPILE_STATUS, &errors);
    if (GL_FALSE == errors)
    {
        glGetShaderInfoLog(num, 2000, NULL, log);
        printf("%s\n", log);
    }
}
size_t LE::ShaderManager::createShader(const std::string FilePath, const std::string Type)
{
    shaders.emplace_back(Shader(FilePath, Type));
    size_t result = shaders.size()-1;
    shaders[result].compile();
    return result;
}
void LE::ShaderManager::attachShader(const mi ShaderNum, const mi ProgramNum)
{
    GLuint& s = shaders[ShaderNum].num;
    GLuint& p = programs[ProgramNum].num;
    glAttachShader(p, s);
    glLinkProgram(p);
}
void LE::ShaderManager::deleteShader(const mi ShaderNum)
{
    glDeleteShader( shaders[ShaderNum].num );
    shaders.erase(shaders.begin()+ShaderNum);
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > shader program
LE::ShaderManager::ShaderProgram::ShaderProgram()
    : num(glCreateProgram())
{
}
LE::ShaderManager::ShaderProgram::~ShaderProgram()
{
}
void LE::ShaderManager::ShaderProgram::use()
{
    GLint errors;
    GLchar log[2000];

    glGetProgramiv(num, GL_LINK_STATUS, &errors);
    if (GL_FALSE == errors)
    {
        glGetProgramInfoLog(num, 2000, NULL, log);
        printf("%s\n", log);
    }

    glUseProgram(num);
}
size_t LE::ShaderManager::createProgram()
{
    programs.emplace_back(ShaderProgram());
    return programs.size()-1;
}
void LE::ShaderManager::useProgram(const mi ProgramNum)
{
    programs[ProgramNum].use();
}
void LE::ShaderManager::deleteProgram(const mi ProgramNum)
{
    glDeleteProgram(programs[ProgramNum].num);
    programs.erase(programs.begin()+ProgramNum);
}