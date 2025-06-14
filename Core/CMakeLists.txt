cmake_minimum_required(VERSION 3.20)
project(LHCraftCoreLib VERSION 1.0)

if(APPLE)
    set(OPENGL_VERSION_MAJOR 4)
    set(OPENGL_VERSION_MINOR 1)
endif()

configure_file(
    cmakeConfig.h.in
    cmakeConfig.h
)

add_library(Core STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glad/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/stb_image/stb_image/stb_image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui/imgui/misc/cpp/imgui_stdlib.cpp
    src/Core/UI/ImguiBuild.cpp 
    src/Core/Application/Application.cpp
    src/Core/Window/Window.cpp
    src/Core/Logging/Logging.cpp
    src/Core/Layers/Layer.cpp
    src/Core/Layers/LayerStack.cpp
    src/Core/Input/Input.cpp
    src/Core/Renderer/Context/GraphicsContext.cpp
    src/Core/Renderer/Platform/OpenGLContext.cpp
    src/Core/Renderer/Platform/OpenGLShader.cpp
    src/Core/Renderer/Platform/OpenGLBuffers.cpp
    src/Core/Renderer/Platform/OpenGLVertexArray.cpp
    src/Core/Renderer/Shader/Shader.cpp
    src/Core/Renderer/Buffers.cpp
    src/Core/Renderer/VertexArray.cpp
    src/Core/Renderer/RendererAPI.cpp
    src/Core/Renderer/Renderer.cpp
    src/Core/Renderer/RenderCommands.cpp
    src/Core/Renderer/Platform/OpenGLRendererAPI.cpp
    src/Core/Camera/ProjectionCamera.cpp
    src/Core/Renderer/Texture.cpp
    src/Core/Renderer/Platform/OpenGlTexture2D.cpp
    src/Core/UI/ImguiLayer.cpp
)

# exposes the header PUBLICLY so the compiler can resolve the include
target_include_directories(Core PUBLIC 
    ${CMAKE_BINARY_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glfw
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/stb_image
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/imgui
)

target_precompile_headers(Core PUBLIC
    $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/Core/LHCpch.h>
)

# Target link libs seems to need to be specified with PUBLIC/PRIVATE/INTERFACE or none at all
target_link_libraries(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glfw/glfw/libglfw3.a
)

if (APPLE)
    target_link_libraries(Core PUBLIC "-framework IOKit")
    target_link_libraries(Core PUBLIC "-framework Cocoa")
    target_link_libraries(Core PUBLIC "-framework OpenGL")
endif()

add_custom_target(CopyShaders ALL
  COMMENT "Copying Shaders → ${CMAKE_BINARY_DIR}/Shaders"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
    "${CMAKE_BINARY_DIR}/Core/Shaders"
)

add_dependencies(Core CopyShaders)

target_compile_definitions(Core PUBLIC
    LHCRAFT_ENABLE_ASSERTS
    GL_SILENCE_DEPRECATION
)
