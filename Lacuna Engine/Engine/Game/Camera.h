#pragma once
#include <iostream>
#include <vector>

namespace LE
{
	class Camera
	{
	private:

	public:
		float x = 0.0f, y = 0.0f, w = 800.0f, h = 600.0f, speed = 1;

		Camera(float x, float y, float w = 800.0f, float h = 600.0f, float speed = 1);
		Camera();
		~Camera();
	};
}