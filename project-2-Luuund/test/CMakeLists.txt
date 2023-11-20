
# We create a test driver executable
add_executable(test_game_of_lines test_game_of_lines.c)
# We link the library to the test driver
target_link_libraries(test_game_of_lines game_of_lines)

# We add the test executable to CTest
add_test(NAME test_game_of_lines COMMAND test_game_of_lines)
