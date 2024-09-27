#pragma once

#define cf(c) (float)c/255.0f // color to float
#define fc(c) 255.0f*(float)c // float to color
#define rgba_to_float(r,g,b,a) cf(r), cf(g), cf(b), cf(a)
#define float_TO_rgba(r,g,b,a) fc(r), fc(g), fc(b), fc(a)

#define xy_to_float(x, y, w, h) ((float)x)/w, ((float)y)/h