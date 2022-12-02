cmake_minimum_required(VERSION 3.24)
project(box_breaker)

set(CMAKE_CXX_STANDARD 17)

add_executable(box_breaker main.cpp game/BoxBreakerGame.h game/Game.cpp)

set(EXT_DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extDeps)

# GLFW
set(GLFW_DIR ${EXT_DEPS_DIR}/glfw)
set(GLFW_INC_DIR ${GLFW_DIR}/include)

# GLAD
set(GLAD_DIR ${EXT_DEPS_DIR}/glad)
set(GLAD_INC_DIR ${GLAD_DIR}/include)

# ENTT
set(ENTT_INC_DIR ${EXT_DEPS_DIR}/entt/include)


# Linking all together
add_subdirectory(${GLAD_DIR})
add_subdirectory(${GLFW_DIR})


find_package(OpenGL REQUIRED)

target_link_libraries(box_breaker PRIVATE glfw OpenGL::GL glad)
target_include_directories(box_breaker PRIVATE ${GLFW_INC_DIR} ${GLAD_INC_DIR} ${ENTT_INC_DIR})
