#pragma once
#include <iostream>
#include <vector>

#include <variant>

#include "../Type/LuaParam.h"

//
#include "../Func/toLowerCase.h"
#include "../Func/toUpperCase.h"

//
#include <GL/glew.h> // glewInit()
#define  GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "../Func/getRandomNumber.h"

#include "../Engine/Import.h"
#include <filesystem>
namespace fs = std::filesystem;

#include "../Console/Log.h"
#include "../Lua/LuaLoad.h"

#include "Keyboard.h"
#include "Camera.h"
#include "Object.h"

#include "../Graphics/ShaderManager.h"

#include "../Graphics/convertToImGuiFlags.h"

namespace LE
{
	class Scene
	{
	private:
		std::vector<Object> objects;
		std::vector<Texture> textures;

	public:
		std::string name;

		GLuint fbo;
		GLuint fboTexture;

		void buildScene  (Log& l, std::string& projectDir, Import& projectImport);
		void unbuildScene(Log& l);

		std::vector<Object>& getObjects();
		mi searchObject(std::string name);

		Scene(std::string name);
		~Scene();

		// TO:DO: to private ?
		static int le_requireHere(lua_State* l);

		static int le_key_code   (lua_State* l);
		static int le_key_pressed(lua_State* l);
		Keyboard k;

		static int le_ui_windowBegin  (lua_State* l);
		static int le_ui_windowEnd    (lua_State* l);
		static int le_ui_setWindowPos (lua_State* l);
		static int le_ui_setWindowSize(lua_State* l);
		static int le_ui_image        (lua_State* l);
		static int le_ui_findImage    (lua_State* l);
		static int le_ui_text         (lua_State* l);
		static int le_ui_centerText   (lua_State* l);
		static int le_ui_button       (lua_State* l);
		static int le_ui_setCursorPos (lua_State* l);

		static int le_camera_new    (lua_State* l);
		static int le_camera_current(lua_State* l);
		static int le_camera_size   (lua_State* l);
		static int le_camera_move   (lua_State* l);
		static int le_camera_speed  (lua_State* l);
		std::vector<Camera> c;
		mi cCurrent = -1; // -1 = undefined

		static int le_shader_new   (lua_State* l);
		static int le_shader_attach(lua_State* l);
		static int le_shader_delete(lua_State* l);
		static int le_shader_program_new   (lua_State* l);
		static int le_shader_program_use   (lua_State* l);
		static int le_shader_program_delete(lua_State* l);

		static int le_texture_new   (lua_State* l);
		static int le_texture_rotate(lua_State* l);
		static int le_texture_flip  (lua_State* l);
		static int le_texture_find  (lua_State* l);
		static int le_texture_tile_new   (lua_State* l);
		static int le_texture_tile_size  (lua_State* l);
		static int le_texture_tile_rotate(lua_State* l);
		static int le_texture_tile_flip  (lua_State* l);

		static int le_object_new         (lua_State* l);
		static int le_object_texture_set (lua_State* l);
		static int le_object_texture_draw(lua_State* l);
		static int le_object_tile_draw   (lua_State* l);
		static int le_object_move        (lua_State* l);

		static int le_random_int(lua_State* l);
		//static int le_random_float(lua_State* l); // TO:DO: Float random bag

		static int LE_OctToHex(lua_State* l);
		static int LE_HexToOct(lua_State* l);

		static int LE_NewRGB   (lua_State* l);
		static int LE_NewRGB_F (lua_State* l);
		static int LE_NewRGBA  (lua_State* l);
		static int LE_NewRGBA_F(lua_State* l);
		static int LE_NewHEX   (lua_State* l);

		static int LE_RandomRGB   (lua_State* l);
		static int LE_RandomRGBA  (lua_State* l);
		static int LE_RandomRGB_F (lua_State* l);
		static int LE_RandomRGBA_F(lua_State* l);

		static int le_sleep(lua_State* l);
		static int le_pause(lua_State* l);

		ShaderManager shaderManager;

		jsonFile json;
		void le_scene_getName(lua_State* l, std::string globalName, std::string variableName);
		void le_scene_getArray(lua_State* l, std::string globalName, std::string arrayName);

		std::vector<State*> states;
		void registerEngineMethods(lua_State* l);
		void loadLuaFile(std::string scenePath);
	};
}