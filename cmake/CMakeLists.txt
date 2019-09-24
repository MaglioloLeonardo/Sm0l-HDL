cmake_minimum_required(VERSION 3.10)
project(circuiti)

set(CMAKE_CXX_STANDARD 14)

add_library(Component  ../src/Flip_Flop.h  ../src/Flip_Flop.cpp ../src/In_Out.h ../src/In_Out.cpp)

add_library(Components_List ../src/Components_List.h ../src/Components_List.cpp)

add_library(Circuit  ../src/Circuit.h ../src/Circuit.cpp)

#----------------------------------------------------------------------

add_executable(circuito ../src/main.cpp)

target_link_libraries(circuito Component Components_List Circuit)

set_target_properties(circuito PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../out")