cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

#add_executable(Project main.cpp main.h ItemTests.cpp Item.cpp Item.h Date.h Date.cpp DateTests.cpp)


set(SOURCE_FILES
        #main.cpp main.h
        ItemTests.cpp Item.cpp Item.h
        Date.h Date.cpp DateTests.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc Date_Operators.cpp Date_Static.cpp FileOps.h FileOps.cpp Orders.h Fridge.h Orders.cpp Fridge.cpp Date_Static_Tests.cpp)



include_directories(GoogleTest)
add_executable(Project ${SOURCE_FILES})
target_link_libraries(Project ${CMAKE_THREAD_LIBS_INIT})