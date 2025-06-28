cmake_minimum_required(VERSION 3.27)
project(template)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_PROJECT_NAME}/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

add_executable(${PROJECT_NAME}
        src/main.cpp
)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PRIVATE --embed-file=${CMAKE_SOURCE_DIR}/assets@/assets/ -sALLOW_MEMORY_GROWTH)
else ()
    add_custom_target(copy_assets
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_SOURCE_DIR}/assets"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    )

    add_dependencies(${PROJECT_NAME} copy_assets)
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(BEE_VENDORED OFF)
set(BEE_STATIC OFF)
set(BEE_STATIC_DEPENDENCIES OFF)

add_subdirectory(Bee-Engine)
add_dependencies(${PROJECT_NAME} bee)
target_link_libraries(${PROJECT_NAME} PRIVATE bee)