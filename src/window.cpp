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

void Window::initNormalShader() {
    _normalShader = std::make_unique<GLSLProgram>();
    _normalShader->attachVertexShaderFromFile("../glsl/normal.vert");
    _normalShader->attachGeometryShaderFromFile("../glsl/normal.geom");
    _normalShader->attachFragmentShaderFromFile("../glsl/normal.frag");
    _normalShader->link();
}

void Window::makeCurrent() {
    glfwMakeContextCurrent(_window);
}

int Window::shouldClose() {
    return glfwWindowShouldClose(_window);
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

void MainWindow::key_callback(GLFWwindow *window, int key, int, int action, int) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
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

void MainWindow::chooseEntity(double xPos, double yPos) {
    entityWindow->chooseEntity(xPos, yPos);
}

// EntityWindow
// ------------
int const EntityWindow::EN_HEIGHT = 800;
int const EntityWindow::EN_WIDTH = 800;

EntityWindow::EntityWindow(MainWindow *mainWindow):
        Window(EN_WIDTH, EN_HEIGHT, "Create Entity"),
        chosenEntity(-1)
    {
    // init window
    glfwSetWindowCloseCallback(_window, window_close_callback);
    glfwSetCursorPosCallback(_window, cursor_position_callback);
    glfwSetWindowUserPointer(_window, mainWindow);
    glfwSetWindowAttrib(_window, GLFW_RESIZABLE, false);

    // init entities
    _cube = std::make_unique<Cube>(2.0f);
    _sphere = std::make_unique<Sphere>(2.0f, 36, 36);
    _prism = std::make_unique<Frustum>(2.0f, 2.0f, 4.0f, 36);
    _pyramid = std::make_unique<Frustum>(2.0f, 0.0f, 4.0f, 36);

    // init light cube
    _lightCube = std::make_unique<Cube>(0.5f);
    _lightCube->position = glm::vec3(5.0f, 3.0f, 4.0f);

    // init quad
    _quad[0] = std::make_unique<Quad>(-1.0f, 0.0f, 1.0f, 0.0f);
    _quad[1] = std::make_unique<Quad>(0.0f, 1.0f, 1.0f, 0.0f);
    _quad[2] = std::make_unique<Quad>(-1.0f, 0.0f, 0.0f, -1.0f);
    _quad[3] = std::make_unique<Quad>(0.0f, 1.0f, 0.0f, -1.0f);

    // init shader
    _primitiveShader = std::make_unique<GLSLProgram>();
    _primitiveShader->attachVertexShaderFromFile("../glsl/primitive.vert");
    _primitiveShader->attachGeometryShaderFromFile("../glsl/primitive.geom");
    _primitiveShader->attachFragmentShaderFromFile("../glsl/primitive.frag");
    _primitiveShader->link();
    _simpleShader = std::make_unique<GLSLProgram>();
    _simpleShader->attachVertexShaderFromFile("../glsl/simple.vert");
    _simpleShader->attachFragmentShaderFromFile("../glsl/simple.frag");
    _simpleShader->link();
    _quadShader = std::make_unique<GLSLProgram>();
    _quadShader->attachVertexShaderFromFile("../glsl/quad.vert");
    _quadShader->attachFragmentShaderFromFile("../glsl/quad.frag");
    _quadShader->link();
    initNormalShader();

    // init framebuffer and its texture
    _framebuffer = std::make_unique<Framebuffer>();
    _colorTexture = std::make_unique<Texture2D>(
            GL_RGBA, EN_WIDTH, EN_HEIGHT, GL_RGBA, GL_FLOAT);
    _depthTexture = std::make_unique<Texture2D>(
            GL_DEPTH_COMPONENT32, EN_WIDTH, EN_HEIGHT,
            GL_DEPTH_COMPONENT, GL_FLOAT);
    _framebuffer->attachTexture2D(*_colorTexture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D);
    _framebuffer->attachTexture2D(*_depthTexture, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D);

    // init camera
    _camera = std::make_unique<PerspectiveCamera>(glm::radians(50.0f),
                                                  (float)EN_WIDTH / EN_HEIGHT, .1f, 10000.0f);
    _camera->position = glm::vec3(5.0f, 4.0f, 4.0f);

    // init light
    _light.color = glm::vec3(0.3f, 0.4f, 0.8f);
    _light.position = glm::vec3(3.0f, -3.0f, 3.0f);
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

    // rotate
    _cube->rotation = glm::angleAxis((float)currentFrame / 2, _cube->getDefaultUp());
    _sphere->rotation = glm::angleAxis((float)currentFrame / 2, _sphere->getDefaultUp());
    _prism->rotation = glm::angleAxis((float)currentFrame / 2, _prism->getDefaultUp());
    _pyramid->rotation = glm::angleAxis((float)currentFrame / 2, _pyramid->getDefaultUp());
    _lightCube->position = _light.position;

    glfwMakeContextCurrent(_window);
    /* begin render */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw primitives
    drawEntity(*_cube, 0);
    drawEntity(*_sphere, 1);
    drawEntity(*_prism, 2);
    drawEntity(*_pyramid, 3);

//    std::cout << glGetError() << std::endl;
    /* end render */
    glfwSwapBuffers(_window);
}

void EntityWindow::drawLightCube() {
    _simpleShader->use();
    _simpleShader->setUniformMat4("model", _lightCube->getModelMat());
    _simpleShader->setUniformMat4("view", _camera->getViewMatrix());
    _simpleShader->setUniformMat4("project", _camera->getProjectionMatrix());
    _lightCube->draw();
}

void EntityWindow::drawEntity(const Entity &entity, int index) {
    // bind framebuffer and clear
    _framebuffer->bind();
    glClearColor(0.0f, .0f, .0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (chosenEntity == index) {
        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.1f));
        _simpleShader->use();
        _simpleShader->setUniformMat4("model", entity.getModelMat() * scaleMat);
        _simpleShader->setUniformMat4("view", _camera->getViewMatrix());
        _simpleShader->setUniformMat4("project", _camera->getProjectionMatrix());
        entity.draw();
    }

    _primitiveShader->use();
    _primitiveShader->setUniformMat4("model", entity.getModelMat());
    _primitiveShader->setUniformMat4("view", _camera->getViewMatrix());
    _primitiveShader->setUniformMat4("project", _camera->getProjectionMatrix());
    _primitiveShader->setUniformVec3("light.color", _light.color);
    _primitiveShader->setUniformVec3("light.position", _light.position);
    _primitiveShader->setUniformFloat("light.intensity", _light.intensity);
    _primitiveShader->setUniformVec3("ambient.color", _ambient.color);
    _primitiveShader->setUniformFloat("ambient.intensity", _ambient.intensity);
    _primitiveShader->setUniformVec3("material.ka", entity.ka);
    _primitiveShader->setUniformVec3("material.kd", entity.kd);
    _primitiveShader->setUniformVec3("material.ks", entity.ks);
    _primitiveShader->setUniformFloat("material.ns", entity.ns);
    _primitiveShader->setUniformVec3("viewPos", _camera->position);
    glEnable(GL_DEPTH_TEST);
    entity.draw();
    glDisable(GL_DEPTH_TEST);

    _framebuffer->unbind();
    _quadShader->use();
    _quadShader->setUniformInt("aTex", 0);
    _colorTexture->bind(0);
    _quad[index]->draw();
}

EntityWindow::~EntityWindow() {
    _cube = nullptr;
    _primitiveShader = nullptr;
    glfwDestroyWindow(_window);
}

void EntityWindow::cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    auto mainWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    mainWindow->chooseEntity(xpos, ypos);
}

void EntityWindow::chooseEntity(double xPos, double yPos) {
    if (xPos < EN_WIDTH / 2 && yPos < EN_HEIGHT / 2)
        chosenEntity = 0;
    else if (xPos >= EN_WIDTH / 2 && yPos < EN_HEIGHT / 2)
        chosenEntity = 1;
    else if (xPos < EN_WIDTH / 2 && yPos >= EN_HEIGHT / 2)
        chosenEntity = 2;
    else
        chosenEntity = 3;
}
