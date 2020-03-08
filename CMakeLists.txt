cmake_minimum_required(VERSION 3.15)
project(VulcanDemo)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "/machine:x64")

aux_source_directory(. SRC_FILES)

include_directories(D:/Library/glfw-3.3/include/)
include_directories(D:/Library/glm-0.9.9.6/glm/)
include_directories(C:/VulkanSDK/1.2.131.2/Include)


link_libraries(D:/Library/Libs/glfw3_64.lib)

link_directories(C:/VulkanSDK/1.2.131.2/Lib)
link_libraries(C:/VulkanSDK/1.2.131.2/Lib/vulkan-1.lib)



add_executable(VulcanDemo ${SRC_FILES})