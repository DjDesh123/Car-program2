cmake_minimum_required(VERSION 3.27)

project(Car-program2 C)

# this creates the actual executable for the project
add_executable(Car-program2)

#compile the code with the include directory
target_include_directories(Car-program2 PRIVATE include include/app include/utils include/setup include/inventory)


# this adds the source files to the executable
target_sources(
Car-program2 PRIVATE 
src/main.c
src/MainMenu.c
src/app/CarProgram2.c 
src/utils/Utils.c
src/setup/Bootstrap.c
src/inventory/inventory.c
src/utils/FileManager.c
)

