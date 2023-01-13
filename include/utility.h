#pragma once

#define opengl_debug(position) if(int error = glGetError()) std::cout << position << ": " << error << std::endl

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;
double convert2NDC(double pos, bool isX);