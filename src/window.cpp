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

    // init entities
    _cube = std::make_unique<Cube>(2.0f);
    _cube->ka = glm::vec3(1.0f);
    _cube->ns = 32.0f;

    // init light cube
    _lightCube = std::make_unique<Cube>(0.5f);
    _lightCube->position = glm::vec3(5.0f, 3.0f, 4.0f);

    // init shader
    _primitiveShader = std::make_unique<GLSLProgram>();
    _primitiveShader->attachVertexShaderFromFile("../glsl/primitive.vert");
    _primitiveShader->attachGeometryShaderFromFile("../glsl/primitive.geom");
    _primitiveShader->attachFragmentShaderFromFile("../glsl/primitive.frag");
    _primitiveShader->link();
    _cubeShader = std::make_unique<GLSLProgram>();
    _cubeShader->attachVertexShaderFromFile("../glsl/simple.vert");
    _cubeShader->attachFragmentShaderFromFile("../glsl/simple.frag");
    _cubeShader->link();

    // init camera
    _camera = std::make_unique<PerspectiveCamera>(glm::radians(50.0f),
                                                  (float)ENWIDTH / ENHEIGHT, .1f, 10000.0f);
    _camera->position = glm::vec3(8.0f, 7.0f, 10.0f);

    // init light
    _light.color = glm::vec3(0.3f, 0.4f, 0.8f);
    _ambient.color = glm::vec3(0.3f, 0.4f, 0.8f);
}

void EntityWindow::window_close_callback(GLFWwindow *window) {
    auto *mainWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    mainWindow->switchEntity();
}

void EntityWindow::render() {
    // process time
    double currentFrame = glfwGetTime();
    _deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;

    // set point light position due to time
    _light.position = glm::vec3(3 * glm::sin(glm::radians(currentFrame * 50)),
                                 3 * glm::cos(glm::radians(currentFrame * 50)),
                                 3.0f);
    _lightCube->position = _light.position;
    glfwMakeContextCurrent(_window);
    glClearColor(.0f, .0f, .0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw point light cube
    _cubeShader->use();
    _cubeShader->setUniformMat4("model", _lightCube->getModelMat());
    _cubeShader->setUniformMat4("view", _camera->getViewMatrix());
    _cubeShader->setUniformMat4("project", _camera->getProjectionMatrix());
    _lightCube->draw();

    // draw primitives
    _primitiveShader->use();
    _primitiveShader->setUniformMat4("model", _cube->getModelMat());
    _primitiveShader->setUniformMat4("view", _camera->getViewMatrix());
    _primitiveShader->setUniformMat4("project", _camera->getProjectionMatrix());
    _primitiveShader->setUniformVec3("light.color", _light.color);
    _primitiveShader->setUniformVec3("light.position", _light.position);
    _primitiveShader->setUniformFloat("light.intensity", _light.intensity);
    _primitiveShader->setUniformVec3("ambient.color", _ambient.color);
    _primitiveShader->setUniformFloat("ambient.intensity", _ambient.intensity);
    _primitiveShader->setUniformVec3("material.ka", _cube->ka);
    _primitiveShader->setUniformVec3("material.kd", _cube->kd);
    _primitiveShader->setUniformVec3("material.ks", _cube->ks);
    _primitiveShader->setUniformFloat("material.ns", _cube->ns);
    _primitiveShader->setUniformVec3("viewPos", glm::vec3(8.0f, 10.0f, 7.0f));
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
