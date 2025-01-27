This is just the repo for the personal learning progress of the [vulkan-guide](https://vkguide.dev/).

# Prerequisites Visual Studio 2022

When opening the rego, VS will ask to install all missing components.

# Project Setup

[Link](https://vkguide.dev/docs/new_chapter_0/building_project/)

## Installations

1. Clone Repo
2. Install [Vulkan SDK ](https://vulkan.lunarg.com/sdk/home) (restart may be required after installation)
3. Install [CMake](https://cmake.org/download/)

## Building

1. In Solution Exlporer select item `CMake Targets View`
2. Select any project and choose `Set as Startup Item`

# Troubleshooting

## CMake Workspace not working

1. Close Visual Studio
1. Delete `.vs` folder
1. Open Workspace

# Personal Notes

## Introduction

### Vulkan API

https://vkguide.dev/docs/introduction/vulkan_overview/

#### Validation Layers

- Validation Layers reduce performance.
- Not good indicator, for it works on all hardware.
- Good for catching errors: incorrect configurations, wrong enums, sync issues, object lifetimes.
- Does not catch bugs like unitizialized memory or bad pointers.

#### Usage and general mindset

- Objects like pipelines are expensive to create (better create offline, than per-frame).
- Some objects like `DescriptorSets` are cheaper.
- All commands are submitted to queue using a `CommandBuffer`.
- Different queues can run in parallel.
- Vulkan has no concept of "frames", it could run in headless-mode.

### Vulkan Usage

https://vkguide.dev/docs/introduction/vulkan_execution/

#### Vulkan main objects and their use

Following concepts are summarized in the previous link:

- `VkInstance` (Vulkan context), 
- `VkPhysicalDevice` (Physical GPU), 
- `VkDevice` (Logical GPU), 
- `VkBuffer` (GPU Memory), 
- `VkImage` (Texture), 
- `VkPipeline` (GPU states)
- `VkRenderPass` (holds Target Image Information, legacy vkguide)
- `VkFrameBuffer` (target image, for render pass. legacy vkguide)
- `VkQueue` (could be graphics, memory, commands)
- `VkDescriptorSet` (GPU-side pointers)
- `VkSwapchainKHR`  (swapchain for the screen (extension: KHR))
- `VkSemaphore` (sync GPU to CPU)
- `VkFence` (sync GPU to CPU, has GPU command finished?)

#### High level Vulkan application flow

##### Engine initialization

1. create `VkInstance`
1. query available `VkPhysicalDevice`
1. assess properties and select suitable `VkPhysicalDevice`
1. create `VkDevice` from selected `VkPhysicalDevice`
1. get `VkQueue` handles from `VkDevice`
1. create `VkCommandPool` objects to use `VkQueue` handles
1. init `VkSwapchainKHR`

##### Asset initialization

- load materials -> `VkPipeline` objects
- meshes -> vertex data to `VkBuffer` objects
- textures -> `VkImage` (readable layout)
- for every pass (main, shadow, depth) -> `VkRenderPass`

##### Render Loop

1. ask `VkSwapchainKHR` for image to render to.
1. create or reuse `VkCommandBuffer` from `VkCommandBufferPool` and start it.
1. begin rendering by starting `VkRenderPass` to image received from `VkSwapchainKHR`.
1. in a loop bind `VkPipeline`, some `VkDescriptorSet`s, vertex buffer and execute a draw call.
1. end `VkRenderPass`. end `VkCommandBuffer` after everything is rendered.
1. use a semaphore to wait until rendering is finished, before presenting to the screen.

The link of this chapter contains pseude-code of the basic render loop.

### Project layout and Libraries

https://vkguide.dev/docs/introduction/project_libs/

#### Project layout

The chapter explains the folder structure of the project.

#### Libraries

- stored in `/third_party`
- SDL is not vendored

Summary of used libraries:

- **GLM**: mathematics, directly compatible with OpenGL and Vulkan
- **SDL**: windowing and inputs: seperatily built, crossplatform
- **dear IMGUI**: GUI library
- **STB Image**: image loading
- **Tiny Obj loader**: loads .obj 3d models
- **Vk Bootstrap**: Vulkan boilerplate abstraction
- **VMA**: vulkan memory allocator

## 0. Project Setup

### Building Project

My notes for this chapter are compiled in an earlier chapter (Project Setup) of this readme.

### Walkthrough

https://vkguide.dev/docs/new_chapter_0/code_walkthrough/

- The site contains short summaries about the .h/cpp files of the project.
- `vk_engine` is the core of the project.
- `vk_main` starting point. starts the engine. could be used to set parameters.
- `VK_CHECK` is a preprocessor macro for printing `VkResult` errors (defined in `vk_types.h`).
- `{fmt} lib` is used instead of `std::cout`
- Parameters for SDL are set in `vk_engine`
- SDL is a C library; SDL objects have to be deleted manually (`VulkanEngine::cleanup`).
- `VulkanEngine::run` in a nutshell so far: call `draw()` until the loop is stopped and not while it is suspended.