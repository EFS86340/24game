cmake_minimum_required(VERSION 3.8)
project(24game)     # by default, here cmake defined 2 vars: <projectname>_BINARY_DIR and <projectname>_SOURCE_DIR

ADD_SUBDIRECTORY(src bin)
# ADD_SUBDIRECTORY grammar:
#       ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)

message(status "this is BINARY DIR " ${24game_BINARY_DIR})
message(status "this is SOURCE DIR " ${24game_SOURCE_DIR})
#   MESSAGE grammar:
#       MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ... )
# in-source-build
#   would generate some middle files which cannot be deleted automatically,tmp files >>> target files
# out-of-source-build
