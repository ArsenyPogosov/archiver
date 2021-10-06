cmake_minimum_required(VERSION 3.13)
project(archiver)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(archiver main.cpp streamwrapper.cpp huffmantable.h huffmantable.cpp encoder.cpp encoder.h decoder.h decoder.cpp binarytrie.h binarytrie.cpp archiver.h archiver.cpp priorityqueue.tcc priorityqueue.h)
add_catch(archiver_test_streamwrapper streamwrapper.cpp tests/test_streamwrapper.cpp)
add_catch(archiver_test_huffmantable huffmantable.cpp tests/test_huffmantable.cpp)
add_catch(archiver_test_binarytrie binarytrie.cpp tests/test_binarytrie.cpp)
add_catch(archiver_test_priorityqueue tests/test_priorityqueue.cpp)
add_catch(archiver_test_encoder_decoder binarytrie.cpp decoder.cpp encoder.cpp huffmantable.cpp streamwrapper.cpp tests/test_encoder_decoder.cpp)

