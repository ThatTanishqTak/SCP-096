project(Engine LANGUAGES C CXX)

set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL_DOCS ON CACHE BOOL "" FORCE)

set(SDL_AUDIO OFF CACHE BOOL "" FORCE)
set(SDL_VIDEO ON CACHE BOOL "" FORCE)
set(SDL_RENDER ON CACHE BOOL "" FORCE)
set(SDL_GPU OFF CACHE BOOL "" FORCE)
set(SDL_CAMERA OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI OFF CACHE BOOL "" FORCE)
set(SDL_POWER OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
set(SDL_DIALOG OFF CACHE BOOL "" FORCE)
set(SDL_TRAY OFF CACHE BOOL "" FORCE)

set(SDL_OPENGL ON CACHE BOOL "" FORCE)
set(SDL_OPENGLES OFF CACHE BOOL "" FORCE)
set(SDL_VULKAN OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_VULKAN OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_GPU OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D11 OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D12 OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendor/spdlog)

find_package(OpenGL REQUIRED)

set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c)

file(GLOB_RECURSE ENGINE_SOURCE CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_library(Engine STATIC
    ${ENGINE_SOURCE}
    ${GLAD_SOURCE}
)
add_library(Engine::Engine ALIAS Engine)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${GLAD_INCLUDE_DIR}
)

target_link_libraries(Engine PUBLIC
    SDL3::SDL3
    spdlog::spdlog
    OpenGL::GL
)

if(MSVC)
    target_compile_options(Engine PRIVATE
        /W4
        $<$<BOOL:${ENABLE_ASAN}>:/fsanitize=address>
    )

    target_link_options(Engine PRIVATE
        $<$<BOOL:${ENABLE_ASAN}>:/fsanitize=address>
    )
else()
    target_compile_options(Engine PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
        $<$<BOOL:${ENABLE_ASAN}>:-fno-omit-frame-pointer>
        $<$<BOOL:${ENABLE_UBSAN}>:-fsanitize=undefined>
    )

    target_link_options(Engine PRIVATE
        $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
        $<$<BOOL:${ENABLE_UBSAN}>:-fsanitize=undefined>
    )
endif()