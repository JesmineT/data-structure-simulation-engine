#include "Storyline.h"

// Storyline class handles and displays narrative text in a game. It stores text, 
// displays it to the console, and allows retrieval of the stored content.
// Constructor to initialize the Storyline object with the provided text
Storyline::Storyline(const std::string& aText)
    : fText(aText) {}

// Method to display the storyline text to the terminal
void Storyline::display() {
    std::cout << fText << std::endl;
}

// Get the storyline text
std::string Storyline::getText() const {
    return fText;
}

// Destructor
Storyline::~Storyline() {}