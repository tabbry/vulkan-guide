#pragma once 

#include <vulkan/vulkan.h>

namespace vkutil {

	/// <summary>
	/// https://vkguide.dev/docs/new_chapter_1/vulkan_mainloop_code/
	/// </summary>
	/// <param name="cmd"></param>
	/// <param name="image"></param>
	/// <param name="currentLayout"></param>
	/// <param name="newLayout"></param>
	void transition_image(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);
};