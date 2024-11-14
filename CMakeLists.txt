# CMakeList.txt: pro_homework1 的 CMake 项目

#set required version
cmake_minimum_required(VERSION 3.8)


if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("pro_homework1")


###################
# add source code
#add_library(pro_homework1_lib "gs.cpp" "pro_homework1.h" "gs.h")

add_library(test_shiyunwang_lib "gs.cpp" "pro_homework1.h" "gs.h")
###################

###################
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_shiyunwang_lib PROPERTY CXX_STANDARD 14)
endif()
###################

# import google test 
add_subdirectory("googletest-main" googletest-build)
# add the path of google test
include_directories("googletest-main/googletest/include")

########################
#add the test example and set name
#add_executable(test_pro_homework1 "test.cpp")
#target_link_libraries(test_pro_homework1 pro_homework1_lib gtest gtest_main)
add_executable(test_shiyunwang "test_shiyunwang.cpp")
target_link_libraries(test_shiyunwang test_shiyunwang_lib gtest gtest_main)

########################

###################
# setting the standard of C++
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_shiyunwang PROPERTY CXX_STANDARD 14)
endif()
###################

enable_testing()
########################
# enable the test 
#add_test(NAME test_pro_homework1 COMMAND test_pro_homework1)
add_test(NAME test_shiyunwang COMMAND test_shiyunwang)
########################
# set the MTd to be the same, otherwise there will be conflicts
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

