#include "Shop.h"

// Initialize the static member
Shop* Shop::instance = nullptr;

// Overloaded constructor
Shop::Shop(Player* playerInstance, Enemy* enemyInstance, CustomerEntity* customerInstance, Stack& cardStackInstance)
    : shopWindow(sf::VideoMode(800, 600), "Shop"), selectedItemIndex(0), player(playerInstance), enemy(enemyInstance), customer(customerInstance), cardStack(cardStackInstance), cardClaimed(false), reputationItemsTree(nullptr), reputationItemsTreeDisplayed(false), speedItemsTree(nullptr), speedItemsTreeDisplayed(false) {

    createPopButton(); // Create pop button
    createBagButton(); // Create bag button
    createHashopediaButton(); // Create hashopedia button
    createApronButton(); // Create apron button


    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // Initialize shop items using the new addShopItem method
    addShopItem(new WaterBottle());
    addShopItem(new FortuneCat());
    addShopItem(new ReputationBoostingKit());
    addShopItem(new SpeedBoostingKit());
    addShopItem(new Boots());
    addShopItem(new Butter());

    addShopItem(new Cigarettes());
    addShopItem(new Pearls());
    addShopItem(new FortunePig());
    addShopItem(new FortuneMask());
    addShopItem(new Heels());
    addShopItem(new Axolotl());

    // Initialize card actions at the start of the game
    if (cardStack.isEmpty()) { // Check if the stack is empty to avoid duplicate pushes
        cardStack.push("Increase Reputation", 10);
        cardStack.push("Decrease Reputation", -5);
        cardStack.push("Increase Reputation", 20);
        cardStack.push("Increase Reputation", 30);
    }
    cardStack.printCards(); // Print to check stack content

    // Build the reputation items tree if not already built
    if (!reputationItemsTree) {
        buildReputationItemsTree(); 
    }

    // Build the speed items tree if not already built
    if (!speedItemsTree) {
        buildSpeedItemsTree(); 
    }
}

// Singleton method to get the Shop instance
Shop* Shop::getInstance(Player* playerInstance, Enemy* enemyInstance, CustomerEntity* customerInstance, Stack& cardStackInstance) {
    if (instance == nullptr) {
        instance = new Shop(playerInstance, enemyInstance, customerInstance, cardStackInstance);
    }
    // Log the address
    std::cout << "Shop instance address: " << instance << std::endl;

    return instance;
}

// Open the shop window and handle the shop loop
void Shop::openShop() {
    if (!shopWindow.isOpen()) {
        shopWindow.create(sf::VideoMode(1700, 700), "Shop");
    }

    // Main shop window event loop
    while (shopWindow.isOpen()) {
        sf::Event event;
        while (shopWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                shopWindow.close(); // Close the window if 'Closed' event occurs
        }

        handleInput();      // Handle user input
        shopWindow.clear(sf::Color::White); // Clear window
        displayItems();     // Display shop items
        shopWindow.display(); // Display the updated contents
    }
}

// Reset shop window and flags
void Shop::resetShop() {
    if (shopWindow.isOpen()) {
        shopWindow.close();
    }
    cardClaimed = false;    // Reset the cardClaimed flag
}

// Display all shop items with positions and properties
void Shop::displayItems() {
    // Define positions for items in two rows
    const float startX = 60; // Starting X position
    const float startY = 50; // Starting Y position
    const float itemSpacingX = 300; // Increased horizontal spacing between items
    const float itemSpacingY = 250; // Increased vertical spacing between rows
    const int itemsPerRow = 6; // Number of items per row
    const float textOffsetY = 100; // Offset for the item name text
    const float costOffsetY = 130; // Offset for the cost text, below the item name

    // Loop through all items in the shop
    for (size_t i = 0; i < shopItems.size(); ++i) {
        // Calculate the row and column for the current item
        int row = i / itemsPerRow;
        int col = i % itemsPerRow;

        // Calculate the position for the item
        float posX = startX + col * itemSpacingX;
        float posY = startY + row * itemSpacingY;

        // Draw the item at calculated position
        shopItems[i]->draw(shopWindow, posX, posY);

        // Display item name text below the image
        sf::Text itemNameText;
        itemNameText.setFont(font);
        itemNameText.setString(shopItems[i]->getName());
        itemNameText.setCharacterSize(24);
        itemNameText.setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::Black);
        itemNameText.setPosition(posX, posY + textOffsetY); // Position the name text below the image

        // Display item cost text below the item name
        sf::Text itemCostText;
        itemCostText.setFont(font);
        itemCostText.setString("Cost: " + std::to_string(shopItems[i]->getCost()));
        itemCostText.setCharacterSize(20);
        itemCostText.setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::Black);
        itemCostText.setPosition(posX, posY + costOffsetY); // Position the cost text below the item name

        // Draw item name and cost texts
        shopWindow.draw(itemNameText);
        shopWindow.draw(itemCostText);
    }

    // Display buttons
    shopWindow.draw(popButton);
    shopWindow.draw(popButtonText);

    shopWindow.draw(bagButton);
    shopWindow.draw(bagButtonText);

    shopWindow.draw(hashopediaButton);
    shopWindow.draw(hashopediaButtonText);

    shopWindow.draw(apronButton);
    shopWindow.draw(apronButtonText);
}

