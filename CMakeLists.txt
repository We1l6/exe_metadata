	cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
	
	project(exe_metadata LANGUAGES CXX) 
	add_executable(main src/main.cpp)
	set(CMAKE_BUILD_TYPE Release)