# CMakeList.txt: pro_homework1 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("pro_homework1")

# 将源代码添加到此项目的库文件（而不是可执行文件）
add_library(pro_homework1_lib "gs.cpp" "pro_homework1.h" "gs.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pro_homework1_lib PROPERTY CXX_STANDARD 20)
endif()

# 引入GoogleTest库
add_subdirectory("googletest-main" googletest-build)
# 添加包含路径
include_directories("googletest-main/googletest/include")

# 添加测试
add_executable(test_pro_homework1 "test.cpp")
target_link_libraries(test_pro_homework1 pro_homework1_lib gtest gtest_main)

# 设置测试目标的 C++ 标准
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_pro_homework1 PROPERTY CXX_STANDARD 20)
endif()

# 启用测试
enable_testing()
add_test(NAME test_pro_homework1 COMMAND test_pro_homework1)

# TODO: 如有需要，请添加安装目标。
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

