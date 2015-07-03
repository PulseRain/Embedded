#===========================================================================
# Copyright (c) : Pulserain Technology, LLC. 2015
#===========================================================================
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required (VERSION 3.0)
project (common)
  
add_library(${PROJECT_NAME} OBJECT about.c CRC32.c)

add_custom_target (about_CRC32
  ALL
  COMMAND objdump -s ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/about.c.o | perl ${CMAKE_CURRENT_SOURCE_DIR}/about_sig_CRC32.pl > ${CMAKE_CURRENT_SOURCE_DIR}/include/about_CRC32.h
  DEPENDS ${PROJECT_NAME} 
)

#add_custom_command (
#  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/about_CRC32.h
#  COMMAND objdump -s ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/about.c.o | perl ${CMAKE_CURRENT_SOURCE_DIR}/about_sig_CRC32.pl > ${CMAKE_CURRENT_SOURCE_DIR}/include/about_CRC32.h
#  DEPENDS ${PROJECT_NAME}
#)

include_directories("./include")
