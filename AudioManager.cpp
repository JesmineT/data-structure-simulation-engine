#include "AudioManager.h"

// Default constructor
AudioManager::AudioManager() {}

// Play music from the provided file path
void AudioManager::playMusic(const std::string& filePath, bool loop, float volume) {
    if (!currentMusic.openFromFile(filePath)) {
        std::cerr << "Error loading music: " << filePath << std::endl;
        return;
    }
    currentMusic.setLoop(loop);
    currentMusic.setVolume(volume);
    currentMusic.play();
}

// Play jumpscare sound effect
void AudioManager::playJumpscareSound(const std::string& filePath, float volume) {
    if (!jumpscareBuffer.loadFromFile(filePath)) {
        std::cerr << "Error loading jumpscare sound: " << filePath << std::endl;
        return;
    }
    jumpscareSound.setBuffer(jumpscareBuffer);
    jumpscareSound.setVolume(volume);
    jumpscareSound.play();
}

// Stop the currently playing music
void AudioManager::stopMusic() {
    currentMusic.stop();
}

// Stop jumpscare sound
void AudioManager::stopJumpscareSound() {
    jumpscareSound.stop();
}

// Change the volume of the music
void AudioManager::setVolume(float volume) {
    currentMusic.setVolume(volume);
}

// Method to enqueue music tracks
void AudioManager::enqueueTrack(const std::string& track) {
    musicQueue.enqueue(track);
}

// Play the next track in the queue
void AudioManager::playNextTrack() {
    if (!musicQueue.isEmpty()) {
        std::string nextTrack = musicQueue.dequeue();
        playMusic(nextTrack); // Play the dequeued track
    }
    else {
        std::cout << "No more tracks in the queue." << std::endl;
    }
}

// Destructor
AudioManager::~AudioManager() {}