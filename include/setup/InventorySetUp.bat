:: to create automation with bash and batch to create a multi os compatable program that checks the files exist and if they do exist to call the needed script
@echo off

:: to check if the file does not exist so we can you temporary data in the defaultInventory.h file
if not exist "Inventory.dat" (


)else(
  :: to read the file that stores the infomation back into the struct array
)