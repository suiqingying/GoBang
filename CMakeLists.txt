cmake_minimum_required(VERSION 3.5.0)
project(Gobang VERSION 0.1.0 LANGUAGES C)

# 使用 pkg-config 查找 SDL2 和 SDL2_ttf 库
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# 包含 SDL2 和 SDL2_ttf 的头文件路径
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# 添加可执行文件
add_executable(Gobang draw.c evaluation.c judge.c main.c search.c)

# 链接 SDL2 和 SDL2_ttf 库
target_link_libraries(Gobang ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})