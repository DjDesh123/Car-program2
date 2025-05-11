#!/bin/bash

# Display purpose
echo "Checking for Inventory.dat..."

# If Inventory.dat does NOT exist
if [ ! -f "Inventory.dat" ]; then
    echo "Inventory.dat not found. Loading default inventory..."
    ./DefaultInventory

else
    echo "Inventory.dat found. Proceeding to load saved inventory..."
    # ./LoadInventory will be created when this scenario is ready
fi
