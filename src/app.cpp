#include "app.h"
#include <iostream>
#include <vulkanBoilerplateHelper.h>
#include <vector>
#include <optional>

void Application::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(getWidth(), getHeight(), "Vulkan window", nullptr, nullptr);
}

void Application::createInstance()
{
    VkApplicationInfo info = VkInit::createAppInfo("VulkanApp");
    VkInstanceCreateInfo createInfo = VkInit::instanceCreateInfo(&info);

    uint32_t glfwextensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwextensionCount);

    createInfo.enabledExtensionCount = glfwextensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    for (const auto& extension : extensions) {
        std::cout << extension.extensionName << std::endl;
    }
}

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {

    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    uint32_t i = 0;

    for (const auto& queueFam : queueFamilies) {

        if (queueFam.queueFlags & VK_QUEUE_GRAPHICS_BIT) {

            indices.graphicsFamily = i;
            break;
        }

        i++;
    }

    return indices;
}

inline bool isDeviceSuitable(VkPhysicalDevice device) {

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    QueueFamilyIndices indices = findQueueFamilies(device);

    return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) && indices.isComplete();
}

void Application::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;

    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);

    vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        if (isDeviceSuitable(device))
        {
            m_physicalDevice = device;
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find suitable GPU!");
    }
}

void Application::createLogicalDevice()
{
    QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    deviceCreateInfo.enabledExtensionCount = 0;

    if (vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    volkLoadDevice(m_device);

    vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
}

void Application::initVulkan()
{
    volkInitialize();

    createInstance();

    volkLoadInstance(m_instance);

    pickPhysicalDevice();

    createLogicalDevice();
}

void Application::run()
{
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
    }
}

void Application::cleanup()
{
    vkDestroyDevice(m_device, nullptr);
    vkDestroyInstance(m_instance, nullptr);

    glfwDestroyWindow(m_window);
    glfwTerminate();
}