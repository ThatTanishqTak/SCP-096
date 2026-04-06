project(Game LANGUAGES CXX)

file(GLOB_RECURSE GAME_SOURCE CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(Game ${GAME_SOURCE})

target_include_directories(Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Game PRIVATE
    Engine::Engine
)

if(MSVC)
    target_compile_options(Game PRIVATE
        /W4
        $<$<BOOL:${ENABLE_ASAN}>:/fsanitize=address>
    )

    target_link_options(Game PRIVATE
        $<$<BOOL:${ENABLE_ASAN}>:/fsanitize=address>
    )
else()
    target_compile_options(Game PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
        $<$<BOOL:${ENABLE_ASAN}>:-fno-omit-frame-pointer>
        $<$<BOOL:${ENABLE_UBSAN}>:-fsanitize=undefined>
    )

    target_link_options(Game PRIVATE
        $<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>
        $<$<BOOL:${ENABLE_UBSAN}>:-fsanitize=undefined>
    )
endif()