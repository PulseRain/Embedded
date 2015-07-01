cmake_minimum_required (VERSION 2.6)
project (align)
 
# add the executable
add_library(archive OBJECT align.c)



include_directories("../common/include")
