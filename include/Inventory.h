#ifndef INVENTORY_H
#define INVENTORY_H

//defines the size of the inital struct array
#define INITIAL_NAME_SIZE 50

//first need to create a struct for handling the specifications of the cars
typedef struct {
  char name[INITIAL_NAME_SIZE];
  int year;
  float price;
  int stock
} car;

// points to carInventory which will be used in inventory.c file
car* carInventory;


#endif //INVENTORY_H
