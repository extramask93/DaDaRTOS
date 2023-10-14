cmake_minimum_required(VERSION 3.14...3.22)

project(DadaRTOS
    VERSION 0.0.1 
    LANGUAGES C)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_library(${PROJECT_NAME} SHARED ${headers} ${sources}
    )
add_compile_options(-Wall -Wextra -Wpedantic)
set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 17
    LINKER_LANGUAGE C)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
                         $<INSTALL_INTERFACE:src/${PROJECT_NAME}-${PROJECT_VERSION}>
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

