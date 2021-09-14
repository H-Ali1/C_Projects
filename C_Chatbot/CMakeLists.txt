#change this if you happen to be working with a lower version of CMake
cmake_minimum_required(VERSION 2.8)

project(comp1921_cw2 C)

#change this to Release to activate optimization and compile without debug symbols
set(CMAKE_BUILD_TYPE Debug)

include_directories(unity/include)

#adds arbitrary flags to the compiler.
#this one is used to generate the files we give in input 
set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")

# main program executable
add_executable(run src/main.c src/preProcessing.c src/preProcessing.h src/chatbotLogic.c src/chatbotLogic.h src/fileReadWrite.c src/fileReadWrite.h)
target_link_libraries(run m)

#executable for the unit testing
add_executable(unit_tests  src/unit_tests.c src/preProcessing.c src/fileReadWrite.c src/chatbotLogic.c unity/src/unity.c)
target_link_libraries(unit_tests m)