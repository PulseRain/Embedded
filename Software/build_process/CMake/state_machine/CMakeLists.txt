cmake_minimum_required (VERSION 3.0)
project (state_machine)
 
# add the executable
add_library(${PROJECT_NAME} OBJECT state_machine.c)

include_directories("../common/include")