// Display the reputation items tree in the console
void Shop::displayReputationItemsTree() {
    std::cout << "Reputation Items Tree" << std::endl;
    if (reputationItemsTree) {
        reputationItemsTree->display();
    }
    else {
        std::cout << "Reputation Items Tree is empty!\n";
    }
    std::cout << "End of Reputation Items Tree" << std::endl;
}

// Display the speed items tree in the console
void Shop::displaySpeedItemsTree() {
    std::cout << "Speed Items Tree" << std::endl;
    if (speedItemsTree) {
        speedItemsTree->display();
    }
    else {
        std::cout << "Speed Items Tree is empty!\n";
    }
    std::cout << "End of Speed Items Tree" << std::endl;
}

// Handles user input in the shop window (such as button clicks, keyboard clicks, item selection etc)
void Shop::handleInput() {
    static bool PkeyPressed = false; // Track P key press state
    static bool buttonPressed = false; // Track pop button click state
    const int itemsPerRow = 6; // Number of items per row
    bool hashMenuActive = false; // Track if hash menu is active

    // Handle left key press for item selection
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        selectedItemIndex = (selectedItemIndex > 0) ? selectedItemIndex - 1 : shopItems.size() - 1;
        sf::sleep(sf::milliseconds(200));
    }

    // Handle right key press for item selection
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        selectedItemIndex = (selectedItemIndex + 1) % shopItems.size();
        sf::sleep(sf::milliseconds(200));
    }

    // Handle up key press to move up by a row in item grid
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (selectedItemIndex >= itemsPerRow) {
            selectedItemIndex -= itemsPerRow;
        }
        else {
            selectedItemIndex = (selectedItemIndex + (shopItems.size() / itemsPerRow) * itemsPerRow) % shopItems.size();
        }
        sf::sleep(sf::milliseconds(200));
    }

    // Handle down key press to move down by a row in item grid
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (selectedItemIndex + itemsPerRow < shopItems.size()) {
            selectedItemIndex += itemsPerRow;
        }
        else {
            selectedItemIndex = selectedItemIndex % itemsPerRow;
        }
        sf::sleep(sf::milliseconds(200));
    }

    // Handle 'P' key press for purchasing item
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        if (!PkeyPressed) { // Check if P was not previously pressed
            PkeyPressed = true; // Set P as pressed
            if (selectedItemIndex < shopItems.size()) {
                purchaseItem(selectedItemIndex); // Purchase the selected item
            }
            else {
                shopWindow.close(); // Close shop if no valid selection
            }
        }
    }
    else {
        PkeyPressed = false; // Reset P press state when key is released
    }

    // Check for mouse button clicks
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(shopWindow);
        
        // Check if pop button is clicked
        if (popButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            // Handle pop button click and card claiming logic
            if (!cardClaimed && !buttonPressed) {
                cardClaimed = true; // Mark the card as claimed
                buttonPressed = true; // Mark the button as pressed

                // Peek the top card before popping
                auto topCard = cardStack.peekCard();
                if (topCard.first != "") { // Ensure there is a card to pop
                    std::cout << "Card popped: " << topCard.first << " (Points: " << topCard.second << ")\n";

                    // Get original reputation
                    int originalReputation = player->getPlayerReputation();
                    std::cout << "Original Reputation: " << originalReputation << std::endl;

                    // Update the player's reputation based on the card points
                    player->setPlayerReputation(originalReputation + topCard.second);

                    // Output the final reputation after the change
                    std::cout << "Final Reputation: " << player->getPlayerReputation() << std::endl;

                    cardStack.pop(); // Pop the first card
                }
                else {
                    std::cout << "No cards in the stack.\n"; // Inform if stack is empty
                }
            }
            else if (cardClaimed && !buttonPressed) {
                buttonPressed = true; // Mark the button as pressed
                std::cout << "Already claimed your card, cannot pop again.\n";
            }
        }

        // Check if bag button is clicked
        else if (bagButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            player->handleBagMenu(); // Trigger player bag handling
            buttonPressed = true; // Mark the button as pressed
        }

        // If the hashopedia button is clicked
        else if (hashopediaButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            std::cout << "Hashopedia button clicked!\n";
            hashMenuActive = true;  // Set hash menu active
        }

        // Check if apron button is clicked
        else if (apronButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            player->handleApronMenu(); // Trigger player apron handling
            buttonPressed = true; // Mark the button as pressed
        }
    }
    else {
        buttonPressed = false; // Reset when the mouse button is released
    }
    // If hash menu is active, display hash-related options
    if (hashMenuActive) {
        char input;

        while (true) {
            // Display the hash menu options
            std::cout << "Hash Menu\n";
            std::cout << "1. Find Item Description by Name\n";
            std::cout << "2. Print Entire Hash Table\n";
            std::cout << "3. Print Items in Specific Index\n";
            std::cout << "4. Exit Hash Menu\n"; // Add an option to exit
            std::cout << "Press a key to select an option...\n";

            // Wait for user input
            std::cin >> input;

            switch (input) {
            case '1': {
                std::string itemName;
                std::cout << "Enter item name: ";
                std::cin.ignore();  // Clear any leftover newline from previous input
                std::getline(std::cin, itemName); // Use getline to capture the full name, including spaces
                hashTable.FindDescription(itemName);
                break;
            }
            case '2': {
                hashTable.PrintTable(); // Print entire hash table
                break;
            }
            case '3': {
                int index;
                std::cout << "Enter index: ";
                std::cin >> index;
                hashTable.PrintItemsInIndex(index); // Print items at specified index
                break;
            }
            case '4': {
                std::cout << "Exiting Hash Menu.\n";
                return; // Exit the function, thus closing the menu
            }
            default:
                std::cout << "Invalid option. Please select a valid option.\n";
                break;
            }
        }
    }
}

