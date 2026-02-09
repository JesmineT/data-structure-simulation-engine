#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
#include "MusicList.h"

class Queue {
private:
    MusicList musicQueue;

public:
    // Default Constructor for the Queue class
    Queue();

    // Enqueue a music track
    void enqueue(const std::string& track);

    // Dequeue a music track
    std::string dequeue();

    // Check if the queue is empty
    bool isEmpty() const;

    // Get the size of the queue
    int getSize() const;

    // Method to print all the music in the queue
    void printTracks() const;

    // Destructor
    ~Queue();
};
#endif
