#ifndef MUSICLIST_H
#define MUSICLIST_H
#include <iostream>
#include <string>

class MusicList {
private:
    // Struct representing each node in the linked list
    struct MusicNode {
        std::string musicTrack; // The music track name
        MusicNode* next; // Pointer to the next node in the list

        // Constructor to initialize a MusicNode with a track name
        MusicNode(const std::string& track)
            : musicTrack(track), next(nullptr) {} // Initialize next to nullptr by default
    };

    MusicNode* head;  // Pointer to the first node in the list (head of the linked list)
    MusicNode* tail;  // Pointer to the last node in the list (tail of the linked list)
    int size;         // Tracks the number of music tracks (nodes) in the list

public:
    // Default constructor
    MusicList();

    // Add track to the list
    void addMusic(const std::string& track);

    // Remove the track from the list
    std::string removeMusic();

    // Check if the list is empty
    bool isEmpty() const;

    // Method to get the current size of the list
    int getSize() const;

    // Method to print all tracks in the list
    void listAllMusic() const;

    // Destructor
    ~MusicList();
};
#endif