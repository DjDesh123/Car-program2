cmake_minimum_required(VERSION 3.29)

#project name and language
project(car_program3 C)

#uses C11 standard
set(CMAKE_C_STANDARD 11)

#this builds the actual car program executable
add_executable(car_program3
        src/main.c
        src/MainMenu.c
        src/inventory/Inventory.c
        src/utils/Utils.c
        src/utils/FileManager.c
        src/setup/Bootstrap.c
        src/setup/DefaultInventory.c
        src/setup/InventoryJSON.c
        third_party/cjson/cJSON.c
)

#tells CMake where this target should look for header files
target_include_directories(car_program3 PRIVATE
        include
        third_party/cjson
)

#separate executables for unit testing directoryExists()
add_executable(directory_exists_test
        tests/DirectoryExistsTest.c
        src/utils/FileManager.c
)

#tests for CheckBackupFilesTest
add_executable(check_backup_files_test
        tests/CheckBackupFilesTest.c
)

#gives the test access to the project headers
target_include_directories(directory_exists_test PRIVATE
        include
)

#gives the test acess to the project headers if needed
target_include_directories(check_backup_files_test PRIVATE
        include
)