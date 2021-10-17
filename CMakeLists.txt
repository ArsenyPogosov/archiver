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
        archiver.cpp
        archiver.h
        argumentsparser.cpp
        argumentsparser.h
        binarytrie.cpp
        binarytrie.h
        decoder.cpp
        decoder.h
        encoder.cpp
        encoder.h
        helper.cpp
        helper.h
        huffmantable.cpp
        huffmantable.h
        main.cpp
        priorityqueue.h
        streamwrapper.cpp
        streamwrapper.h
        unarchiver.cpp
        unarchiver.h
        word.h )

add_catch(archiver_test_all
        argumentsparser.cpp
        binarytrie.cpp
        decoder.cpp
        encoder.cpp
        huffmantable.cpp
        streamwrapper.cpp
        tests/test_all.cpp)
