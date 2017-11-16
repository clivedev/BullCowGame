/**
 * This is the console executable, that makes use of the BullCow class. 
 * This acts as the view in a MVC pattern, and is responsible for all
 * user interaction. For game logic see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText Guess);
void PrintGameSummary();
bool IsPlayingAgain();

FBullCowGame BCGame; // Create an instance of a new game

// Entry point for our application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} 
	while (IsPlayingAgain());

	return 0;
}

// Introduce the game
void PrintIntro()
{
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n\n";
	
	return;
}

// Main game loop
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "You have " << MaxTries << " tries to guess the word." << std::endl;

	// Loop asking for guesses while the game is 
	// NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		// Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls << ", ";
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";

		//PrintGuess(Guess);
	}

	PrintGameSummary();

	return;
}

// Loop continually until the player gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		// Get a guess from the player
		std::cout << "Try " << CurrentTry << ". Please enter your word guess: ";
		std::getline(std::cin, Guess);

		// Check status and give feedback
		Status = BCGame.CheckValidGuess(Guess);
		switch (Status)
		{
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n";
				break;
			case EGuessStatus::Not_Letters:
				std::cout << "Please enter a word with valid letters.\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n";
				break;
			case EGuessStatus::Wrong_Length:
				if (Guess.length() > 0)
				{
					std::cout << "The word is too ";
					if ((int32)Guess.length() < BCGame.GetHiddenWordLength())
						std::cout << "short. ";
					else
						std::cout << "long. ";
				}
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
				break;
			default:
				// assume the guess is valid
				break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors

	return Guess;
}

// Prints the guess back to the player
void PrintGuess(FText Guess)
{
	std::cout << "You guessed the word: " << Guess << std::endl;
	
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "You Win :D Congratulations!\n";
	else
		std::cout << "You Lose :( Better luck next time!\n";

	return;
}

// Check if player wants to play again?
bool IsPlayingAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << "\n\n"; // double newline so the next game is spaced out

	if (toupper(Response[0]) == 'Y')
		return true;

	return false;
}
