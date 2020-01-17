

file(GLOB_RECURSE VMETA_TEST_SOURCES *.cpp *.cc *.cxx)

add_executable(test_all ${VMETA_TEST_SOURCES})

enable_testing()
find_package(GTest CONFIG REQUIRED)
target_link_libraries(test_all PRIVATE GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main)
target_include_directories(test_all PRIVATE "../include")
if(NOT CMAKE_CXX_COMPILER MATCHES MSVC)
target_link_libraries(test_all pthread)
endif()


include(GoogleTest)
gtest_add_tests(test_all "" AUTO)

install(TARGETS test_all LIBRARY DESTINATION "lib" RUNTIME DESTINATION "bin" ARCHIVE DESTINATION "lib")

