/*
 * Handle of a glfw window
 */
#ifndef ROOM_WINDOW_H
#define ROOM_WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
protected:
    GLFWwindow *window;
public:
    Window(int width, int height, char const *title);
    void makeCurrent();
    int shouldClose();
    GLFWwindow* getHandle();
    void swapBuffers();
};

class MainWindow: public Window {
public:
    MainWindow(int width, int height);
private:
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void static key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

#endif //ROOM_WINDOW_H
