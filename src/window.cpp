#include "window.h"

// base class Window
// -----------------

Window::Window(int width, int height, char const *title) {
    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (_window == nullptr) {
        std::cout << "Failed to create GLFW mainWindow" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwSetWindowUserPointer(_window, this);
    glfwMakeContextCurrent(_window);
}

void Window::makeCurrent() {
    glfwMakeContextCurrent(_window);
}

int Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

GLFWwindow *Window::getHandle() {
    return _window;
}

// MainWindow
// ----------

MainWindow::MainWindow(int width, int height): Window(width, height, "Room") {
    glfwSetKeyCallback(_window, key_callback);
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

MainWindow::~MainWindow() {
    entityWindow = nullptr;
    glfwDestroyWindow(_window);
}

void MainWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glfwMakeContextCurrent(window);
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
    glfwMakeContextCurrent(_window);
    if (entityWindow)
        entityWindow->render();
    glfwSwapBuffers(_window);
}

// EntityWindow
// ------------

EntityWindow::EntityWindow(MainWindow *mainWindow): Window(ENWIDTH, ENHEIGHT, "Create Entity") {
    // init window
    glfwSetWindowCloseCallback(_window, window_close_callback);
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    glfwSetWindowUserPointer(_window, mainWindow);
    _cube = std::make_unique<Cube>(1.0f);

    // init shader
    _primitiveShader = std::make_unique<GLSLProgram>();
    _primitiveShader->attachVertexShaderFromFile("../glsl/primitive.vert");
    _primitiveShader->attachGeometryShaderFromFile("../glsl/primitive.geom");
    _primitiveShader->attachFragmentShaderFromFile("../glsl/primitive.frag");
    _primitiveShader->link();

    // init camera
    _camera = std::make_unique<PerspectiveCamera>(glm::radians(50.0f),
                                                  1.0 * ENWIDTH / ENHEIGHT, .1f, 10000.0f);
    _camera->transform.position = glm::vec3(5.0f, 5.0f, 5.0f);
    _camera->transform.lookAt(glm::vec3(0.0f));

    // init light
    _light.color = glm::vec3(0.3f, 0.4f, 0.8f);
    _light.direction = glm::vec3(0.0f) - glm::vec3(5.0f, 4.0f, 3.0f);
}

void EntityWindow::window_close_callback(GLFWwindow *window) {
    auto *mainWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    mainWindow->switchEntity();
}

void EntityWindow::render() {
    glfwMakeContextCurrent(_window);
    glClearColor(.0f, .0f, .0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _primitiveShader->use();
    glm::mat4 model(1.0f);
    _primitiveShader->setUniformMat4("model", model);
    _primitiveShader->setUniformMat4("view", _camera->getViewMatrix());
    _primitiveShader->setUniformMat4("project", _camera->getProjectionMatrix());
    _primitiveShader->setUniformVec3("light.color", glm::vec3(0.5f, 0.3f, 0.8f));
    _primitiveShader->setUniformVec3("light.direction", glm::vec3(-5.0f, -10.0f, -13.0f));
    _primitiveShader->setUniformFloat("light.intensity", 1.0f);
    _primitiveShader->setUniformVec3("ambient.color", glm::vec3(1.0f));
    _primitiveShader->setUniformFloat("ambient.intensity", 0.1f);
    _primitiveShader->setUniformVec3("material.ka", glm::vec3(0.1f));
    _primitiveShader->setUniformVec3("material.kd", glm::vec3(1.0f));
    _cube->draw();
//    std::cout << glGetError() << std::endl;
    glfwSwapBuffers(_window);
}

EntityWindow::~EntityWindow() {
    _cube = nullptr;
    _primitiveShader = nullptr;
    glfwDestroyWindow(_window);
}

void EntityWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
}
