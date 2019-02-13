cmake_minimum_required(VERSION 3.12)
project(rubiks3_solve)

set(CMAKE_CXX_STANDARD 14)

include_directories("Xcode/Rubiks Cube Solver")

add_executable(rubiks3_solve
        "Xcode/Rubiks Cube Solver/cmake-build-debug/Choice.mtb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/cmake_install.cmake"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/CMakeCache.txt"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/CrnrPerm.mtb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/CrnrSlic.ptb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/EdgePerm.mtb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/EdgeSlic.ptb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/Flip.mtb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/FlipChce.ptb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/Makefile"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/rubiks3-solve"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/rubiks3-solve.cbp"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/SlicPerm.mtb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/Twist.mtb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/TwstChce.ptb"
        "Xcode/Rubiks Cube Solver/cmake-build-debug/TwstFlip.ptb"
        "Xcode/Rubiks Cube Solver/CMakeLists.txt"
        "Xcode/Rubiks Cube Solver/Combinatorics.cpp"
        "Xcode/Rubiks Cube Solver/Combinatorics.hpp"
        "Xcode/Rubiks Cube Solver/Cube.cpp"
        "Xcode/Rubiks Cube Solver/Cube.hpp"
        "Xcode/Rubiks Cube Solver/CubeDetector.cpp"
        "Xcode/Rubiks Cube Solver/CubeDetector.hpp"
        "Xcode/Rubiks Cube Solver/CubeParser.cpp"
        "Xcode/Rubiks Cube Solver/CubeParser.hpp"
        "Xcode/Rubiks Cube Solver/FaceletCube.cpp"
        "Xcode/Rubiks Cube Solver/FaceletCube.hpp"
        "Xcode/Rubiks Cube Solver/KociMoveTables.hpp"
        "Xcode/Rubiks Cube Solver/main.cpp"
        "Xcode/Rubiks Cube Solver/MoveTable.cpp"
        "Xcode/Rubiks Cube Solver/MoveTable.hpp"
        "Xcode/Rubiks Cube Solver/PruningTable.cpp"
        "Xcode/Rubiks Cube Solver/PruningTable.hpp"
        "Xcode/Rubiks Cube Solver/RubiksCube.cpp"
        "Xcode/Rubiks Cube Solver/RubiksCube.hpp"
        "Xcode/Rubiks Cube Solver/Solver.cpp"
        "Xcode/Rubiks Cube Solver/Solver.hpp"
        "Xcode/Rubiks Cube Solver/Vector.cpp"
        "Xcode/Rubiks Cube Solver/Vector.hpp")
