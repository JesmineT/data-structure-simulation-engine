#include "Restaurant.h"

// Overloaded constructor
// Constructor with width and height as unsigned to prevent negative dimensions
Restaurant::Restaurant(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode(width, height), title),
    shop(nullptr),
    waitingArea(1200, 600, 290, 150),
    servingHatch(0, 50, 1500, 100),
    appetizer(FoodType::Appetizer, { 445, 60 }, { 40, 40 }), // (FoodType, { x, y }, { w, h })
    mainCourse(FoodType::MainCourse, { 605, 60 }, { 40, 40 }), // (FoodType, { x, y }, { w, h })
    dessert(FoodType::Dessert, { 775, 70 }, { 40, 40 }), // (FoodType, { x, y }, { w, h })
    champagne(FoodType::Champagne, { 905, 50 }, { 40, 40 }), // (FoodType, { x, y }, { w, h })

    selectedCustomer(nullptr), // initialize to nullptrs (not selected anything yet)
    selectedFood(nullptr),
    selectedTable(nullptr),

    currentLevel(1) {

    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // Initialize the bag button position and size
    bagButtonPosition = sf::Vector2f(50.f, 50.f); 
    bagButtonSize = sf::Vector2f(200.f, 50.f);    

    // Setup the bag button text 
    bagButton.setSize(bagButtonSize);
    bagButton.setPosition(bagButtonPosition);
    bagButton.setFillColor(sf::Color(100, 100, 250));  

    // Setup the bag button text
    bagButtonText.setFont(font);  
    bagButtonText.setString("Open Bag");
    bagButtonText.setCharacterSize(24);  
    bagButtonText.setFillColor(sf::Color::White);  
    bagButtonText.setPosition(
        bagButtonPosition.x + (bagButtonSize.x - bagButtonText.getLocalBounds().width) / 2,
        bagButtonPosition.y + (bagButtonSize.y - bagButtonText.getLocalBounds().height) / 2
    );

    // Initialize the apron button position and size
    apronButtonPosition = sf::Vector2f(50.f, 120.f); 
    apronButtonSize = sf::Vector2f(200.f, 50.f);      

    // Setup the apron button text
    apronButton.setSize(apronButtonSize);
    apronButton.setPosition(apronButtonPosition);
    apronButton.setFillColor(sf::Color(250, 100, 100)); 

    // Setup the apron button text
    apronButtonText.setFont(font);
    apronButtonText.setString("Open Apron");
    apronButtonText.setCharacterSize(24);
    apronButtonText.setFillColor(sf::Color::White);
    apronButtonText.setPosition(
        apronButtonPosition.x + (apronButtonSize.x - apronButtonText.getLocalBounds().width) / 2,
        apronButtonPosition.y + (apronButtonSize.y - apronButtonText.getLocalBounds().height) / 2
    );

    // Initialize the first level
    restaurantManager.setCurrentLevel(currentLevel);

    // Assigns the list of customers managed by RestaurantManager to the customers vector in the Restaurant class, 
    // using polymorphism to handle different derived customer types through the base class pointer (CustomerEntity*), 
    // allowing access and rendering without knowing specific types.
    customers = restaurantManager.getCustomers();


    // Retrieve the player instance from the RestaurantManager class
    player = restaurantManager.getPlayer(); // Accesses the player pointer managed by RestaurantManager
    
    // Initialize tables
    tables.emplace_back(Table("1", { 250, 300 }, { 130, 80 }));
    tables.emplace_back(Table("2", { 550, 300 }, { 130, 80 }));
    tables.emplace_back(Table("3", { 850, 300 }, { 130, 80 }));
    tables.emplace_back(Table("4", { 250, 500 }, { 130, 80 }));
    tables.emplace_back(Table("5", { 550, 500 }, { 130, 80 }));
    tables.emplace_back(Table("6", { 850, 500 }, { 130, 80 }));

    // Manually populate the StepTiles for the pathway
    float tileSize = 70;
    stepTiles.emplace_back(StepTile(460, 100, tileSize)); 
    stepTiles.emplace_back(StepTile(630, 100, tileSize)); 
    stepTiles.emplace_back(StepTile(790, 100, tileSize)); 
    stepTiles.emplace_back(StepTile(930, 100, tileSize));  
    stepTiles.emplace_back(StepTile(460, 150, tileSize)); 
    stepTiles.emplace_back(StepTile(460, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(410, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(360, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(310, 200, tileSize));
    stepTiles.emplace_back(StepTile(310, 250, tileSize)); 
    stepTiles.emplace_back(StepTile(500, 200, tileSize));
    stepTiles.emplace_back(StepTile(550, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(600, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(650, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(700, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(750, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(800, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(850, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(900, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(630, 150, tileSize)); 
    stepTiles.emplace_back(StepTile(630, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(630, 250, tileSize)); 
    stepTiles.emplace_back(StepTile(790, 150, tileSize)); 
    stepTiles.emplace_back(StepTile(790, 200, tileSize)); 
    stepTiles.emplace_back(StepTile(930, 150, tileSize));  
    stepTiles.emplace_back(StepTile(930, 200, tileSize));  
    stepTiles.emplace_back(StepTile(930, 250, tileSize));  
    stepTiles.emplace_back(StepTile(450, 250, tileSize));
    stepTiles.emplace_back(StepTile(450, 300, tileSize));
    stepTiles.emplace_back(StepTile(450, 350, tileSize));
    stepTiles.emplace_back(StepTile(450, 400, tileSize));
    stepTiles.emplace_back(StepTile(750, 250, tileSize)); 
    stepTiles.emplace_back(StepTile(750, 300, tileSize));
    stepTiles.emplace_back(StepTile(750, 350, tileSize));
    stepTiles.emplace_back(StepTile(750, 400, tileSize));
    stepTiles.emplace_back(StepTile(700, 400, tileSize));
    stepTiles.emplace_back(StepTile(650, 400, tileSize));
    stepTiles.emplace_back(StepTile(600, 400, tileSize));
    stepTiles.emplace_back(StepTile(550, 400, tileSize));
    stepTiles.emplace_back(StepTile(500, 400, tileSize));
    stepTiles.emplace_back(StepTile(800, 400, tileSize));
    stepTiles.emplace_back(StepTile(850, 400, tileSize));
    stepTiles.emplace_back(StepTile(900, 400, tileSize));
    stepTiles.emplace_back(StepTile(450, 400, tileSize));
    stepTiles.emplace_back(StepTile(400, 400, tileSize));
    stepTiles.emplace_back(StepTile(350, 400, tileSize));
    stepTiles.emplace_back(StepTile(300, 400, tileSize));
    stepTiles.emplace_back(StepTile(300, 450, tileSize));
    stepTiles.emplace_back(StepTile(600, 450, tileSize));
    stepTiles.emplace_back(StepTile(900, 450, tileSize));
    stepTiles.emplace_back(StepTile(950, 400, tileSize));
    stepTiles.emplace_back(StepTile(1000, 400, tileSize));
    stepTiles.emplace_back(StepTile(1050, 400, tileSize));
    stepTiles.emplace_back(StepTile(1100, 400, tileSize));
    stepTiles.emplace_back(StepTile(1150, 400, tileSize));
    stepTiles.emplace_back(StepTile(1200, 400, tileSize));
    stepTiles.emplace_back(StepTile(1200, 450, tileSize));
    stepTiles.emplace_back(StepTile(1200, 500, tileSize));
    stepTiles.emplace_back(StepTile(1200, 550, tileSize));
    stepTiles.emplace_back(StepTile(1250, 550, tileSize));
    stepTiles.emplace_back(StepTile(1300, 550, tileSize));
    stepTiles.emplace_back(StepTile(1350, 550, tileSize));
}

// Main game loop
void Restaurant::run() {
    // Enqueue music tracks for each level at the start
    audioManager.enqueueTrack("Main Menu.wav");
    audioManager.enqueueTrack("On Time! (Barely).wav");
    audioManager.enqueueTrack("Table for Two.wav");

    // Start playing the first track
    audioManager.playNextTrack();

    // Main game loop that runs while the game window is open
    while (window.isOpen()) {
        processEvents(); // Process player inputs and other events

        checkPlayerCustomerCollision(); // Check if the player has collided with a customer

        // Call to check if reputation should increase (for Fortune Cat)
        player->updateReputationForFortuneCat();

        // Call to check if reputation should increase (for Fortune Pig)
        player->updateReputationForFortunePig();

        // Call to check if reputation should increase (for Fortune Mask)
        player->updateReputationForFortuneMask();

        update(); // Update game objects and state
        render(); // Render the game scene

        int reputation = player->getPlayerReputation(); // Get the player's current reputation

        // Check if the player's reputation has dropped to 0 or below
        if (reputation <= 0) {
            std::cout << "Player's reputation has dropped to 0 or below. Game Over!" << std::endl;
            audioManager.stopMusic(); // Stop all background music
            audioManager.stopJumpscareSound(); // Stop any jumpscare sound
            exit(0); // Exit the program immediately
        }

        // Transition logic for Level 1 to Level 2
        if (currentLevel == 1 && restaurantManager.isLevelComplete()) {
            std::cout << "Level 1 complete! Moving to Level 2...\n";
            std::cout << "Press any key to continue..." << std::endl; // Prompt user
            std::cin.ignore(); // Wait for user input
            std::cin.get(); // Wait for any key press

            // Get or create the Shop instance
            shop = Shop::getInstance(player, &enemy, selectedCustomer, cardStack);
            if (shop) {
                shop->resetShop(); // Reset shop for the new level
                shop->openShop(); // Open the shop for purchases
            }
            else {
                std::cerr << "Failed to get Shop instance!" << std::endl;
            }

            currentLevel = 2; // Move to Level 2
            restaurantManager.setCurrentLevel(currentLevel); // Update RestaurantManager to new level
            audioManager.playNextTrack(); // Play the next level's music track

            // Update local variables to reflect new level data
            customers = restaurantManager.getCustomers(); // Retrieve updated customer list
            player = restaurantManager.getPlayer(); // Retrieve updated player instance
        }

        // Transition logic for Level 2 to Level 3
        if (currentLevel == 2 && restaurantManager.isLevelComplete()) {
            std::cout << "Level 2 complete! Moving to Level 3...\n";
            std::cout << "Press any key to continue..." << std::endl; // Prompt user to continue
            std::cin.ignore(); // Wait for user input
            std::cin.get(); // Wait for any key press

            // Obtain or create the Shop instance
            shop = Shop::getInstance(player, &enemy, selectedCustomer, cardStack);
            if (shop) {
                shop->resetShop(); // Reset shop for the new level
                shop->openShop(); // Open the shop for purchases
            }
            else {
                std::cerr << "Failed to get Shop instance!" << std::endl;
            }

            currentLevel = 3; // Move to Level 3
            restaurantManager.setCurrentLevel(currentLevel); // Update RestaurantManager to new level
            audioManager.playNextTrack(); // Play the next level's music track

            // Update local variables to reflect new level data
            customers = restaurantManager.getCustomers(); // Retrieve updated customer list
            player = restaurantManager.getPlayer(); // Retrieve updated player instance
        }

        // Check if Level 3 is complete, indicating the end of the game
        if (currentLevel == 3 && restaurantManager.isLevelComplete()) {
            std::cout << "Congratulations! You have completed all levels. Game Over!" << std::endl;
            std::cout << "Press any key to exit..." << std::endl; // Prompt user to exit
            std::cin.ignore(); // Wait for user input
            std::cin.get(); // Wait for any key press

            window.close(); // Close the game window
            break; // Exit the game loop
        }
    }
}

// Define this method to check if the player is within the StepTile boundaries, helping in pathing and movement restriction
bool Restaurant::isWithinStepTileBoundaries(const sf::Vector2f& position) const {
    // Iterate through all step tiles
    for (const auto& tile : stepTiles) {
        // Check if the player is within the bounds of a step tile
        if (tile.contains(position)) {
            return true; // Player is within one of the step tile boundaries
        }
    }
    return false; // Player is outside all step tile boundaries
}

// Function to check if the player collides with any scrap and remove it
void Restaurant::checkPlayerScrapCollision() {
    // Loop through all scraps from the RestaurantManager
    for (auto currentScrap = restaurantManager.getScraps().begin(); currentScrap != restaurantManager.getScraps().end();) {
        sf::FloatRect playerBounds = player->getGlobalBounds();
        sf::FloatRect scrapBounds = currentScrap->getGlobalBounds();

        // Check if the player's bounds intersect with the scrap's bounds
        if (playerBounds.intersects(scrapBounds)) {
            // Check if the scrap is already in the player's apron
            if (!player->findScrapFromApron(currentScrap->getName())) {
                player->addScrapToApron(currentScrap->getName());
            }

            // Remove the scrap from the vector
            currentScrap = restaurantManager.getScraps().erase(currentScrap);
        }
        else {
            ++currentScrap; // Move to the next scrap if no collision
        }
    }
}

// Checks if player collides with a customer
void Restaurant::checkPlayerCustomerCollision() {
    // Check for "Reputation Boosting Kit" in the bag and apply to any customer type
    if (player->IsItemInBag("Reputation Boosting Kit") && player->isItemActivated("Reputation Boosting Kit")) { // Check if "Reputation Boosting Kit" is in the bag
        for (auto& customer : customers) {
            if (customer->getGlobalBounds().intersects(player->getGlobalBounds())) {
                // Player is in proximity of a customer
                // Apply the "Reputation Boosting Kit" effect to any customer type
                reputationBoostingKit.applyCustomerEffect(player, customer);
            }
        }
    }

    if (player->IsItemInBag("Cigarettes") && player->isItemActivated("Cigarettes")) { // Check if "Cigarette" is in the bag
        for (auto& customer : customers) {
            if (dynamic_cast<VIPCustomer*>(customer)) { // Check if it's a VIP customer
                if (customer->getGlobalBounds().intersects(player->getGlobalBounds())) {
                    // Player is in proximity of a VIP customer
                    // Apply the effect only if "Cigarette" is found in the inventory
                    cigarettes.applyCustomerEffect(player, customer);
                }
            }
        }
    }
    if (player->IsItemInBag("Pearls") && player->isItemActivated("Pearls")) { // Check if "Pearls" is in the bag
        for (auto& customer : customers) {
            if (dynamic_cast<PrincessCustomer*>(customer)) { // Check if it's a Princess customer
                if (customer->getGlobalBounds().intersects(player->getGlobalBounds())) {
                    // Player is in proximity of a Princess customer
                    // Apply the effect only if "Pearls" is found in the inventory
                    pearls.applyCustomerEffect(player, customer);
                }
            }
        }
    }
    if (player->IsItemInBag("WaterBottle") && player->isItemActivated("WaterBottle")) { // Check if "WaterBottle" is in the bag
        for (auto& customer : customers) {
            if (dynamic_cast<SeniorCustomer*>(customer)) { // Check if it's a Senior customer
                if (customer->getGlobalBounds().intersects(player->getGlobalBounds())) {
                    // Player is in proximity of a Senior customer
                    // Apply the effect only if "WaterBottle" is found in the inventory
                    waterBottle.applyCustomerEffect(player, customer);
                }
            }
        }
    }

    // Apply effects of other activated items in the player's bag that impact the player or enemy directly
    if (player->IsItemInBag("Speed Boosting Kit") && player->isItemActivated("Speed Boosting Kit")) {
        speedBoostingKit.applyEffect(player, &enemy);
    }
    if (player->IsItemInBag("Boots") && player->isItemActivated("Boots")) {
        boots.applyEffect(player, &enemy);
    }
    if (player->IsItemInBag("Heels") && player->isItemActivated("Heels")) {
        heels.applyEffect(player, &enemy);
    }
    if (player->IsItemInBag("Butter") && player->isItemActivated("Butter")) {
        butter.applyEffect(player, &enemy);
    }
    if (player->IsItemInBag("Axolotl") && player->isItemActivated("Axolotl")) {
        axolotl.applyEffect(player, &enemy);
    }
    if (player->IsItemInBag("Fortune Cat") && player->isItemActivated("Fortune Cat")) {
        fortuneCat.applyEffect(player, &enemy);
    }
    if (player->IsItemInBag("Fortune Pig") && player->isItemActivated("Fortune Pig")) {
        fortunePig.applyEffect(player, &enemy);
    }
}

// Processes all events
void Restaurant::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Check for a mouse click on the bag button
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Check if the click is within the bounds of the bag button
            if (bagButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                player->handleBagMenu();
            }

            // Check if the click is within the bounds of the apron button
            if (apronButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                player->handleApronMenu();
            }
        }

        // Handle key presses
        if (event.type == sf::Event::KeyPressed) {
            // Press spacebar to review player's current reputation
            if (event.key.code == sf::Keyboard::Space) {
                if (player) {
                    std::cout << "Player Reputation: " << player->getPlayerReputation() << std::endl;
                    std::cout << "\n";
                }
                else {
                    std::cout << "Player instance is null\n" << std::endl; // Debugging output
                }
            }
        }

        // Handle mouse clicks
        if (event.type == sf::Event::MouseButtonPressed) {
            float mouseX = event.mouseButton.x;
            float mouseY = event.mouseButton.y;

            // Handle right mouse clicks
            if (event.mouseButton.button == sf::Mouse::Right) {
                handleRightClick(mouseX, mouseY);
            }
        }
    }
}

bool isColliding = false;

// Updates game state and elements each frame
void Restaurant::update() {
    // Handle player movement with arrow keys
    if (player) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            // Move up
            sf::Vector2f newPosition = player->getPosition(); 
            newPosition.y -= player->getPlayerSpeed();
            // Check boundaries before updating the position
            if (isWithinStepTileBoundaries(newPosition)) {
                player->setPosition(newPosition); 
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            // Move down
            sf::Vector2f newPosition = player->getPosition();
            newPosition.y += player->getPlayerSpeed();
            if (isWithinStepTileBoundaries(newPosition)) {
                player->setPosition(newPosition);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Move left
            sf::Vector2f newPosition = player->getPosition();
            newPosition.x -= player->getPlayerSpeed();
            if (isWithinStepTileBoundaries(newPosition)) {
                player->setPosition(newPosition);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // Move right
            sf::Vector2f newPosition = player->getPosition();
            newPosition.x += player->getPlayerSpeed();
            if (isWithinStepTileBoundaries(newPosition)) {
                player->setPosition(newPosition);
            }
        }
    }

    // Check for interactions based on player proximity to objects
    handlePlayerProximity();

    // Check if player is colliding with any scrap
    checkPlayerScrapCollision();

    // Update each customer in the restaurant
    for (auto& customer : customers) {
        customer->update();
    }

    // Update enemy spawning and behavior through restaurant manager
    restaurantManager.update();

    bool hasColliding = false;
    // If the enemy has spawned, update the enemy behavior
    if (restaurantManager.isEnemySpawned()) {
        enemy.chase(player, *this);

        // Check for collisions between the player and the enemy
        if (checkCollision(*player, enemy)) {
            if (!isColliding) {
                // Apply effect if player has a specific item and it's active
                if (player->IsItemInBag("Fortune Mask") && player->isItemActivated("Fortune Mask")) {
                    fortuneMask.applyEffect(player, &enemy);
                }
                std::cout << "Playing Jumpscare Sound..." << std::endl;
                audioManager.playJumpscareSound("Jumpscare Sound.wav", 20); // Play sound

                enemy.attackPlayerReputation(); // Decrease player's reputation

                isColliding = true; // Set collision state to true
            }
        }
        else {
            isColliding = false; // Reset collision state if no collision
        }
    }

    // Check if all customers have finished their meals
    restaurantManager.checkLevelCompletion(window, customers);
}

// Checks for collision between player and enemy
bool Restaurant::checkCollision(const Player& player, const Enemy& enemy) {
    // Get bounding boxes of player and enemy
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect enemyBounds = enemy.getGlobalBounds();

    // Check for intersection between bounding boxes
    return playerBounds.intersects(enemyBounds);
}

// Renders the game elements on the screen
void Restaurant::render() {
    window.clear();

    // Draw static restaurant elements
    waitingArea.draw(window);
    servingHatch.draw(window);

    // Draw each step tile
    for (auto& tile : stepTiles) { 
        tile.draw(window);
    }

    // Draw each table
    for (auto& table : tables) {
        table.draw(window);
    }

    // Draw food items
    appetizer.draw(window);
    mainCourse.draw(window);
    dessert.draw(window);
    champagne.draw(window);

    // Draw enemy if it has spawned
    if (restaurantManager.isEnemySpawned()) {
        enemy.draw(window);
    }

    // Draw scraps on the screen
    for (const Scrap& scrap : restaurantManager.getScraps()) {
        scrap.draw(window); 
    }

    // Draw each customer in the restaurant
    for (auto& customer : customers) {
        customer->draw(window);
    }
    // Draw the player character
    if (player) {
        player->draw(window);
    }

    // Draw the bag button
    window.draw(bagButton);   
    window.draw(bagButtonText); 

    // Draw the apron button
    window.draw(apronButton);     
    window.draw(apronButtonText);

    window.display();
}

// Handles logic when the player is intersecting specific objects
void Restaurant::handlePlayerProximity() {
    bool foodSelectionConfirmed = false;  // Flag to confirm food selection

    // Check if player intersects any food item and set selectedFood
    if (appetizer.getGlobalBounds().intersects(player->getGlobalBounds())) {
        if (!appetizer.isMessagePrinted()) {
            std::cout << "Food selected: Appetizer\n";
            appetizer.setMessagePrinted(true);
        }
        selectedFood = &appetizer;
        foodSelectionConfirmed = false; 
    }
    else if (mainCourse.getGlobalBounds().intersects(player->getGlobalBounds())) {
        if (!mainCourse.isMessagePrinted()) {
            std::cout << "Food selected: Main Course\n";
            mainCourse.setMessagePrinted(true);
        }
        selectedFood = &mainCourse;
        foodSelectionConfirmed = false; 
    }
    else if (dessert.getGlobalBounds().intersects(player->getGlobalBounds())) {
        if (!dessert.isMessagePrinted()) {
            std::cout << "Food selected: Dessert\n";
            dessert.setMessagePrinted(true);
        }
        selectedFood = &dessert;
        foodSelectionConfirmed = false;
    }
    else if (champagne.getGlobalBounds().intersects(player->getGlobalBounds())) {
        if (!champagne.isMessagePrinted()) {
            std::cout << "Food selected: Champagne\n";
            champagne.setMessagePrinted(true);
        }
        selectedFood = &champagne;
        foodSelectionConfirmed = false; 
    }
    else {
        // Reset message status if no food selected
        appetizer.setMessagePrinted(false);
        mainCourse.setMessagePrinted(false);
        dessert.setMessagePrinted(false);
        champagne.setMessagePrinted(false);
        appetizer.resetMessageStatus();
        mainCourse.resetMessageStatus();
        dessert.resetMessageStatus();
        champagne.resetMessageStatus();
    }

    // Check proximity to customers and confirm food selection
    for (auto& customer : customers) {
        if (customer->getGlobalBounds().intersects(player->getGlobalBounds())) {
            if (!customer->isMessagePrinted()) {
                std::cout << customer->getCustomerID() << " is selected\n";
                customer->setMessagePrinted(true);
            }
            // If food is selected but not confirmed, confirm selection by touching customer again
            if (selectedFood != nullptr && !foodSelectionConfirmed) {
                selectedCustomer = customer;
                foodSelectionConfirmed = true;  // Now food selection is confirmed
                std::cout << "Food selection confirmed. Customer " << selectedCustomer->getCustomerID() << " ready for food assignment.\n";
            }
            // If no food is selected, just select the customer for seating
            else if (selectedFood == nullptr) {
                selectedCustomer = customer;
            }
            break; // Exit the loop after selecting customer
        }
        else {
            customer->resetMessageStatus(); // Reset if not colliding
        }
    }

    // Check if the player's circle is colliding a table
    for (auto& table : tables) {
        if (table.getGlobalBounds().intersects(player->getGlobalBounds())) {
            if (!table.isMessagePrinted()) {
                std::cout << "Table " << table.getTableID() << " is " << (table.isAvailable() ? "vacant\n" : "occupied\n");
                table.setMessagePrinted(true);
            }
            selectedTable = &table;
            break;
        }
        else {
            table.resetMessageStatus();
        }
    }

    // Assign customer to table if conditions are met
    if (selectedCustomer != nullptr && !selectedCustomer->isSeated() && selectedTable != nullptr && selectedTable->isAvailable()) {
        std::cout << "Customer " << selectedCustomer->getCustomerID() << " assigned to Table " << selectedTable->getTableID() << std::endl;

        // Assign table to customer and update positions and states
        selectedTable->setAvailability(false);
        selectedCustomer->setSeated(true);
        selectedCustomer->setPosition(selectedTable->getPosition().x + selectedTable->getWidth() / 2 - selectedCustomer->getRadius(),
            selectedTable->getPosition().y + selectedTable->getHeight() / 2 - selectedCustomer->getRadius());
        selectedCustomer->seat(selectedTable);

        // Deselect customer after seating
        selectedCustomer = nullptr;
    }

    // Assign food to customer if selection is confirmed
    if (foodSelectionConfirmed && selectedCustomer != nullptr && selectedCustomer->isSeated()) {
        *selectedFood >> selectedCustomer; // Use the overloaded operator for food assignment

        // Deselect both food and customer after assignment
        selectedFood = nullptr;
        selectedCustomer = nullptr;
        foodSelectionConfirmed = false; // Reset confirmation state
    }
}

// Handles right-click interactions to display customer stats
void Restaurant::handleRightClick(float mouseX, float mouseY) {
    for (CustomerEntity* customer : customers) {
        if (customer->isClicked(mouseX, mouseY)) {
            std::cout << *customer << std::endl; // Output customer stats
        }
    }
}

// Destructor
Restaurant::~Restaurant() {
    // Delete all dynamically allocated customers
    for (auto customer : customers) {
        delete customer;
    }
    // Set the vector to empty to release any held memory
    customers.clear();
}