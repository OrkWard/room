#include "window.h"

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

MainWindow::~MainWindow() {
    entityWindow = nullptr;
    glfwDestroyWindow(window);
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
    glfwMakeContextCurrent(window);
    if (entityWindow)
        entityWindow->render();
    glfwSwapBuffers(window);
}

// EntityWindow
// ------------

EntityWindow::EntityWindow(MainWindow *mainWindow): Window(ENWIDTH, ENHEIGHT, "Create Entity") {
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window, mainWindow);
    cube = std::make_unique<Cube>();

    primitiveShader = std::make_unique<GLSLProgram>();
    primitiveShader->attachVertexShaderFromFile("../glsl/primitive.vert");
    primitiveShader->attachFragmentShaderFromFile("../glsl/primitive.frag");
    primitiveShader->link();
}

void EntityWindow::window_close_callback(GLFWwindow *window) {
    auto *mainWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    mainWindow->switchEntity();
}

void EntityWindow::render() {
    glfwMakeContextCurrent(window);
    glClearColor(0.3f, 0.2f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    primitiveShader->use();
    glm::mat4 model(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(5.0f, 5.0f, 5.0f),
                                 glm::vec3(.0f, .0f, .0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 project = glm::perspective(glm::radians(45.0f),
                                            (float)ENWIDTH / ENHEIGHT, 0.1f, 100.0f);
    primitiveShader->setUniformMat4("model", model);
    primitiveShader->setUniformMat4("view", view);
    primitiveShader->setUniformMat4("project", project);
    cube->draw();
    glfwSwapBuffers(window);
}

EntityWindow::~EntityWindow() {
    cube = nullptr;
    primitiveShader = nullptr;
    glfwDestroyWindow(window);
}

void EntityWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
}
