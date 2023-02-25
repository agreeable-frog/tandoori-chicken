#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

inline std::ostream& operator<<(std::ostream& stream, const VkPhysicalDeviceType& type) {
    switch(type) {
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            stream << "integrated GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            stream << "main GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            stream << "CPU";
            break;
        default:
            stream << "other";
            break;
    }
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const VkPhysicalDeviceProperties& prop) {
    stream << "Device : " << prop.deviceType << " " << std::string(prop.deviceName) << ", id : " << prop.deviceID << '\n';
    stream << "API version : " << prop.apiVersion << ", driver version : " << prop.driverVersion;
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const VkQueueFamilyProperties& prop) {
    stream << "Queue family :\n" << prop.queueCount << " queues\n";
    stream << "Graphics operations : ";
    prop.queueFlags & VK_QUEUE_GRAPHICS_BIT ? stream << "OK\n" : stream << "KO\n";
    stream << "Compute operations : ";
    prop.queueFlags & VK_QUEUE_COMPUTE_BIT ? stream << "OK\n" : stream << "KO\n";
    stream << "Transfer operations : ";
    prop.queueFlags & VK_QUEUE_TRANSFER_BIT ? stream << "OK\n" : stream << "KO\n";
    return stream;
}