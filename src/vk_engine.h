// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>

/// <summary>
/// https://vkguide.dev/docs/new_chapter_2/vulkan_new_rendering/
/// </summary>
struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	}

	void flush() {
		// reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)(); //call functors
		}

		deletors.clear();
	}
};


// The data we need for each N (FRAME_OVERLAP) frame from the N-buffering.
// - command pool and buffer: https://vkguide.dev/docs/new_chapter_1/vulkan_commands_code/
// - semaphores and fence: https://vkguide.dev/docs/new_chapter_1/vulkan_mainloop_code/
// - deletion queue: https://vkguide.dev/docs/new_chapter_2/vulkan_new_rendering/
struct FrameData {
	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;

	/// <summary>
	/// The semaphore for which the render commands wait on the swapchain image request.
	/// </summary>
	VkSemaphore _swapchainSemaphore;

	/// <summary>
	/// The semaphore to control presenting the image to the OS once the drawing finishes.
	/// </summary>
	VkSemaphore _renderSemaphore;

	/// <summary>
	/// The fence that will wait for the draw commands of a given frame to be finished.
	/// </summary>
	VkFence _renderFence;

	/// <summary>
	/// The deletion queue for objects which are used within one frame.
	/// </summary>
	DeletionQueue _deletionQueue;
};

constexpr unsigned int FRAME_OVERLAP = 2;

class VulkanEngine {
public:

	bool _isInitialized{ false };
	int _frameNumber {0};
	bool stop_rendering{ false };
	VkExtent2D _windowExtent{ 1700 , 900 };

	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debug_messenger;
	VkPhysicalDevice _chosenGPU;
	VkDevice _device;
	VkSurfaceKHR _surface;

	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat;

	std::vector<VkImage> _swapchainImages;
	std::vector<VkImageView> _swapchainImageViews;
	VkExtent2D _swapchainExtent;

	// The draw image acts as a canvas, so that we don't have to draw directly on the swapchain image.
	AllocatedImage _drawImage;
	// Dimensions for the draw image.
	VkExtent2D _drawExtent;

	FrameData _frames[FRAME_OVERLAP];
	FrameData& get_current_frame() { return _frames[_frameNumber % FRAME_OVERLAP]; };

	VkQueue _graphicsQueue;
	uint32_t _graphicsQueueFamily;

	DeletionQueue _mainDeletionQueue;

	VmaAllocator _allocator;

	struct SDL_Window* _window{ nullptr };

	static VulkanEngine& Get();

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();

private:
	void init_vulkan();
	void init_swapchain();
	void init_commands();
	void init_sync_structures();

	void draw_background(VkCommandBuffer cmd);

	void create_swapchain(uint32_t width, uint32_t height);
	void destroy_swapchain();
};
