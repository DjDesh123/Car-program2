:: to create automation with bash and batch to create a multi os compatible program that checks the files exist and if they do exist to call the needed script
@echo off

:: to check if the file does not exist so we can you temporary data in the defaultInventory.h file
if not exist "Inventory.dat" (
   :: calls the file to input the default data
   DefaultInventory.exe


)else(
  :: to read the file that stores the information back into the struct array
)