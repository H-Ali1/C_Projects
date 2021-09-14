cmake_minimum_required(VERSION 3.17)
project(c_packetSniffer C)

set(CMAKE_BUILD_TYPE Debug)



set(GCC_COVERAGE_LINK_FLAGS    "-lpcap")
set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")
set(CMAKE_C_FLAGS "-D_BSD_SOURCE")


include(WpdPack/FindPCAP.cmake)
find_package(PCAP REQUIRED)
target_link_libraries(c_packetSniffer ${PCAP_LIBRARY})
add_executable(c_packetSniffer main.c)