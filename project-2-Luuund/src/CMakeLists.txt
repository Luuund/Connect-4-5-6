
# We create a library for the functions in our game
add_library(game_of_lines game_of_lines.c)
# Make header files in the current folder for #include
target_include_directories(game_of_lines PUBLIC .)

# We create an executable to run the game
add_executable(play_game play_game.c)
# We link our library to the game executable, so the executable can access the functions in the library.
target_link_libraries(play_game game_of_lines)
