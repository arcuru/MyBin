cmake_minimum_required(VERSION 2.8)

project(Euler C)

# Find all Euler source files
file(GLOB euler_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

# Save the extra libraries to a var
set (EXTRA_LIBS -pthread -lgomp -lgmp -lm)

# Create targets for local libraries
foreach(lib 
        Utils
        Sudoku
        Sort
        Primes
        NumberTheory
    )
    add_subdirectory(../${lib} ${lib})
    set(EXTRA_LIBS ${EXTRA_LIBS} ${lib})
endforeach(lib)

add_executable(Euler ${euler_SRC})
target_include_directories(Euler PUBLIC inc)
target_link_libraries(Euler ${EXTRA_LIBS})

