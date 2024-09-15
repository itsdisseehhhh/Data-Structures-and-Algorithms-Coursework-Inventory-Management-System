#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <iomanip>

using namespace std;

// Structure for each item in the inventory
struct Item {
    string name;
    int quantity;
    double price;
    int reorderLevel;
};

// Class to handle the entire inventory
class Inventory {
private:
    // Array for storing items in a fixed size
    Item items[100];
    int itemCount;

    // Hash table for mapping item names to indices for quick lookup
    unordered_map<string, int> itemLookup;

    // Queue for managing automated reorder requests
    queue<string> reorderQueue;

public:
    Inventory() : itemCount(0) {}

    // Function to add an item to the inventory
    void addItem(const string& name, int quantity, double price, int reorderLevel) {
        if (itemCount < 100) {
            items[itemCount] = {name, quantity, price, reorderLevel};
            itemLookup[name] = itemCount;
            itemCount++;
            cout << name << " has been added to the inventory.\n";
        } else {
            cout << "Inventory is full!\n";
        }
    }

    // Function to update the quantity of an item in real time
    void updateItemQuantity(const string& name, int newQuantity) {
        auto it = itemLookup.find(name);
        if (it != itemLookup.end()) {
            int index = it->second;
            items[index].quantity = newQuantity;
            cout << "Updated " << name << " quantity to " << newQuantity << ".\n";

            // Check if reorder is needed
            if (newQuantity <= items[index].reorderLevel) {
                reorderQueue.push(name);
                cout << name << " added to reorder queue.\n";
            }
        } else {
            cout << "Item not found!\n";
        }
    }


    // Processing reorder queue
    void processReorders() {
        while (!reorderQueue.empty()) {
            string itemName = reorderQueue.front();
            reorderQueue.pop();
            auto it = itemLookup.find(itemName);
            if (it != itemLookup.end()) {
                int index = it->second;
                items[index].quantity += 50; // Restocking by 50 units
                cout << itemName << " restocked by 50 units.\n";
            } else {
                cout << "Error processing reorder for " << itemName << "\n";
            }
        }
    }

    // Display inventory items
    void displayInventory() const {
        cout << "Current Inventory:\n";
        for (int i = 0; i < itemCount; i++) {
            cout << "Item: " << items[i].name
                 << ", Quantity: " << items[i].quantity
                 << ", Price: $" << fixed << setprecision(2) << items[i].price
                 << ", Reorder Level: " << items[i].reorderLevel << "\n";
        }
    }
};

// Main function for interacting with the system
int main() {
    Inventory inventory;
    int choice;

    while (true) {
        cout << "\nInventory Management System\n";
        cout << "1. Add Item\n";
        cout << "2. Update Item Quantity\n";
        cout << "3. Process Reorders\n";
        cout << "4. Display Inventory\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int quantity, reorderLevel;
            double price;
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter item quantity: ";
            cin >> quantity;
            cout << "Enter item price: ";
            cin >> price;
            cout << "Enter reorder level: ";
            cin >> reorderLevel;
            inventory.addItem(name, quantity, price, reorderLevel);
        } else if (choice == 2) {
            string name;
            int quantity;
            cout << "Enter item name to update: ";
            cin >> name;
            cout << "Enter new quantity: ";
            cin >> quantity;
            inventory.updateItemQuantity(name, quantity);
        } else if (choice == 3) {
            inventory.processReorders();
        } else if (choice == 4) {
            inventory.displayInventory();
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
