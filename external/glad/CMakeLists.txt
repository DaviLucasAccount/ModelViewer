cmake_minimum_required(VERSION 3.25)

project(glad LANGUAGES C)

add_library(glad STATIC)

target_sources(glad
    PRIVATE
        src/glad.c
)

target_include_directories(glad
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_library(glad::glad ALIAS glad)
