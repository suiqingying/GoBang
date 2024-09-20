cmake_minimum_required(VERSION 3.5.0)
project(GoBang VERSION 0.1.0 LANGUAGES C)

# 查找 SDL2 库
find_package(SDL2 REQUIRED)

# 添加可执行文件
add_executable(GoBang main.c draw.c search.c evaluation.c) 

# 链接 SDL2 库
target_link_libraries(GoBang SDL2::SDL2)