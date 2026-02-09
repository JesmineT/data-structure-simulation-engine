#ifndef STORYLINE_H
#define STORYLINE_H
#include <iostream>
#include <string>

// Storyline class handles and displays narrative text in a game. It stores text, 
// displays it to the console, and allows retrieval of the stored content.
class Storyline
{
private:
    std::string fText; // Text for the storyline

public:
    // Constructor to initialize the Storyline object with the provided text
    Storyline(const std::string& aText);

    // Method to display the storyline text to the terminal
    void display();

    // Get the storyline text
    std::string getText() const;

    // Destructor
    ~Storyline();
};
#endif
