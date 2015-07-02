cmake_minimum_required (VERSION 3.0)
project (common)
  
add_library(${PROJECT_NAME} OBJECT about.c CRC32.c)

add_custom_target (about_CRC32.h
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
