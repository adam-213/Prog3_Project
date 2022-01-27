cmake_minimum_required(VERSION 3.16)
project(Project)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

#add_executable(Project main.cpp main.h ItemTests.cpp Item.cpp Item.h Date.h Date.cpp DateTests.cpp)


set(
        SOURCE_FILES
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc

        Tests/ItemTests.cpp Kod/Item.cpp Headers/Item.h

        Headers/Date.h Kod/Date.cpp
        Kod/Date_Operators.cpp Kod/Date_Static.cpp
        Tests/Date_Static_Tests.cpp Tests/Date_Tests.cpp

        Headers/FileOps.h Kod/FileOps.cpp

        Headers/Fridge.h Kod/Fridge.cpp Kod/Fridge_put.cpp
        Tests/Fridge_Base_Tests.cpp

        Kod/Orders.cpp Headers/Orders_Generators.h
        Tests/Orders_Tests.cpp

        Headers/Shelf.h Kod/Shelf.cpp
        Tests/Shelf_Tests.cpp
        Tests/FileOps_Tests.cpp)


include_directories(GoogleTest)
add_executable(Project ${SOURCE_FILES})
target_link_libraries(Project ${CMAKE_THREAD_LIBS_INIT})