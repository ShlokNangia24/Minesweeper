cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
project(Minesweeper)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(minesweeper main.cpp Toolbox.h Button.cpp Button.h Tile.h Tile.cpp GameState.cpp GameState.h minesweeper.h Smiley.h)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
