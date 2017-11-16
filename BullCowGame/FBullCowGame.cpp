#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetTriesRemaining() const { return 0; }
int32 FBullCowGame::GetNumberOfBulls() const { return 0; }
int32 FBullCowGame::GetNumberOfCows() const { return 0; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bMyGameWon; }

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// Treat 0 and 1 as an isogram
	if (Guess.length() < 2) return true;
	
	// Declare map to store if we have letter already
	TMap<char, bool> LetterSeen;

	// Loop over each letter in the word
	for (auto Letter : Guess) // auto (compiler detects the data type of Letter)
	{
		Letter = tolower(Letter); // Handle mixed case

		// If the letter is already in the map then guess is not an isogram
		if (LetterSeen[Letter] == true)
			return false;
		else // Add the letter to our map
			LetterSeen[Letter] = true;
	}

	return true; // for example in cases where \0 (null) is entered
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	// Loop over each letter in the word
	for (auto Letter : Guess) // auto (compiler detects the data type of Letter)
	{
		if (Letter != tolower(Letter)) // Letter entered was NOT lowercase
			return false;
	}

	return true; // for example in cases where \0 (null) is entered
}

bool FBullCowGame::HasValidLetters(FString Guess) const
{
	// Now check if the word contains any invalid characters 
	// i.e. spaces, null characters (\0), non alphabetical
	for (auto Letter : Guess) // auto (compiler detects the data type of Letter)
	{
		// Only allow letters inbetween the range of a-z (lowercase)
		// a=97, b=98, c=99 ... x=120, y=121, z=122
		if (Letter < 97 || Letter > 122)
			return false;
	}

	return true;
}

void FBullCowGame::SetMaxTries() { return; }
void FBullCowGame::NewGame() { return; }
void FBullCowGame::PickWord() { return; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries   = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bMyGameWon = false;

	return;
}

// Receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	FBullCowCount BullCowCount; 

	// Increment our current try as we have received a valid guess
	MyCurrentTry++;

	// Set the length of the hidden word and guess word
	int32 HiddenWordLength = GetHiddenWordLength();
	int32 GuessWordLength  = Guess.length();

	// Loop through all letters in the hidden word
	for(int32 i = 0; i < HiddenWordLength; i++)
	{
		// Compare letters against the guessed word
		for (int32 j = 0; j < GuessWordLength; j++)
		{
			// If the letters match
			if(MyHiddenWord[i] == Guess[j])
			{
				if(i == j) // If they are in the same place
					BullCowCount.Bulls++;
				else // Otherwise if in the wrong place
					BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLength)
		bMyGameWon = true;

	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckValidGuess(FString Guess) const
{
	if (!IsLowercase(Guess))
		return EGuessStatus::Not_Lowercase;
	else if (!HasValidLetters(Guess))
		return EGuessStatus::Not_Letters; 
	else if (!IsIsogram(Guess))
		return EGuessStatus::Not_Isogram;
	if (Guess.length() != GetHiddenWordLength())
		return EGuessStatus::Wrong_Length;

	return EGuessStatus::OK;
}
