cmake_minimum_required(VERSION 3.17)
project(mini_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(src
        googletest-master/googlemock/include
        googletest-master/googletest/include)

# sources
set(SOURCE_FILES src/)

# unit tests
set(TEST_SOURCES test/main_test.cpp test/test_matrix.cpp test/test_vector.cpp)

#add and link Google Test library
add_subdirectory(googletest-master)
link_libraries(gmock)

# add running config
add_executable(config_run ${SOURCE_FILES} src/main.cpp)

# add unit test config
add_executable(config_test ${SOURCE_FILES} ${TEST_SOURCES})