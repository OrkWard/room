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
#include <imguiFileDialog/ImGuiFileDialog.h>
#include <stb/stb_image_write.h>
#include <iostream>
#include <memory>

#include "model.h"
#include "glsl_program.h"
#include "camera.h"
#include "light.h"
#include "framebuffer.h"
#include "texture2d.h"
#include "utility.h"

class Window;
class MainWindow;
class EntityWindow;

enum CameraMove {
    cameraStay = 0,
    cameraScale = 1,
    cameraRotate = 2,
    cameraTranslate = 3
};

enum EntityMove {
    entityStay = 0,
    entityScale = 1,
    entityRotate = 2,
    entityTranslate = 3
};

enum FocusAxis_ {
    focusX = 1 << 0,
    focusY = 1 << 1,
    focusZ = 1 << 2
};

using FocusAxis = int;
using std::cout;
using std::endl;

class Window {
protected:
    GLFWwindow *_window;
    double _deltaTime = 0;
    double _lastFrame = 0;

    float _xPos, _yPos;

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
    CameraMove cameraMove = cameraStay;
    EntityMove entityMove = entityStay;
    FocusAxis focusAxis = 0;
public:
    MainWindow(int width, int height);
    ~MainWindow();
    // swtich entity window
    void switchEntity();

    void chooseEntity(double xPos, double yPos);
    void addEntity(const char *path);
    void render() override;
    void setCursorPosition(double xPos, double yPos);
    void orbit();
    void printScreen();

    // mouse viewport change event
    void setCameraResize(int width, int height);
    void setCameraMouse(double xPos, double yPos);
    void setCameraScroll(double offset);

    // mouse entity edit event
    void setEntityMouse(double xPos, double yPos);
private:
    std::unique_ptr<EntityWindow> _entityWindow;

    // entity resources
    std::unique_ptr<GLSLProgram> _primitiveShader;
    std::vector<Entity*> _entites;
    std::vector<std::string> _entityNames;
    int _selectedEntity;
    std::vector<std::unique_ptr<ImageTexture2D>> _textures;

    std::unique_ptr<PerspectiveCamera> _camera;

    // environment
    std::unique_ptr<Axis> _axis;
    std::unique_ptr<GLSLProgram> _axisShader;
    AmbientLight _ambient;
    PointLight _light;
    std::unique_ptr<Entity> _lightCube;
    std::unique_ptr<GLSLProgram> _lightCubeShader;

    // entity to construct
    int _chosenEntity = -1;
private:
    void showImGuiWindow();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow *window, int buttom, int action, int mods);
    static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

class EntityWindow: public Window {
public:
    static const int EN_WIDTH;
    static const int EN_HEIGHT;
private:
    std::unique_ptr<GLSLProgram> _primitiveShader;
    std::unique_ptr<GLSLProgram> _simpleShader;
    std::unique_ptr<PerspectiveCamera> _camera;
    AmbientLight _ambient;
    PointLight _light;

    // entities
    std::unique_ptr<Entity> _cube;
    std::unique_ptr<Entity> _sphere;
    std::unique_ptr<Entity> _prism;
    std::unique_ptr<Entity> _pyramid;

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
    // draw entity normal (for debug)
    void drawEntity(const Entity& entity, int index, bool drawNormal);
};

#endif //ROOM_WINDOW_H
