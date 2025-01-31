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

/// <summary>
/// https://vkguide.dev/docs/new_chapter_3/building_pipeline/
/// </summary>
class PipelineBuilder {
public:
    std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;

    VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
    VkPipelineRasterizationStateCreateInfo _rasterizer;
    VkPipelineColorBlendAttachmentState _colorBlendAttachment;
    VkPipelineMultisampleStateCreateInfo _multisampling;
    VkPipelineLayout _pipelineLayout;
    VkPipelineDepthStencilStateCreateInfo _depthStencil;
    VkPipelineRenderingCreateInfo _renderInfo;
    VkFormat _colorAttachmentformat;

    PipelineBuilder() { clear(); }

    void clear();

    VkPipeline build_pipeline(VkDevice device);
    void set_shaders(VkShaderModule vertexShader, VkShaderModule fragmentShader);

    /// <summary>
    /// What Topology (TRIANGLE, POINT,...) is used for drawing the geometry.
    /// </summary>
    /// <param name="topology"></param>
    void set_input_topology(VkPrimitiveTopology topology);

    /// <summary>
    /// Sets the polygon mode for the rasterizer.
    /// </summary>
    /// <param name="mode"></param>
    void set_polygon_mode(VkPolygonMode mode);

    /// <summary>
    /// Sets the cull mode for the rasterizer.
    /// </summary>
    /// <param name="cullMode"></param>
    /// <param name="frontFace"></param>
    void set_cull_mode(VkCullModeFlags cullMode, VkFrontFace frontFace);

    void set_multisampling_none();

    void disable_blending();

    void set_color_attachment_format(VkFormat format);
    void set_depth_format(VkFormat format);
    void enable_depthtest(bool depthWriteEnable, VkCompareOp op);
    /// <summary>
    /// Disables depth test by modifying the values for _depthStencil.
    /// </summary>
    void disable_depthtest();

    void enable_blending_additive();
    void enable_blending_alphablend();
};