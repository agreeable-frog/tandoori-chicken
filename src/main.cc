#include "application.hh"

int main() {
    auto window = Window();
    VulkanContext::getInstance();
    auto& physicalDevice = PhysicalDevice::pickDevice();
    std::cout << "Chosen device : " << physicalDevice.getName() << '\n';
    auto logicalDevice = LogicalDevice(physicalDevice);
    return 0;
}