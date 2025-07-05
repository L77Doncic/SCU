cmake_minimum_required(VERSION 3.28)
project(The_fourth_course_design)

set(CMAKE_CXX_STANDARD 17)

add_executable(The_fourth_course_design main.cpp)

add_executable(memoryAlloc Test4_code/memoryAlloc.cpp)
add_executable(virtumem Test4_code/virtumem.cpp)

add_executable(teamwork1 teamwork/teamwork1.cpp)
add_executable(teamwork2 teamwork/teamwork2.cpp)
add_executable(mine_choose mine_choose.cpp)
add_executable(main main.cpp)