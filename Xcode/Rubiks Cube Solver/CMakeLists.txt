cmake_minimum_required(VERSION 3.12)
project(rubiks3-solve)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(OpenCV REQUIRED )

INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )

add_executable(rubiks3-solve main.cpp Combinatorics.cpp Combinatorics.hpp Cube.cpp Cube.hpp CubeParser.cpp
        CubeParser.hpp FaceletCube.cpp FaceletCube.hpp KociMoveTables.hpp MoveTable.cpp MoveTable.hpp
        PruningTable.cpp PruningTable.hpp RubiksCube.cpp RubiksCube.hpp Solver.cpp Solver.hpp Vector.cpp Vector.hpp
        CubeDetector.cpp CubeDetector.hpp)

TARGET_LINK_LIBRARIES(rubiks3-solve ${OpenCV_LIBS})