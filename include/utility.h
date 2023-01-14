#pragma once
#include <glfw/glfw3.h>

#define opengl_debug(position) if(int error = glGetError()) std::cout << position << ": " << error << std::endl

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;
const float TRANSLATE_SPEED = 0.03f;
const float SCROLL_SPEED = 0.5f;