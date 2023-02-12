#pragma once

#include "vk_mem_alloc.hh"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hh"

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

    const VkInstance& getHandle() const {
        return _handle;
    }

private:
    VkInstance _handle;
    const std::vector<const char*> _validationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
    VkDebugUtilsMessengerEXT _debugMessenger;

    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks* pAllocator);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();

    VulkanContext();
    ~VulkanContext() {
        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(_handle, _debugMessenger, nullptr);
        }
        vkDestroyInstance(_handle, nullptr);
        std::cerr << "Destroyed Vulkan instance.\n";
    }

public:
    VulkanContext(VulkanContext const&) = delete;
    void operator=(VulkanContext const&) = delete;
};

class Window {
private:
    GLFWwindow* _handle = nullptr;
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

        _handle = glfwCreateWindow(_width, _height, "Vulkan", monitor, nullptr);
    }

    ~Window() {
        if (_handle) glfwDestroyWindow(_handle);
    }
};

class PhysicalDevice {
public:
    static std::vector<PhysicalDevice>& getPhysicalDevices(bool force = false);
    static PhysicalDevice& pickDevice(bool force = false);

private:
    VkPhysicalDevice _handle;
    VkPhysicalDeviceProperties _deviceProperties;
    VkPhysicalDeviceFeatures _deviceFeatures;
    std::vector<VkQueueFamilyProperties> _deviceQueueFamilies;
    PhysicalDevice(const VkPhysicalDevice& handle) {
        _handle = handle;
        vkGetPhysicalDeviceProperties(_handle, &_deviceProperties);
        std::cout << _deviceProperties << '\n';
        vkGetPhysicalDeviceFeatures(_handle, &_deviceFeatures);
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(_handle, &queueFamilyCount, nullptr);
        _deviceQueueFamilies = std::vector<VkQueueFamilyProperties>(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(_handle, &queueFamilyCount, _deviceQueueFamilies.data());
    };
};