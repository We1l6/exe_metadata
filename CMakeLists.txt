	cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
	
	project(exe_metadata LANGUAGES CXX) 
	add_executable(main src/main.cpp)
	set(CMAKE_BUILD_TYPE Release)

	add_subdirectory(libs/gtest/googletest)
	include_directories(libs/gtest/googletest/googletest/include)
	add_executable(MyTest test/test.cpp)
	target_link_libraries(MyTest gtest_main)