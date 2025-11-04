#include "cgamelibs.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initializes the Vulkan surface for the specified window.
 *
 * This function uses GLFW's built-in method to create a Vulkan surface 
 * associated with the given `Window` struct. The resulting surface handle 
 * is stored in the `vkSurfaceKHR` member of the `Window` struct.
 *
 * If the surface creation fails, an error message is printed to stderr, 
 * and the program exits.
 *
 * @param window Pointer to a `Window` struct that contains the GLFW 
 *               window handle and the Vulkan instance required for surface 
 *               creation. The function modifies the `vkSurfaceKHR` member 
 *               to store the created surface handle.
 */
void init_surface(Window *window) {
    // GLFW has a built-in function to create a surface from the window
    int retval = glfwCreateWindowSurface(window->vkInstance, window->glfwWindow, NULL, &window->vkSurfaceKHR);
    if (retval != VK_SUCCESS) {
        fprintf(stderr, "Failed to create window surface!\nReason: %d\n", retval);
        exit(EXIT_FAILURE);
    }
}