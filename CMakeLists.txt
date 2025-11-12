cmake_minimum_required(VERSION 3.5)
project(LIMITI-vision)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wl,--no-as-needed")

# 查找OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 创建可执行文件
add_executable(run test.cpp)

# 链接OpenCV库
target_link_libraries(run ${OpenCV_LIBS})

# 启用测试
enable_testing()

# 获取环境变量，如果没有设置就用默认值
set(TEST_DISPLAY "$ENV{DISPLAY}")
if(NOT TEST_DISPLAY)
    set(TEST_DISPLAY ":0")
endif()

set(TEST_LD_LIBRARY_PATH "$ENV{LD_LIBRARY_PATH}")
if(NOT TEST_LD_LIBRARY_PATH)
    set(TEST_LD_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu:/usr/local/lib")
endif()

# 创建测试并设置环境
add_test(NAME MyTest COMMAND ${CMAKE_BINARY_DIR}/run)
set_tests_properties(MyTest PROPERTIES
    ENVIRONMENT "DISPLAY=${TEST_DISPLAY};LD_LIBRARY_PATH=${TEST_LD_LIBRARY_PATH}"
)
