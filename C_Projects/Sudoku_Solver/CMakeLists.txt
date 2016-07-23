cmake_minimum_required(VERSION 2.8)

project(Sudoku_Solver C)

# Create targets for local libraries
foreach(lib 
        Utils
        Sudoku
    )
    add_subdirectory(../${lib} ${lib})
    set(EXTRA_LIBS ${EXTRA_LIBS} ${lib})
endforeach(lib)

add_executable(Sudoku_Solver src/main.c)
target_link_libraries(Sudoku_Solver ${EXTRA_LIBS})

