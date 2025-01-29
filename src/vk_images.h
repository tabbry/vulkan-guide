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

	/// <summary>
	/// https://vkguide.dev/docs/new_chapter_2/vulkan_new_rendering/
	/// </summary>
	/// <param name="cmd"></param>
	/// <param name="source"></param>
	/// <param name="destination"></param>
	/// <param name="srcSize"></param>
	/// <param name="dstSize"></param>
	void copy_image_to_image(VkCommandBuffer cmd, VkImage source, VkImage destination, VkExtent2D srcSize, VkExtent2D dstSize);
};