// Purchases an item based on the given index
void Shop::purchaseItem(int index) {
    // Validate the item index; if invalid, output error and return
    if (index < 0 || index >= shopItems.size()) {
        std::cerr << "Invalid item index.\n";
        return;
    }

    // Get the shop item based on index
    ShopItem* item = shopItems[index];

    // Find the item in the reputation items tree
    ItemTree* currentNode = findNode(reputationItemsTree, item);

    // If not found, check in the speed items tree
    if (!currentNode) {
        currentNode = findNode(speedItemsTree, item);
        if (!currentNode) {
            std::cerr << "Item not found in either item tree.\n";
            return;
        }
    }

    // Check if the item is purchasable
    if (!currentNode->isPurchasable()) {
        std::cerr << "This item is not available for purchase yet.\n";
        return;
    }

    // Prompt the player to decide whether to use Reputation Points or Scrap to buy the item
    std::cout << "Do you want to use Reputation Points or Scrap to buy " << item->getName() << "?\n";
    std::cout << "1. Reputation Points\n2. Scrap\n";
    char choice;
    std::cin >> choice;

    if (choice == '1') {
        // Deduct reputation points if the player has enough
        int cost = item->getCost();
        if (player->getPlayerReputation() >= cost) {
            player->setPlayerReputation(player->getPlayerReputation() - cost);

            // Add the item to the player's bag
            player->addItemToBag(item->getName(), cost);

            // Confirm purchase and display the bag's contents
            std::cout << "You bought " << item->getName() << " for " << cost << " Reputation Points.\n";
            std::cout << "Current items in bag:\n";
            player->listItemsInBag();

            // Mark the children of the current node as purchasable
            currentNode->unlockChildren();
        }
        else {
            std::cout << "You don't have enough Reputation Points!\n";
        }
    }
    else if (choice == '2') {
        // Prompt the player to enter the scrap name
        std::cout << "Enter the name of the scrap you want to use:\n";
        std::cin.ignore(); // Ignore any leftover newline from previous input
        std::string scrapName;
        std::getline(std::cin, scrapName);

        // Check if the player has the specified scrap
        if (player->findScrapFromApron(scrapName)) {
            player->removeScrapFromApron(scrapName);

            // Add the item to the player's bag using scrap
            player->addItemToBag(item->getName(), item->getCost());  // No cost deduction for scrap purchase
            std::cout << "You bought " << item->getName() << " using " << scrapName << ".\n";
            std::cout << "Current items in bag:\n";
            player->listItemsInBag();

            // Mark the children of the current node as purchasable
            currentNode->unlockChildren();
        }
        else {
            std::cout << "You don't have a scrap named " << scrapName << "!\n";
            std::cout << "You didn't buy anything with the scrap.\n";
        }
    }
    else {
        std::cout << "Invalid choice. Please select again.\n";
    }
}

