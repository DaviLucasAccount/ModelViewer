cmake_minimum_required(VERSION 3.25)

project(ModelViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)
add_subdirectory(external/assimp EXCLUDE_FROM_ALL)
add_subdirectory(external/glad EXCLUDE_FROM_ALL)

set(SOURCES
    src/application.cpp
    src/shader.cpp
    src/vertexArray.cpp
    src/vertexBuffer.cpp
    src/indexBuffer.cpp
    src/model.cpp
    src/camera.cpp

    src/main.cpp
)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        glm::glm
        assimp::assimp
        glad::glad
        OpenGL::GL
)

add_custom_target(resources ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
    COMMENT "Copying resources into binary directory"
)

add_dependencies(${PROJECT_NAME} resources)
