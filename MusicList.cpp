#include "MusicList.h"

// Default constructor
MusicList::MusicList() : head(nullptr), tail(nullptr), size(0) {}

// Add track to the end of the list
void MusicList::addMusic(const std::string& track) {
    MusicNode* newMusic = new MusicNode(track); // Create new node
    if (head == nullptr) { // Checking for empty list
        head = tail = newMusic;
    }
    else {
        tail->next = newMusic; // Adding to a non-empty list
        tail = newMusic;
    }
    size++; // Increment the size
}

// Remove from the head of the list and return the first track
std::string MusicList::removeMusic() {
    if (isEmpty()) {
        throw std::out_of_range("The music list is empty"); // Use exception handling
    }

    MusicNode* temp = head; // Store the current head
    std::string track = head->musicTrack; // Get the track
    head = head->next; // Move head to the next node
    if (head == nullptr) { // If the list is now empty
        tail = nullptr;
    }
    delete temp; // Free memory
    size--; // Decrement list size
    return track; // Return the track
}

// Check if the queue is empty
bool MusicList::isEmpty() const {
    return head == nullptr;
}

// Method to get the current size of the queue
int MusicList::getSize() const {
    return size;
}

// Method to read and print all music tracks
void MusicList::listAllMusic() const {
    if (head == nullptr) {
        std::cout << "No music in the list." << std::endl;
        return;
    }

    MusicNode* current = head; // Start from the head of the linked list
    // Iterate through the linked list until the end is reached
    while (current) {
        std::cout << current->musicTrack << std::endl;
        current = current->next;
    }
}

// Destructor
MusicList::~MusicList() {
    while (head != nullptr) {
        MusicNode* temp = head;
        head = head->next;
        delete temp;
    }
}