#include "StoryIterator1D.h"

// Constructor: initializes the array pointer, size and starting element index
StoryIterator1D::StoryIterator1D(Storyline aArray[], const int aLength, int aStart)
	: fArrayElements(aArray), fLength(aLength), fIndex(aStart) {}

// Returns the current element the iterator points to
Storyline& StoryIterator1D::operator*() const {
	return fArrayElements[fIndex]; // Access the current story window
}

// Pre-increment operator: move to the next element and return the updated iterator
StoryIterator1D& StoryIterator1D::operator++() {
	// Check if already at the end of the array
	if (fIndex < fLength - 1) { // -1 because fLength is the size, and index starts from 0
		fIndex++; // Increment the index to point to the next element
	}
	else {
		std::cout << "Already at the end of the story." << std::endl;
	}
	return *this; // Return the updated iterator
}


// Post-increment operator: move to the next element but return the old position
StoryIterator1D StoryIterator1D::operator++(int) {
	StoryIterator1D temp = *this; // create a copy of the current iterator
	// Check if incrementing would go out of bounds
	if (fIndex < fLength) {
		fIndex++; // increment the index
	}
	else {
		std::cout << "Already at the end of the story." << std::endl;
	}
	return temp; // return the copy, which has the old position
}


// Pre-decrement operator: move to the previous element and return the updated iterator
StoryIterator1D& StoryIterator1D::operator--() {
	// Check if the current index is greater than 0 (not at the beginning)
	if (fIndex > 0) {
		fIndex--; // Move to the previous element
	}
	else {
		std::cout << "Already at the beginning of the story." << std::endl;
	}
	return *this; // Return the updated iterator
}

// Post-decrement operator: move to the previous element but return the old position
StoryIterator1D StoryIterator1D::operator--(int) {
	StoryIterator1D temp = *this; // create a copy of the current iterator
	// Check if decrementing would go out of bounds
	if (fIndex > 0) {
		fIndex--; // decrement the index
	}
	else {
		std::cout << "Already at the beginning of the story." << std::endl;
	}
	return temp; // return the copy, which has the old position
}

// Equality comparison: returns true if array and index match
bool StoryIterator1D::operator==(const StoryIterator1D& aOther) const {
	return ((fArrayElements == aOther.fArrayElements) && (fIndex == aOther.fIndex));
}

// Inequality comparison: returns true if array and index dont match
bool StoryIterator1D::operator!=(const StoryIterator1D& aOther) const {
	return !(*this == aOther);
}

// Returns a copy of this iterator, index at the beginning
StoryIterator1D StoryIterator1D::begin() const {
	return StoryIterator1D(fArrayElements, fLength, 0);
}

// Returns a copy of this iterator, index at the end
StoryIterator1D StoryIterator1D::end() const {
	return StoryIterator1D(fArrayElements, fLength, fLength);
}

// Get the size/fLength
int StoryIterator1D::getSize() const {
	return fLength;
}

// Get the current index
int StoryIterator1D::getIndex() const {
	return fIndex;
}

// Destructor
StoryIterator1D::~StoryIterator1D() {}
