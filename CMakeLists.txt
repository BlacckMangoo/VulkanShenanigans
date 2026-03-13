cmake_minimum_required( VERSION 3.5)
project(learnVulkan LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Vulkan REQUIRED)

#GLFW 
add_subdirectory(external/glfw)



add_executable(learnVulkan src/main.cpp external/volk/volk.c src/app.cpp )

target_include_directories(learnVulkan PRIVATE include external/glm external/volk/volk.h)

target_link_libraries(learnVulkan PRIVATE Vulkan::Vulkan glfw)