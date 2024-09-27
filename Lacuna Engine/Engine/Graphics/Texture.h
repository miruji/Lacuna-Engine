#pragma once
#include <iostream>
#include <vector>
#include <string>

// --
#include <GL/glew.h> // glewInit()
#define  GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_internal.h>

#include "FreeImage/FreeImage.h"

#include "../File/getFileName.h"
#include "../File/noFileType.h"

#include "../Graphics/ConvertColor.h"

#include "../Type/mi.h"

// GUIIcon
namespace LE
{
	struct Texture
	{
		std::string name;
		int w, h;
		GLuint num, pitch;

		std::vector<float> color;
		void addColor(std::string color)
		{
			if (color != "")
				this->color = convertColor(color);
		}

		GLubyte* getPixels()
		{
			// load image in buffer
			glBindTexture(GL_TEXTURE_2D, num);
			GLubyte* pixels = new GLubyte[w*h*4];
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			return pixels;
		}

		//
		struct Tile
		{
			float x, y, w, h;
			int degree = 0, axis = -1;

			Tile(std::string values);
			Tile();
			~Tile();
		};
		std::vector<Tile> tilemap;

		//
		Texture(std::string name, int w, int h, GLuint pitch, GLuint num);
		Texture();
		~Texture();

		void rotate(int degree);
		void flip(bool axis);

		void del();
	};

	std::vector<std::string> loadTextures(std::vector<Texture>& texture, const std::vector<std::string>& loadNames, const std::string& loadMode);
	Texture loadTexture(std::string loadName, std::string loadMode);
	LE::mi searchTexture(const std::vector<Texture>& textures, const std::string& name);
	LE::mi searchTexture(const std::vector<Texture>& textures, const mi& num);
	LE::mi getTextureNum(const std::vector<Texture>& textures, const std::string& name);
	LE::mi getTextureNum(const std::vector<Texture>& textures, const mi& num);
}