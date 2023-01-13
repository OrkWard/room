/*
 * Handle of a glfw window
 */
#ifndef ROOM_WINDOW_H
#define ROOM_WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <memory>

#include "entity.h"
#include "glsl_program.h"
#include "camera.h"
#include "light.h"
#include "framebuffer.h"
#include "texture2d.h"
#include "utility.h"

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
public:
    MainWindow(int width, int height);
    ~MainWindow();
    void switchEntity();
    void chooseEntity(double xPos, double yPos);
    void addEntity();
    void render() override;
    void setCamera(int width, int height);
private:
    std::unique_ptr<EntityWindow> _entityWindow;
    std::vector<Entity*> _entites;
    std::unique_ptr<GLSLProgram> _primitiveShader;
    std::unique_ptr<PerspectiveCamera> _camera;
    AmbientLight _ambient;
    PointLight _light;
    int _chosenEntity;
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
    std::unique_ptr<GLSLProgram> _simpleShader;
    std::unique_ptr<Cube> _lightCube;
    std::unique_ptr<PerspectiveCamera> _camera;
    AmbientLight _ambient;
    PointLight _light;

    // entities
    std::unique_ptr<Cube> _cube;
    std::unique_ptr<Sphere> _sphere;
    std::unique_ptr<Frustum> _prism;
    std::unique_ptr<Frustum> _pyramid;

    // framebuffer
    std::unique_ptr<Framebuffer> _framebuffer;
    std::unique_ptr<Texture2D> _colorTexture;
    std::unique_ptr<Texture2D> _depthTexture;
    std::unique_ptr<GLSLProgram> _quadShader;
    std::unique_ptr<Quad> _quad[4];
    int chosenEntity;
public:
    explicit EntityWindow(MainWindow* mainWindow);
    ~EntityWindow();
    void render() override;
    int chooseEntity(double xPos, double yPos);
private:
    static void window_close_callback(GLFWwindow *window);
    static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    // draw point light cube (for debug)
    void drawLightCube();
    void drawEntity(const Entity& entity, int index);
};

#endif //ROOM_WINDOW_H