// Function to search for a node in the item tree
ItemTree* Shop::findNode(ItemTree* node, ShopItem* item) {
    // Base case: return null if node is null or empty
    if (node == nullptr || node->isEmpty()) {
        return nullptr;
    }

    // Check if node matches item
    if (node->key() == item) {
        return node;
    }
    
    // Recursively search left and right subtrees
    ItemTree* leftResult = findNode(node->left(), item);
    if (leftResult != nullptr) {
        return leftResult;
    }
    return findNode(node->right(), item);
}

// Builds a binary tree for reputation-boosting items
void Shop::buildReputationItemsTree() {
    // Create root node with ReputationBoostingKit
    reputationItemsTree = new ItemTree(shopItems[2]);

    // WaterBottle as the left child of the root
    reputationItemsTree->attachLeft(new ItemTree(shopItems[0]));

    // FortuneCat as the right child of the root
    reputationItemsTree->attachRight(new ItemTree(shopItems[1]));

    // Attach children to WaterBottle
    reputationItemsTree->left()->attachLeft(new ItemTree(shopItems[6])); // Cigarettes
    reputationItemsTree->left()->attachRight(new ItemTree(shopItems[7])); // Pearls

    // Attach children to FortuneCat
    reputationItemsTree->right()->attachLeft(new ItemTree(shopItems[8])); // Fortune Pig
    reputationItemsTree->right()->attachRight(new ItemTree(shopItems[9])); // Fortune Mask

    // Set NIL for children of Cigarettes and Pearls (if they have no further children)
    reputationItemsTree->left()->left()->attachLeft(&ItemTree::NIL); // Cigarettes left child is NIL
    reputationItemsTree->left()->left()->attachRight(&ItemTree::NIL); // Cigarettes right child is NIL

    reputationItemsTree->left()->right()->attachLeft(&ItemTree::NIL); // Pearls left child is NIL
    reputationItemsTree->left()->right()->attachRight(&ItemTree::NIL); // Pearls right child is NIL

    reputationItemsTree->right()->left()->attachLeft(&ItemTree::NIL); // Fortune Pig left child is NIL
    reputationItemsTree->right()->left()->attachRight(&ItemTree::NIL); // Fortune Pig right child is NIL

    reputationItemsTree->right()->right()->attachLeft(&ItemTree::NIL); // Fortune Mask left child is NIL
    reputationItemsTree->right()->right()->attachRight(&ItemTree::NIL); // Fortune Mask right child is NIL

    // Set the flag to indicate that the item tree is now displayed
    reputationItemsTreeDisplayed = true;

    // Display tree structure if not already displayed
    if (reputationItemsTreeDisplayed) {
        displayReputationItemsTree();
    }
    reputationItemsTreeDisplayed = false;

    // Set the root node to be purchasable (Initial as the only purchasable item in this tree at the start of the game)
    reputationItemsTree->setPurchasable(true);
}

// Builds a binary tree for speed items
void Shop::buildSpeedItemsTree() {
    // Create root node with SpeedBoostingKit
    speedItemsTree = new ItemTree(shopItems[3]);

    // Butter as the left child of the root
    speedItemsTree->attachLeft(new ItemTree(shopItems[5]));

    // Boots as the right child of the root
    speedItemsTree->attachRight(new ItemTree(shopItems[4]));

    speedItemsTree->left()->attachLeft(new ItemTree(shopItems[11])); // Axolotl as the left child of Butter
    speedItemsTree->left()->attachRight(&ItemTree::NIL); // Attach NIL sentinel to the right

    speedItemsTree->right()->attachLeft(new ItemTree(shopItems[10])); // Heels as the left child of Boots
    speedItemsTree->right()->attachRight(&ItemTree::NIL); // Attach NIL sentinel to the right

    // Attach NIL children to Axolotl
    speedItemsTree->left()->left()->attachLeft(&ItemTree::NIL); // Axolotl left child is NIL
    speedItemsTree->left()->left()->attachRight(&ItemTree::NIL); // Axolotl right child is NIL

    // Attach NIL children to Heels
    speedItemsTree->right()->left()->attachLeft(&ItemTree::NIL); // Heels left child is NIL
    speedItemsTree->right()->left()->attachRight(&ItemTree::NIL); // Heels right child is NIL

    // Set the flag to indicate that the item tree is now displayed
    speedItemsTreeDisplayed = true;

    // Display tree structure if not already displayed
    if (speedItemsTreeDisplayed) {
        displaySpeedItemsTree();
    }
    speedItemsTreeDisplayed = false;

    // Set the root node to be purchasable (Initial as the only purchasable item in this tree at the start of the game)
    speedItemsTree->setPurchasable(true);
}

