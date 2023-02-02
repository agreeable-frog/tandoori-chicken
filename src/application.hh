#pragma once

#include "vk_mem_alloc.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

class GlfwContext {
public:
    static GlfwContext& getInstance() {
        static GlfwContext instance;
        return instance;
    }

private:
    GlfwContext() {
        if (glfwInit() == GLFW_FALSE)
            throw std::runtime_error("GLFW library initialisation failed.");
        std::cerr << "GLFW library successfully initialised.\n";
    }
    ~GlfwContext() {
        glfwTerminate();
        std::cerr << "Terminated GLFW library.\n";
    }

public:
    GlfwContext(GlfwContext const&) = delete;
    void operator=(GlfwContext const&) = delete;
};

class VulkanContext {
public:
    static VulkanContext& getInstance() {
        static VulkanContext instance;
        return instance;
    }

private:
    VkInstance _instance;
    VulkanContext() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "None";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cerr << "Available extensions:\n";
        for (const auto& extension : extensions) {
            std::cerr << '\t' << extension.extensionName << '\n';
        }

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        auto result = vkCreateInstance(&createInfo, nullptr, &_instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Error while creating Vulkan instance.");
        }
        std::cerr << "Vulkan instance successfully created.\n";
    }
    ~VulkanContext() {
        vkDestroyInstance(_instance, nullptr);
        std::cerr << "Destroyed Vulkan instance.\n";
    }

public:
    VulkanContext(VulkanContext const&) = delete;
    void operator=(VulkanContext const&) = delete;
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