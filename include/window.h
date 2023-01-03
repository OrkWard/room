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
#include "camera.h"
#include "light.h"

class Window;
class MainWindow;
class EntityWindow;

class Window {
protected:
    GLFWwindow *_window;
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
    ~MainWindow();
    void switchEntity();
    void render() override;
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

class EntityWindow: public Window {
private:
    std::unique_ptr<GLSLProgram> _primitiveShader;
    std::unique_ptr<Cube> _cube;
    std::unique_ptr<PerspectiveCamera> _camera;
    AmbientLight _ambient;
    DirectionalLight _light;
public:
    static const int ENWIDTH = 230;
    static const int ENHEIGHT = 200;
public:
    EntityWindow(MainWindow* mainWindow);
    ~EntityWindow();
    void render() override;
private:
    static void window_close_callback(GLFWwindow *window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif //ROOM_WINDOW_H
