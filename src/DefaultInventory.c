#include <stdio.h>
#include "../include/DefaultInventory.h"
#include "../include/Inventory.h"
#define INITIAL_INVENTORY_SIZE 10


void defaultInventory(){
    car carInventory[INITIAL_INVENTORY_SIZE]={
        {"Toyota", 2017, 2500.00, 10},
        {"Honda", 2019, 2200.00, 15},
        {"Ford", 2020, 3000.00, 8},
        {"BMW", 2018, 3500.00, 5},
        {"Chevrolet", 2021, 2800.00, 12},
        {"Audi", 2016, 4500.00, 3},
        {"Mercedes", 2022, 5000.00, 4},
        {"Nissan", 2017, 2400.00, 18},
        {"Hyundai", 2020, 2300.00, 20},
        {"Kia", 2021, 2600.00, 7}
    };
}