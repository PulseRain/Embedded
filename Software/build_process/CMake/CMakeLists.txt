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
project (demo)
  

add_definitions(-DVMAJOR=1)
add_definitions(-DVMINOR=3g)
add_definitions("-DPRODUCT_NAME=A SUPER Product")

add_definitions(-DCONFIG_CHECK_ABOUT_SIGNATURE)
add_definitions(-DCONFIG_ENABLE_ALIGNMENT_MODULE)
add_definitions(-DCONFIG_ENABLE_STATE_MACHINE_MODULE)

add_subdirectory(align)
add_subdirectory(common)
add_subdirectory(state_machine)
add_subdirectory(main)

add_dependencies(main common)
add_dependencies(main about_CRC32)

set(CMAKE_C_FLAGS  "-O3")

add_executable(demo $<TARGET_OBJECTS:main> $<TARGET_OBJECTS:common> $<TARGET_OBJECTS:align> $<TARGET_OBJECTS:state_machine>)


