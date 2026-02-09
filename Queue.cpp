#include "Queue.h"

// Default Constructor for the Queue class
Queue::Queue() {}

// Enqueue a music track to the queue
void Queue::enqueue(const std::string& track) {
    musicQueue.addMusic(track); // Call the MusicList's method to enqueue a music track
}

// Dequeue a music from the queue
std::string Queue::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty. No music to dequeue."); // Exception handling
    }
    return musicQueue.removeMusic(); // Use MusicList's removeFront method
}

// Check if the queue is empty
bool Queue::isEmpty() const {
    return musicQueue.isEmpty();
}

// Get the size of the queue
int Queue::getSize() const {
    return musicQueue.getSize(); // Use MusicList's getSize method
}

// Method to print all music tracks in the queue
void Queue::printTracks() const {
    musicQueue.listAllMusic();
}

// Destructor
Queue::~Queue() {}