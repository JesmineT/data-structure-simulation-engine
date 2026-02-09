#include "ItemTree.h"

// Default private constructor (for sentinel node)
ItemTree::ItemTree() : fKey(nullptr), fLeft(nullptr), fRight(nullptr), purchasable(false) {}

// Constructor initializes fKey and sets left/right to NIL
ItemTree::ItemTree(ShopItem* aKey) : fKey(aKey), fLeft(&NIL), fRight(&NIL), purchasable(false) {}

// Check if the node is empty
bool ItemTree::isEmpty() const {
    return this == &NIL;
}

// Return the key, throws an exception if the node is empty
ShopItem* ItemTree::key() const {
    if (isEmpty())
        throw std::domain_error("Empty node!");
    return fKey;
}

// Access methods for left child
ItemTree* ItemTree::left() {
    if (isEmpty())
        throw std::domain_error("Empty Item Tree");
    return fLeft; // Return left child
}

// Access methods for right child
ItemTree* ItemTree::right() {
    if (isEmpty())
        throw std::domain_error("Empty Item Tree");
    return fRight; // Return right child
}

// Attach left child
void ItemTree::attachLeft(ItemTree* aTree) {
    if (isEmpty())
        throw std::domain_error("Empty Item Tree");
    if (fLeft != &NIL)
        throw std::domain_error("Non-empty left subtree");
    fLeft = aTree;
}

// Attach right child
void ItemTree::attachRight(ItemTree* aTree) {
    if (isEmpty())
        throw std::domain_error("Empty Item Tree");
    if (fRight != &NIL)
        throw std::domain_error("Non-empty right subtree");
    fRight = aTree;
}

// Detach left child
ItemTree* ItemTree::detachLeft() {
    if (isEmpty())
        throw std::domain_error("Empty Item Tree");
    ItemTree* temp = fLeft;
    fLeft = &NIL; // Set left to NIL
    return temp; // Return the detached node
}

// Detach right child
ItemTree* ItemTree::detachRight() {
    if (isEmpty())
        throw std::domain_error("Empty Item Tree");
    ItemTree* temp = fRight;
    fRight = &NIL; // Set right to NIL
    return temp; // Return the detached node
}

// Method to display the item tree
void ItemTree::display(int depth) const {
    if (!isEmpty()) {
        std::cout << std::string(depth, ' ') << key()->getName() << " (Cost: " << key()->getCost() << ")\n";
        if (fLeft && fLeft != &NIL) {
            fLeft->display(depth + 2); // Display left child
        }
        if (fRight && fRight != &NIL) {
            fRight->display(depth + 2); // Display right child
        }
    }
}

// Check if the item is purchasable
bool ItemTree::isPurchasable() const {
    return purchasable;
}

// Set the item as purchasable
void ItemTree::setPurchasable(bool status) {
    purchasable = status;
}

// Mark children as purchasable
void ItemTree::unlockChildren() {
    if (fLeft != &NIL) {
        fLeft->setPurchasable(true);
    }
    if (fRight != &NIL) {
        fRight->setPurchasable(true);
    }
}

// Destructor
ItemTree::~ItemTree() {
    delete fKey; // Deleting the ShopItem
    // Delete left and right children if they are not NIL
    if (fLeft != &NIL) {
        delete fLeft;
    }
    if (fRight != &NIL) {
        delete fRight;
    }
}

// Sentinel implementation for ItemTree
ItemTree ItemTree::NIL;
