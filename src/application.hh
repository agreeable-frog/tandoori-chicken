#pragma once

#include "vk_mem_alloc.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class GlfwContext {
public:
    static GlfwContext& getInstance() {
        static GlfwContext instance;
        return instance;
    }
private:
    GlfwContext() {
        if (glfwInit() == GLFW_FALSE)
            std::cout << "GLFW library initialisation failed.\n";
        else if (glfwInit() == GLFW_TRUE)
            std::cout << "GLFW library successfully initialised.\n";
    }
    ~GlfwContext() {
        glfwTerminate();
        std::cout << "Terminated GLFW library.\n";
    }
public:
    GlfwContext(GlfwContext const&) = delete;   
    void operator=(GlfwContext const&) = delete;
};

class Window {
private:
    GLFWwindow* _pwindow = nullptr;
    uint32_t _width;
    uint32_t _height;
    std::string _name;

public:
    Window(uint32_t width = 800, uint32_t height = 600, const std::string& name = "Window")
        : _width(width), _height(height), _name(name) {
        GlfwContext::getInstance();
    };

    void create(GLFWmonitor* monitor = nullptr, bool resizeable = false) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _pwindow = glfwCreateWindow(_width, _height, "Vulkan", monitor, nullptr);
    }

    ~Window() {
        if (_pwindow) glfwDestroyWindow(_pwindow);
    }
};