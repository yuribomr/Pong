cmake_minimum_required(VERSION 3.15)
project(SIMULATOR VERSION 1.0)

# Config c++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# baixar raylib
include(FetchContent)
FetchContent_Declare(
	raylib
	URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)

# Configurações para a raylib (desativa testes e exemplos para compilar rápido)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

#adicionar executavel
add_executable(${PROJECT_NAME} main.cpp)

#Linkar raylib com libs do sistema
target_link_libraries(${PROJECT_NAME} raylib)
