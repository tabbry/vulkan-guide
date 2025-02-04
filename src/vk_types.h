﻿// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.
#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <span>
#include <array>
#include <functional>
#include <deque>

#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>
#include <vk_mem_alloc.h>

#include <fmt/core.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>


#define VK_CHECK(x)                                                     \
    do {                                                                \
        VkResult err = x;                                               \
        if (err) {                                                      \
            fmt::println("Detected Vulkan error: {}", string_VkResult(err)); \
            abort();                                                    \
        }                                                               \
    } while (0)

/// <summary>
/// https://vkguide.dev/docs/new_chapter_2/vulkan_new_rendering/
/// </summary>
struct AllocatedImage {
    VkImage image;
    VkImageView imageView;
    VmaAllocation allocation;
    VkExtent3D imageExtent;
    VkFormat imageFormat;
};

/// <summary>
/// https://vkguide.dev/docs/new_chapter_3/mesh_buffers/
/// </summary>
struct AllocatedBuffer {
    VkBuffer buffer;
    VmaAllocation allocation;
    VmaAllocationInfo info;
};

/// <summary>
/// https://vkguide.dev/docs/new_chapter_3/mesh_buffers/
/// </summary>
struct Vertex {

    glm::vec3 position;

    // The UV properties are "positioned" like this to better align with GPU limitations.
    float uv_x;
    glm::vec3 normal;
    float uv_y;
    glm::vec4 color;
};


/// <summary>
/// holds the resources needed for a mesh
/// https://vkguide.dev/docs/new_chapter_3/mesh_buffers/
/// </summary>
struct GPUMeshBuffers {

    AllocatedBuffer indexBuffer;
    AllocatedBuffer vertexBuffer;
    VkDeviceAddress vertexBufferAddress;
};

/// <summary>
/// push constants for our mesh object draws
/// https://vkguide.dev/docs/new_chapter_3/mesh_buffers/
/// </summary>
struct GPUDrawPushConstants {
    glm::mat4 worldMatrix;
    VkDeviceAddress vertexBuffer;
};

enum class MaterialPass :uint8_t {
    MainColor,
    Transparent,
    Other
};
struct MaterialPipeline {
    VkPipeline pipeline;
    VkPipelineLayout layout;
};

struct MaterialInstance {
    /// <summary>
    /// Non-owning pointer to the material pipeline.
    /// </summary>
    MaterialPipeline* pipeline;
    VkDescriptorSet materialSet;
    MaterialPass passType;
};