// Method for the button to open the player's bag
void Shop::createBagButton() {
    // Define the size and position of the bag button
    bagButton.setSize(sf::Vector2f(200, 50));
    bagButton.setFillColor(sf::Color(100, 100, 250));
    bagButton.setPosition(20, 600); // Positioned at bottom left of the window

    // Set the text for the bag button
    bagButtonText.setFont(font);
    bagButtonText.setString("Open Bag");
    bagButtonText.setCharacterSize(24);
    bagButtonText.setFillColor(sf::Color::Black);

    // Calculate text position to center it in the button
    sf::FloatRect textBounds = bagButtonText.getLocalBounds();
    bagButtonText.setPosition(
        20 + (95 - textBounds.width) / 2, // Center text horizontally
        600 + (25 - textBounds.height) / 2 // Center text vertically
    );
}

// Method for the button to open the player's apron
void Shop::createApronButton() {
    apronButton.setSize(sf::Vector2f(200, 50)); // Same size as other buttons
    apronButton.setFillColor(sf::Color(250, 100, 100));  // Button color
    apronButton.setPosition(220, 600);            // Positioned at bottom left of the window

    apronButtonText.setFont(font);
    apronButtonText.setString("Open Apron");
    apronButtonText.setCharacterSize(24);
    apronButtonText.setFillColor(sf::Color::Black);

    // Calculate text position to center it in the button
    sf::FloatRect textBounds = apronButtonText.getLocalBounds();
    apronButtonText.setPosition(
        220 + (70 - textBounds.width) / 2, // Center text horizontally
        600 + (25 - textBounds.height) / 2 // Center text vertically
    );
}

// Create the button for "Pop Card"
void Shop::createPopButton() {
    popButton.setSize(sf::Vector2f(200, 50)); // Set button size
    popButton.setFillColor(sf::Color(100, 250, 100)); // Set button color
    popButton.setPosition(1200, 600); // Positioned at bottom right of the window

    // Set up button text
    popButtonText.setFont(font);
    popButtonText.setString("Pop Card");
    popButtonText.setCharacterSize(24);
    popButtonText.setFillColor(sf::Color::Black);

    // Calculate text position to center it in the button
    sf::FloatRect textBounds = popButtonText.getLocalBounds();
    popButtonText.setPosition(
        1200 + (100 - textBounds.width) / 2, // Center text horizontally
        600 + (25 - textBounds.height) / 2 // Center text vertically
    );
}

// Create the button for "Open Hashopedia"
void Shop::createHashopediaButton() {
    // Set the button shape
    hashopediaButton.setSize(sf::Vector2f(225, 50)); // Same width and height as the other buttons
    hashopediaButton.setFillColor(sf::Color(250, 250, 100)); // Button color
    hashopediaButton.setPosition(1400, 600); // Positioned next to the Pop Card button

    // Set the button text
    hashopediaButtonText.setFont(font);
    hashopediaButtonText.setString("Open Hashopedia");
    hashopediaButtonText.setCharacterSize(24);
    hashopediaButtonText.setFillColor(sf::Color::Black);

    // Calculate text position to center it in the button
    sf::FloatRect textBounds = hashopediaButtonText.getLocalBounds();
    hashopediaButtonText.setPosition(
        1400 + (50 - textBounds.width) / 2, // Center text horizontally
        600 + (25 - textBounds.height) / 2 // Center text vertically
    );
}

// Adds a new item to the shop's item vector and stores its name and description in the hash table for quick lookup
void Shop::addShopItem(ShopItem* newItem) {
    // Add the new item to the shop's item vector
    shopItems.push_back(newItem);

    // Add the item's name and description to the hash table for quick lookups
    hashTable.AddItem(newItem->getName(), newItem->getDescription());
}


// Destructor to free ShopItem objects
Shop::~Shop() {
    for (ShopItem* item : shopItems) {
        delete item;
    }
    shopItems.clear();

    if (instance) {
        delete instance;
        instance = nullptr;
    }
}