# CMakeList.txt : CMake project for VMeta, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)
project(VMeta)

option(VMETA_BUILD_TESTS "Set ON to build test" OFF)

# Add source to this project's executable.

find_package(Git)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive)



if(VMETA_BUILD_TESTS)
add_subdirectory(test)
endif()

# TODO: Add tests and install targets if needed.
