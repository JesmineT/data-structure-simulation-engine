#ifndef	STORYITERATOR1D_H
#define STORYITERATOR1D_H
#include <iostream>
#include <sstream>
#include "Storyline.h"

class StoryIterator1D {
private:
	// The attributes here are meant to reference (not copy) a container
	Storyline* fArrayElements;
	const int fLength;

	// We use this index to keep track of which element is currently selected
	int fIndex;

public:
	// Constructor
	StoryIterator1D(Storyline aArray[], const int aLength, int aStart = 0);

	// Returns a reference to the current element in the array that the iterator is pointing to.
	Storyline& operator*() const; // for accessing the selected element's value 

	// Pre-increment operator
	StoryIterator1D& operator++(); // step forward - return new position

	// Post-increment operator
	StoryIterator1D operator++(int); // step forward - return old position 

	// Pre-decrement operator
	StoryIterator1D& operator--(); // step backward - return new position

	// Post-decrement operator
	StoryIterator1D operator--(int); // step backward - return old position 

	// Equality comparison: returns true if array and index match
	bool operator==(const StoryIterator1D& aOther) const;

	// Inequality comparison: returns true if array and index dont match
	bool operator!=(const StoryIterator1D& aOther) const;

	// Returns a copy of this iterator, index at the beginning
	StoryIterator1D begin() const;

	// Returns a copy of this iterator, index at the end
	StoryIterator1D end() const;

	// Get the size/fLength
	int getSize() const;

	// Get the current index
	int getIndex() const;

	// Destructor
	~StoryIterator1D();
};
#endif