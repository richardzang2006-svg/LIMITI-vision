cmake_minimum_required(VERSION 3.5)
project(LIMITI-vision)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# 查找OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 创建可执行文件
add_executable(run test.cpp)

# 链接OpenCV库
target_link_libraries(run ${OpenCV_LIBS})

# 启用测试
enable_testing()
add_test(NAME MyTest COMMAND run)
