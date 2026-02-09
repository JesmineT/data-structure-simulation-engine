#ifndef ITEMTREE_H
#define ITEMTREE_H
#include <stdexcept>
#include <iostream>
#include <string>
#include "ShopItem.h"

class ItemTree {
private:
    ShopItem* fKey; // Node's value (ShopItem)
    ItemTree* fLeft; // Left child node
    ItemTree* fRight; // Right child node
    bool purchasable; // Flag to indicate if the item is purchasable

    // Default private constructor (for sentinel node)
    ItemTree();

public:
    // Sentinel to represent an empty node
    static ItemTree NIL;

    // Constructor, initializes fKey and sets left/right to NIL
    ItemTree(ShopItem* aKey);

    // Check if the node is empty
    bool isEmpty() const;

    // Return the key, throws an exception if the node is empty
    ShopItem* key() const;

    // Access methods for left and right children
    ItemTree* left();
    ItemTree* right();

    // Attach left child
    void attachLeft(ItemTree* aTree);

    // Attach right child
    void attachRight(ItemTree* aTree);

    // Detach left child
    ItemTree* detachLeft();

    // Detach right child
    ItemTree* detachRight();

    // Method to display the item tree
    void display(int depth = 0) const;

    // Check if the item is purchasable
    bool isPurchasable() const;

    // Set the item as purchasable
    void setPurchasable(bool status);

    // Mark children as purchasable
    void unlockChildren();

    // Destructor
    ~ItemTree();
};
#endif