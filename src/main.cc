#include "application.hh"

int main() {
    auto window = Window();
    VulkanContext::getInstance();
    auto physicalDevice = PhysicalDevice::pickDevice();
    std::cout << "In main\n";
    return 0;
}