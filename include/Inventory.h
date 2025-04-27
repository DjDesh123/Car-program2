#ifndef INVENTORY_H
#define INVENTORY_H

//defines the size of the initial struct array
#define INITIAL_NAME_SIZE 50

//first need to create a struct for handling the specifications of the cars
typedef struct {
  char name[INITIAL_NAME_SIZE];
  int year;
  float price;
  int stock;
} car;




#endif //INVENTORY_H
