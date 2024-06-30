cmake_minimum_required(VERSION 3.16)
project(test-readwrite)
add_executable(test-readwrite test-readwrite.c)
install(TARGETS test-readwrite DESTINATION bin)
