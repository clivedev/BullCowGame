#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All values initialised as zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Letters,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame
{
public:
	// NB: const prevents getter methods from modifying the private properties
	FBullCowGame(); // constructor
	
	int32 GetMaxTries() const; // get maximum number of tries allowed
	int32 GetCurrentTry() const; // get the current try count
	int32 GetTriesRemaining() const; // get remaining number of tries
	int32 GetNumberOfBulls() const; // get number of bulls in the word
	int32 GetNumberOfCows() const; // get number of cows in the word
	int32 GetHiddenWordLength() const; // get the length of the word selected
	bool IsGameWon() const; // have we guessed the word?
	
	void SetMaxTries(); // set maximum number of tries allowed
	void NewGame(); // start a new game
	void PickWord(); // pick a word to guess
	void Reset(); // TODO make a more rich return value

	// Counts bulls & cows, and increases try count assuming valid guess
	FBullCowCount SubmitValidGuess(FString Guess); // submit a word to guess
	EGuessStatus CheckValidGuess(FString Guess) const; // check the guess is valid

// Ignore this bit for now...  vv
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bMyGameWon;

	bool IsIsogram(FString Guess) const; // is the word entered an isogram?
	bool IsLowercase(FString Guess) const; // is the word entered lowercase?
	bool HasValidLetters(FString Guess) const; // does the word entered have valid letters?
};