//
// Created by ZZDirty on 2020/3/1.
//

#ifndef VULCANDEMO_HELLOTRIANGLEAPPLICATION_H
#define VULCANDEMO_HELLOTRIANGLEAPPLICATION_H
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>

#include <stdexcept>
#include <set>
#include <vector>
#include <optional>
#include <array>
#include <algorithm>
#include <fstream>

//------------ some const variables defined here

const int MAX_FRAMES_IN_FLIGHT = 2;

//------------ some functions defined here:

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger, const
                                   VkAllocationCallbacks *pAllocator);

std::vector<char> readFile(const std::string &filename);

//------------ some structs definde here
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; //vec2
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT; //vec3
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }

};

//------------ Application Defined Here

class HelloTriangleApplication {
public:
    const int width = 1024;
    const int height = 768;
    const char *title = "Vulkan";

    const std::vector<Vertex> vertices = {
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };//交叉顶点属性定义

    const std::vector<const char *> validationLayers = { // 要开启的validationLayers
            "VK_LAYER_KHRONOS_validation",
            //"VK_LAYER_NV_nomad_release_public_2020_1_1",
            //"VK_LAYER_NV_GPU_Trace_release_public_2020_1_1",
            "VK_LAYER_NV_nsight-sys",
            //"VK_LAYER_NV_optimus",
            //"VK_LAYER_NV_nsight",
    };

    const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

#ifdef NDEBUG //如果是Debug模式那么开启validationLayers
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    GLFWwindow *window;

    void run();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallBack(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                        void *pUserData);

    static void
    populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

private:
    VkInstance instance;

    VkDebugUtilsMessengerEXT debugMessenger;

    //物理设备的抽象
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    //逻辑设备的抽象
    VkDevice device;

    //图形队列
    VkQueue graphicsQueue;

    //与屏幕交互的Extension
    VkSurfaceKHR surface;

    //呈现队列
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;

    //swapChain的图像，自动销毁
    std::vector<VkImage> swapChainImages;

    VkFormat swapChainImageFormat;

    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;

    VkPipelineLayout pipelineLayout;

    VkRenderPass renderPass;

    VkPipeline graphicsPipeline;

    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkCommandPool commandPool;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;

    std::vector<VkSemaphore> renderFinishedSemaphores;

    size_t currentFrame = 0;

    bool framebufferResized = false;

    std::vector<VkFence> inFlightFences;

    std::vector<VkFence> imagesInFlight;

    VkBuffer vertexBuffer;

    VkDeviceMemory vertexBufferMemory;

    void initWindow();

    void mainLoop();

    void cleanUp();

    void initVulkan();

    void createInstance();

    bool checkValidationLayerSupport();

    void setupDebugMessenger();

    void pickPhysicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice device);

    void createLogicalDevice();

    void createSurface();

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice d);

    std::vector<const char *> getRequiredExtensions();

    bool checkDeviceExtensionSupport(VkPhysicalDevice d);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice d);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    void createSwapChain();

    void createImageViews();

    void createGraphicsPipeline();

    VkShaderModule createShaderModule(const std::vector<char> &code);

    void createRenderPass();

    void createFramebuffers();

    void createCommandPool();

    void createCommandBuffers();

    void drawFrame();

    void createSyncObjects();

    void recreateSwapChain();

    void cleanupSwapChain();

    static void framebufferResizeCallback(GLFWwindow *window, int width,
                                          int height);

    void createVertexBuffer();

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

};


#endif //VULCANDEMO_HELLOTRIANGLEAPPLICATION_H
