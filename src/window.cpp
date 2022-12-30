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

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

// MainWindow
// ----------

MainWindow::MainWindow(int width, int height): Window(width, height, "MainWindow") {
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void MainWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void MainWindow::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        std::cout << "key a pressed with shift hold" << std::endl;
}

