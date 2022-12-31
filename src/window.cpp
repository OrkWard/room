#include "window.h"

#include <memory>
// base class Window
// -----------------

Window::Window(int width, int height, char const *title) {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW mainWindow" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
}

void Window::makeCurrent() {
    glfwMakeContextCurrent(window);
}

int Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

GLFWwindow *Window::getHandle() {
    return window;
}

// MainWindow
// ----------

MainWindow::MainWindow(int width, int height): Window(width, height, "Room") {
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void MainWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void MainWindow::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT) {
        auto* mainWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
        mainWindow->switchEntity();
    }
}

void MainWindow::switchEntity() {
    if (!entityWindow)
        entityWindow = std::make_unique<EntityWindow>(this);
    else
        entityWindow = nullptr;
}

void MainWindow::render() {
    glfwMakeContextCurrent(window);
    if (entityWindow)
        entityWindow->render();
    glfwSwapBuffers(window);
}

// EntityWindow
// ------------

EntityWindow::EntityWindow(MainWindow *mainWindow): Window(ENWIDTH, ENHEIGHT, "Create Entity") {
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetWindowUserPointer(window, mainWindow);
    createEntity = std::make_unique<CreateEntity>(1, 1, 1, 1);

    triShader = std::make_unique<GLSLProgram>();
    triShader->attachVertexShaderFromFile("../glsl/triangle.vert");
    triShader->attachFragmentShaderFromFile("../glsl/triangle.frag");
    triShader->link();
}

void EntityWindow::window_close_callback(GLFWwindow *window) {
    auto *mainWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    mainWindow->switchEntity();
}

void EntityWindow::render() {
    glfwMakeContextCurrent(window);
    triShader->use();
    createEntity->draw();
    glfwSwapBuffers(window);
}

EntityWindow::~EntityWindow() {
    createEntity = nullptr;
    triShader = nullptr;
    glfwDestroyWindow(window);
}