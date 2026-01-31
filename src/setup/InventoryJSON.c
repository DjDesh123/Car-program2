#include "setup/InventoryJSON.h"
#include <cJSON.h>
//TODO: ADD A DIRECTORY AND GET RID OF THE ../
#include "utils/FileManager.h"
#include "../include/setup/DefaultInventory.h"

#define INITIAL_INVENTORY_SIZE 10

int createJsonFile(){

    if (directoryExists("./storage/Inventory.json")) {
        return 0;
    }

    cJSON *root = cJSON_CreateObject();
    cJSON *inventory = cJSON_CreateArray();

    for (int i = 0; i < INITIAL_INVENTORY_SIZE; i++) {
        cJSON *carObj = cJSON_CreateObject();

        cJSON_AddStringToObject(carObj, "make", carInventory[i].name);
        cJSON_AddNumberToObject(carObj, "year", carInventory[i].year);
        cJSON_AddNumberToObject(carObj, "price", carInventory[i].price);
        cJSON_AddNumberToObject(carObj, "quantity", carInventory[i].stock);

        cJSON_AddItemToArray(inventory, carObj);
    }

    cJSON_AddItemToObject(root, "inventory", inventory);


  }