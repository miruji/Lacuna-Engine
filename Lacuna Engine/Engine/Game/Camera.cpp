#include "Camera.h"

LE::Camera::Camera(float x, float y, float w, float h, float speed)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = speed;
}
LE::Camera::Camera()
{
}
LE::Camera::~Camera()
{
}