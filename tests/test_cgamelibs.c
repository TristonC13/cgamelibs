#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "cgamelibs.h"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Function declarations
void mainLoop(GLFWwindow* window);
void cleanup(GLFWwindow* window, VkInstance instance, VkSurfaceKHR surface);
//void create_instance(VkInstance *instance);

int main() {
    Window window;

    VkInstance vk_instance = VK_NULL_HANDLE; // Initialize to null
    VkSurfaceKHR vk_surface = VK_NULL_HANDLE; // Initialize to null

    // 1. Initialize GLFW and create the window
    // This calls glfwInit(), which must happen before querying extensions.
    init_window(&window, 800, 600);
    
    // 2. Create the Vulkan instance
    // Now glfwGetRequiredInstanceExtensions will work correctly.
    init_vkinstance(&window);
    
    // 3. Create the window surface
    init_surface(&window);
    
    mainLoop(window.glfwWindow);
    
    // 4. Cleanup Vulkan and GLFW resources
    cleanup(window.glfwWindow, vk_instance, vk_surface); // **Updated call**

    return 0;
}

/**
 * @brief The main loop that keeps the window open.
 * @param window The GLFWwindow pointer.
 */
void mainLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        // Process all pending events like window closing, key presses, etc.
        glfwPollEvents();

        // **NOTE:** Since we haven't set up a Vulkan rendering pipeline (Instance, 
        // Swapchain, Render Pass, etc.) and aren't clearing the screen, 
        // the window will appear **blank** or with residual desktop content, 
        // which fulfills the requirement of this basic example.
    }
}

/**
 * @brief Cleans up Vulkan and GLFW resources.
 * @param window The GLFWwindow pointer.
 * @param instance The VkInstance to destroy.
 * @param surface The VkSurfaceKHR to destroy.
 */
void cleanup(GLFWwindow* window, VkInstance instance, VkSurfaceKHR surface) {
    // 1. Destroy the Vulkan surface
    if (surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance, surface, NULL);
        printf("Vulkan Window Surface destroyed.\n");
    }

    // 2. Destroy the Vulkan instance
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, NULL);
        printf("Vulkan Instance destroyed.\n");
    }

    // 3. Destroy the GLFW window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    printf("Program terminated successfully.\n");
}