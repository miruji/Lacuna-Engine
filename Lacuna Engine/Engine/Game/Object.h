#pragma once
#include <iostream>
#include <vector>
#include "../Graphics/FloatMacro.h"
#include "../Graphics/Texture.h"
#include "../Graphics/vertex.h"

#include "Camera.h"
#include "../Type/mi.h"

namespace LE
{
	class Object
	{
	private:

	public:
		std::string name;
		std::vector<size_t> textures;
		float x, y, w, h;

		Object(const std::string name, const float x, const float y, const float w, const float h);
		~Object();

		void drawRect(Camera& c, Texture& t, mi tilemap = -1);
	};
}