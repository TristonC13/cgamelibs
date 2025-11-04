#include <stdio.h>
#include <stdlib.h> // Required for malloc
#include <vulkan/vulkan_core.h>

#include "cgamelibs.h"

/**
 * Queries and allocates memory for Vulkan physical devices.
 * The caller is responsible for freeing the memory allocated to *window->vkPhysicalDevs.
 *
 * @param window The game window
 * @param window->vkPhysicalDevs A pointer to a VkPhysicalDevice* to store the dynamically allocated array.
 */
void query_devices(Window *window) {
    // Vulkan uses uint32_t for counts, but we'll use 'unsigned' as requested
    VkResult res;

    // Initialize output pointers to a safe state
    if (window->vkPhysicalDevCount) window->vkPhysicalDevCount = 0;
    if (window->vkPhysicalDevs) window->vkPhysicalDevs = NULL;

    // --- 1. Get the number of physical devices (Count phase) ---
    // Note: We use a local uint32_t 'count' to ensure type compatibility with vkEnumeratePhysicalDevices
    res = vkEnumeratePhysicalDevices(window->vkInstance, &window->vkPhysicalDevCount, NULL);

    if (res != VK_SUCCESS) {
        fprintf(stderr, "Error: Failed to query physical device count (VkResult: %d).\n", res);
        return;
    }

    if (window->vkPhysicalDevCount == 0) {
        fprintf(stderr, "Warning: No physical devices with Vulkan support found.\n");
        return;
    }

    // Allocate memory on the heap (The fix for the stack allocation error)
    window->vkPhysicalDevs = malloc(window->vkPhysicalDevCount * sizeof(VkPhysicalDevice));
    if (window->vkPhysicalDevs == NULL) {
        fprintf(stderr, "Fatal Error: Failed to allocate memory for %u physical devices.\n", window->vkPhysicalDevCount);
        return;
    }

    // --- 3. Get the physical devices (Population phase) ---
    // Pass the allocated array pointer to retrieve the device handles
    res = vkEnumeratePhysicalDevices(window->vkInstance, &window->vkPhysicalDevCount, window->vkPhysicalDevs);

    if (res != VK_SUCCESS && res != VK_INCOMPLETE) {
        fprintf(stderr, "Error: Failed to enumerate physical devices (VkResult: %d).\n", res);
        // Clean up allocated memory on failure
        free(window->vkPhysicalDevs);
        window->vkPhysicalDevs = NULL;
        return;
    }

    // --- 4. Success: Set the final count and devices for the caller ---
    if (window->vkPhysicalDevCount) {
        window->vkPhysicalDevCount = (unsigned)window->vkPhysicalDevCount;
    }

    printf("Successfully found and retrieved %u physical device(s).\n", window->vkPhysicalDevCount);
}