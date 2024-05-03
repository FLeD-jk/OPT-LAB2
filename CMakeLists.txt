cmake_minimum_required(VERSION 3.27)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

# Add all necessary source files to the executable
add_executable(Lab2 main.cpp Lexer.cpp Lexer.h Token.cpp Token.h Lexer_scan.cpp Output.cpp
        Lexer.cpp
        Information_Table.cpp
        Parser.h
        Parser.cpp
        Parser.cpp)
