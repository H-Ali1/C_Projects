cmake_minimum_required(VERSION 2.8)

project(ed19h6a C)


set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")


add_executable(run src/main.c src/book_management.h src/user.h src/user_management.c users.txt src/book_management.c src/loans.c src/loans.h)

