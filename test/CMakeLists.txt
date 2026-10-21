add_executable(${MP2_TESTS}
    test_main.cpp
    test_tmatrix.cpp
    test_tvector.cpp
)
target_link_libraries(${MP2_TESTS} PRIVATE ${MP2_LIBRARY} gtest)