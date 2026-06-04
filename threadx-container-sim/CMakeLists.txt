cmake_minimum_required(VERSION 3.20)

project(threadx_container_sim C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(THREADX_ARCH "linux" CACHE STRING "ThreadX port architecture for container simulation")
set(THREADX_TOOLCHAIN "gnu" CACHE STRING "ThreadX toolchain for container simulation")
set(THREADX_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/threadx" CACHE PATH "Path to the ThreadX source tree")

if(NOT EXISTS "${THREADX_ROOT}/CMakeLists.txt")
    message(FATAL_ERROR "ThreadX source tree was not found. Run the Docker build or clone ThreadX into ${THREADX_ROOT}.")
endif()

add_subdirectory("${THREADX_ROOT}" "${CMAKE_BINARY_DIR}/threadx")

add_executable(threadx_sim
    app/demo_threadx_sim.c
)

target_include_directories(threadx_sim PRIVATE
    "${THREADX_ROOT}/common/inc"
    "${THREADX_ROOT}/ports/linux/gnu/inc"
)

target_link_libraries(threadx_sim PRIVATE
    threadx
    pthread
)
