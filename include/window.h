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
#include "framebuffer.h"
#include "texture2d.h"

class Window;
class MainWindow;
class EntityWindow;

class Window {
protected:
    GLFWwindow *_window;
    double _deltaTime = 0;
    double _lastFrame = 0;
    std::unique_ptr<GLSLProgram> _normalShader;
public:
    Window(int width, int height, char const *title);
    void makeCurrent();
    int shouldClose();
    virtual void render() = 0;
protected:
    void initNormalShader();
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
public:
    static const int EN_WIDTH;
    static const int EN_HEIGHT;
private:
    std::unique_ptr<GLSLProgram> _primitiveShader;
    std::unique_ptr<Cube> _cube;
    std::unique_ptr<Sphere> _sphere;
    std::unique_ptr<GLSLProgram> _cubeShader;
    std::unique_ptr<Cube> _lightCube;
    std::unique_ptr<PerspectiveCamera> _camera;
    AmbientLight _ambient;
    PointLight _light;

    std::unique_ptr<Framebuffer> _framebuffer;
    std::unique_ptr<Texture2D> _colorTexture;
    std::unique_ptr<Texture2D> _depthTexture;
    std::unique_ptr<GLSLProgram> _quadShader;
    std::unique_ptr<Quad> _quad[6];
public:
    explicit EntityWindow(MainWindow* mainWindow);
    ~EntityWindow();
    void render() override;
private:
    static void window_close_callback(GLFWwindow *window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    // draw point light cube (for debug)
    void drawLightCube();
    void drawEntity(const Entity& entity, int index);
};

#endif //ROOM_WINDOW_H
