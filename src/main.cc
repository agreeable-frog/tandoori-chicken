#include "application.hh"

int main() {
    auto window = Window();
    VulkanContext::getInstance();
    std::cout << "In main\n";
    return 0;
}