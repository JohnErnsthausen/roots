project(roots)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/googlemock/include $ENV{GMOCK_HOME}/googletest/include)
link_directories($ENV{GMOCK_HOME}/mybuild/googlemock $ENV{GMOCK_HOME}/mybuild/googlemock/gtest)
add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g -O2 -Wall -ansi -pedantic -Wc++11-compat")

set(sStub main.cpp rpolytest.cpp)
add_executable(tStub ${sStub})
target_link_libraries(tStub pthread)
target_link_libraries(tStub gtest)

set(sources main.cpp rootstest.cpp)
add_executable(test ${sources})
target_link_libraries(test pthread)
target_link_libraries(test gtest)

set(sAkiti main.cpp akititest.cpp)
add_executable(tAkiti ${sAkiti})
target_link_libraries(tAkiti pthread)
target_link_libraries(tAkiti gtest)

