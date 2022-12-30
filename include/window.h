/*
 * Handle of a glfw window
 */
#ifndef ROOM_WINDOW_H
#define ROOM_WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "entity.h"
#include "glsl_program.h"

class Window;
class MainWindow;
class EntityWindow;

class Window {
protected:
    GLFWwindow *window;
public:
    Window(int width, int height, char const *title);
    void makeCurrent();
    int shouldClose();
    GLFWwindow* getHandle();
    virtual void render() = 0;
};

class MainWindow: public Window {
private:
    std::unique_ptr<EntityWindow> entityWindow;
public:
    MainWindow(int width, int height);
    void switchEntity();
    void render() override;
private:
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void static key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

class EntityWindow: public Window {
private:
    std::unique_ptr<GLSLProgram> triShader;
    std::unique_ptr<CreateEntity> createEntity;
public:
    static const int ENWIDTH = 230;
    static const int ENHEIGHT = 200;
public:
    EntityWindow();
    void render() override;
};

#endif //ROOM_WINDOW_H
