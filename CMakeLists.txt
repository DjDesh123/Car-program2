cmake_minimum_required(VERSION 3.27)

project(Car-program2)

# this creates the actual executable for the project
add_executable(Car-program2)

#compile the code with the include directory
target_include_directories(Car-program2 PRIVATE include)


# this adds the source files to the executable
target_sources(Car-program2 PRIVATE main.c src/MainMenu.c include/MainMenu.h include/app/CarProgram2.h src/app/CarProgram2.c)

