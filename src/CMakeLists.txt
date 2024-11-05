# CMakeList.txt : CMake project for TetrisBD, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
set(SOURCES 
	"main.cpp"
	"application.cpp"
	"game.cpp"
	"renderer.cpp"
	"playfield.cpp"
	"tetromino.cpp"

)
add_executable (TetrisBD ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TetrisBD PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(TetrisBD raylib)