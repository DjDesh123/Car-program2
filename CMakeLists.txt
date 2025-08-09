cmake_minimum_required(VERSION 3.29)
project(car_program3 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(include/setup)

add_executable(car_program3
        src/main.c
        src/MainMenu.c
        src/Inventory.c
        src/Utils.c
        src/FileManager.c
        src/setup/Bootstrap.c
        src/setup/DefaultInventory.c
)
