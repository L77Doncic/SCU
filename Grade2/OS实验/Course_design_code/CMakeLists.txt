cmake_minimum_required(VERSION 3.28)
project(Course_design_code)

set(CMAKE_CXX_STANDARD 17)

#设定构建运行路径，避免污染根目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/runtime)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/path)

#遍历项目目录下的.cpp文件，自动添加
file(GLOB_RECURSE file *.c */*.c *.cpp */*.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable(${exe} ${file})
    message(\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ runtime${exe})
endforeach ()

