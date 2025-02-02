#pragma once

#include <vk_types.h>

/// <summary>
/// https://vkguide.dev/docs/new_chapter_2/vulkan_shader_code/
/// </summary>
struct DescriptorLayoutBuilder {

    std::vector<VkDescriptorSetLayoutBinding> bindings;

    void add_binding(uint32_t binding, VkDescriptorType type);
    void clear();
    VkDescriptorSetLayout build(VkDevice device, VkShaderStageFlags shaderStages, void* pNext = nullptr, VkDescriptorSetLayoutCreateFlags flags = 0);
};

/// <summary>
/// https://vkguide.dev/docs/new_chapter_2/vulkan_shader_code/
/// </summary>
struct DescriptorAllocator {

    struct PoolSizeRatio {
        VkDescriptorType type;
        float ratio;
    };

    // Maintaining one big pool for the whole engine involves a lot of effort.
    // We try to have a pool for each part of the engine.
    VkDescriptorPool pool;

    /// <summary>
    /// https://vkguide.dev/docs/new_chapter_2/vulkan_shader_code/
    /// </summary>
    /// <param name="device"></param>
    /// <param name="maxSets">The number of descriptors that can be created in total</param>
    /// <param name="poolRatios">The ratios which define on how the poolsize should be distributed across the descriptor types</param>
    void init_pool(VkDevice device, uint32_t maxSets, std::span<PoolSizeRatio> poolRatios);

    /// <summary>
    /// This will reset all the descriptors of this pool and reset the pool.
    /// </summary>
    /// <param name="device"></param>
    void clear_descriptors(VkDevice device);

    void destroy_pool(VkDevice device);

    VkDescriptorSet allocate(VkDevice device, VkDescriptorSetLayout layout);
};

/// <summary>
/// https://vkguide.dev/docs/new_chapter_4/descriptor_abstractions/
/// </summary>
struct DescriptorAllocatorGrowable {
public:
    struct PoolSizeRatio {
        VkDescriptorType type;
        float ratio;
    };

    void init(VkDevice device, uint32_t initialSets, std::span<PoolSizeRatio> poolRatios);
    void clear_pools(VkDevice device);
    void destroy_pools(VkDevice device);

    VkDescriptorSet allocate(VkDevice device, VkDescriptorSetLayout layout, void* pNext = nullptr);
private:
    VkDescriptorPool get_pool(VkDevice device);
    VkDescriptorPool create_pool(VkDevice device, uint32_t setCount, std::span<PoolSizeRatio> poolRatios);

    std::vector<PoolSizeRatio> ratios;
    std::vector<VkDescriptorPool> fullPools;
    std::vector<VkDescriptorPool> readyPools;
    uint32_t setsPerPool;

};

/// <summary>
/// https://vkguide.dev/docs/new_chapter_4/descriptor_abstractions/
/// </summary>
struct DescriptorWriter {
    std::deque<VkDescriptorImageInfo> imageInfos;
    std::deque<VkDescriptorBufferInfo> bufferInfos;
    std::vector<VkWriteDescriptorSet> writes;

    /// <summary>
    /// https://vkguide.dev/docs/new_chapter_4/descriptor_abstractions/
    /// </summary>
    /// <param name="binding"></param>
    /// <param name="image"></param>
    /// <param name="sampler"></param>
    /// <param name="layout">VK_IMAGE_LAYOUT_[SHADER_READ_ONLY_OPTIMAL | GENERAL]</param>
    /// <param name="type"></param>
    void write_image(int binding, VkImageView image, VkSampler sampler, VkImageLayout layout, VkDescriptorType type);

    /// <summary>
    /// https://vkguide.dev/docs/new_chapter_4/descriptor_abstractions/
    /// </summary>
    /// <param name="binding"></param>
    /// <param name="buffer"></param>
    /// <param name="size"></param>
    /// <param name="offset"></param>
    /// <param name="type">VK_DESCRIPTOR_TYPE_[UNIFORM_BUFFER|STORAGE_BUFFER|UNIFORM_BUFFER_DYNAMIC|STORAGE_BUFFER_DYNAMIC]</param>
    void write_buffer(int binding, VkBuffer buffer, size_t size, size_t offset, VkDescriptorType type);

    void clear();
    void update_set(VkDevice device, VkDescriptorSet set);
};