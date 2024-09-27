#pragma once
#include <GL/glew.h> // glewInit()

#include <iostream>
#include <vector>

#include "../File/GetFileStrings.h"
#include "../Func/JoinStringVector.h"

#include "../Type/mi.h"

namespace LE
{
	struct ShaderManager
	{
		ShaderManager();
		~ShaderManager();
		void clear();

		struct Shader
		{
			GLuint num;
			Shader(const std::string filePath, const std::string type);
			~Shader();

			void compile();
		};
		std::vector<Shader> shaders;
		size_t createShader(const std::string filePath, const std::string type);
		void attachShader(const mi shaderNum, const mi programNum);
		void deleteShader(const mi shaderNum);

		struct ShaderProgram
		{
			GLuint num;
			ShaderProgram();
			~ShaderProgram();

			void use();
		};
		std::vector<ShaderProgram> programs;
		size_t createProgram();
		void useProgram(const mi programNum);
		void deleteProgram(const mi programNum);
	};
}