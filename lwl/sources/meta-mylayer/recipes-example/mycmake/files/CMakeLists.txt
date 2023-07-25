cmake_minimum_required(VERSION 3.16)
project(hello)
add_executable(userprog userprog.c)
install(TARGETS userprog DESTINATION bin)
