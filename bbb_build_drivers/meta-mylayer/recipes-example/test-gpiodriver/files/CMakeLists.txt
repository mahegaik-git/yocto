cmake_minimum_required(VERSION 3.16)
project(test-gpiodriver)
add_executable(test-gpiodriver test-gpiodriver.c)
install(TARGETS test-gpiodriver DESTINATION bin)

