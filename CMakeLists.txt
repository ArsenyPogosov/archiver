cmake_minimum_required(VERSION 3.13)
project(archiver)

set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include(cmake/BuildFlags.cmake)
include(cmake/TestSolution.cmake)

find_package(Catch REQUIRED)

include_directories(util)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(archiver
        main.cpp
        argumentsparser.cpp
        argumentsparser.h
        streamwrapper.cpp
        streamwrapper.h
        huffmantable.cpp
        huffmantable.h
        encoder.cpp
        encoder.h
        decoder.cpp
        decoder.h
        binarytrie.cpp
        binarytrie.h
        archiver.h
        archiver.cpp
        priorityqueue.h )

add_catch(archiver_test_all
        argumentsparser.cpp
        streamwrapper.cpp
        huffmantable.cpp
        encoder.cpp
        decoder.cpp
        binarytrie.cpp
        tests/test_all.cpp)


add_catch(archiver_test_argumentsparser
        argumentsparser.cpp
        tests/test_argumentsparser.cpp)