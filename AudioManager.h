#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Queue.h"

class AudioManager {
private:
    sf::Music currentMusic;
    sf::SoundBuffer jumpscareBuffer; // Buffer for jumpscare sound
    sf::Sound jumpscareSound; // Sound object for jumpscare
    Queue musicQueue;

public:
    // Default constructor
    AudioManager();

    // Play music from the provided file path
    void playMusic(const std::string& filePath, bool loop = true, float volume = 50.0f);

    // Play jumpscare sound effect
    void playJumpscareSound(const std::string& filePath, float volume = 100.0f);

    // Stop the currently playing music
    void stopMusic();

    // Stop jumpscare sound
    void stopJumpscareSound();

    // Change the volume of the music
    void setVolume(float volume);

    // Method to enqueue music tracks
    void enqueueTrack(const std::string& track);

    // Play the next track in the queue
    void playNextTrack();

    // Destructor
    ~AudioManager();
};
#endif
