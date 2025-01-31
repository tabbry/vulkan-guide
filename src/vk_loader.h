#pragma once

#include <vk_types.h>
#include <unordered_map>
#include <filesystem>

struct GeoSurface {
    uint32_t startIndex;
    uint32_t count;
};

struct MeshAsset {
    std::string name;

    std::vector<GeoSurface> surfaces;
    GPUMeshBuffers meshBuffers;
};

//forward declaration
class VulkanEngine;

/// <summary>
/// Only supports binary GLTF files.
/// <param name="engine"></param>
/// <param name="filePath"></param>
/// <returns>The return value could be errored or null</returns>
/// </summary>
std::optional<std::vector<std::shared_ptr<MeshAsset>>> loadGltfMeshes(VulkanEngine* engine, std::filesystem::path filePath);