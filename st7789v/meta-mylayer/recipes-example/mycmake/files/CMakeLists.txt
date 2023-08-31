cmake_minimum_required(VERSION 3.16)
project(framebuffer)
add_executable(myfb framebuffer.c)
install(TARGETS myfb DESTINATION bin)
