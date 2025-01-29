#pragma once 
#include <vk_types.h>

namespace vkutil {

    /// <summary>
    /// https://vkguide.dev/docs/new_chapter_2/vulkan_shader_code/
    /// </summary>
    /// <param name="filePath"></param>
    /// <param name="device"></param>
    /// <param name="outShaderModule"></param>
    /// <returns></returns>
    bool load_shader_module(const char* filePath, VkDevice device, VkShaderModule* outShaderModule);
};