#include "pch.h"
#include "Game.h"
#include "Timer.h"
#include <Windows.h>

unsigned int hFunction(const string &word)
{
	// Put number of buckets in a variable.
	unsigned int numberOfBucketsChosen = 503;

	// Create an integer of the length of word.
	unsigned int amount = 1;

	unsigned int increment = 0;

	// Write Function that you can pass in and have everthing seperated evenly enough.
	for (unsigned int index = 0; index < word.length(); index++)
	{
		
		amount = amount * word[index];
	}


	unsigned int newAmount = amount * amount;


	// Create an integer for the amount mod bucket count.
	unsigned int bucketNumber = newAmount % numberOfBucketsChosen;

	// Return the result.
	return bucketNumber;

}

Game::Game() : hashTable(503, hFunction)
{
	
}



Game::~Game()
{

}



void Game::LoadArrayUpWithSavedValues()
{
	ifstream inFile;

	inFile.open("HighScores.txt");

	if (inFile.fail())
	{
		
	}
	else
	{
		

		while(true)
		{
			HighScores temp;

			if (!inFile.eof())
			{
				inFile.ignore(INT_MAX, ':');
				inFile.get();

				inFile >> temp.name;

				inFile.ignore(INT_MAX, ':');
				inFile.get();

				inFile >> temp.score;
			}
			else
			{
				break;
			}
			ArrayOfHighScores.push_back(temp);
		}
		




		// Close file.
		inFile.close();
	}
	cout << endl;
}

void Game::LoadDictionary(string FilePath)
{

	// Refernce an ifstream and open.
	ifstream inFile;

	inFile.open(FilePath);


	// Prevent crash if file fails to open.
	if (inFile.fail())
	{
		cout << "File may be opened elsewhere, failed to open." << endl;
		cout << endl;
		system("pause");
	}
	else
	{
		// Create a string to save words as you loop through file.
		string line;

		// Loop through and load words one by one.
		
		while (getline(inFile, line))
		{
			bool apostropheFound = false;
			bool wordLengthAcceptable = false;

			// only store words that are 3 to 6 letters in length
			if (line.length() >= 3 && line.length() <= 6)
			{
				// Let it be known that the word is in acceptable range.
				wordLengthAcceptable = true;

				// Prevent storeing any words with ( ' ) in them.
				for (unsigned int index = 0; index < line.length(); index++)
				{

					// If you found an apostrophe do not store in new list.
					if (line[index] == '\'')
					{
						// Do not store in a bucket.
						apostropheFound = true;

						break;
					}

				}

			}

				// Store eligable word
	  		if (apostropheFound == false && wordLengthAcceptable == true)
	  		{
	  
				string word = line;
	  
	  			hashTable.insert(word);
	  		}
		}



		// Close file.
		inFile.close();

	}

}


void Game::BeginGuessing()
{
	Sleep(25);

	//re-set the moving to next round until proven true.
	_movingToTheNextRound = false;

	// Set and create a HANDLE for cursor.
	CONSOLE_CURSOR_INFO cursorInfo;
	HANDLE out;
	out = GetStdHandle(STD_OUTPUT_HANDLE);


	// Hide the cursor.
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	Sleep(25);

	system("cls");
	cout << endl;
	cout << "Round: " << _round << endl;
	cout << endl;
	cout << "You will have 60 seconds to guess the right word to continue to the next round." << endl;
	cout << endl;
	cout << "Make as many guesses as you can in the time frame to increase the possibility of guessing the correct word." << endl;
	cout << endl;
	cout << "Guessing other words stored in my dictionary will also give you points." << endl;
	cout << endl;
	cout << "Good Luck!" << endl;
	cout << endl;
	system("pause");

	
	string RandomWordFound = DisplayRandomWord();
	Sleep(25);

	Timer bob;
	string userInput;
	string usersPreviousGuesses;
	

	while (bob.getElapsedTime() < 60000)
	{


		// get user input
		if (_kbhit())
		{
			char ch = _getch();

			if (-32 == ch)
			{
				_getch();
				Sleep(20);
			}
				
				

			// did the user press a-z?
			else if (isalpha(ch))
			{
				userInput += tolower(ch);
				Sleep(25);
			}

			// Enter key.
			if (ch == 13)
			{
				// Store users word every time they hit enter.
				ComparePlayersGuesses(userInput);
				Sleep(20);
				usersPreviousGuesses += userInput;
				usersPreviousGuesses += " ";
				userInput = "";
				Sleep(25);

			}

			// Incorperate backspace to erase
			if (ch == 8)
			{
				if (userInput.length() > 0)
				{
					userInput.resize(userInput.length() - 1);
					Sleep(25);
				}
				
			}

		}


		// draw the screen
		system("cls");
		cout << "Round: " << _round << endl;
		cout << endl;
		cout << "Score: " <<  _playersScore << endl;
		cout << "Timer: " << 60 - bob.getElapsedTime() / 1000;
		cout << endl;
		cout << "Your random 6 letter word is: " << RandomWordFound << endl;
		cout << endl;
		cout << userInput << endl;
		cout << endl;
		cout << endl;
		cout << "Previous Guessed words" << endl;
		cout << endl;
		cout << usersPreviousGuesses << endl;
		Sleep(25);
	}

	
	// Did the player guess the word?
	if (_movingToTheNextRound == false)
	{
		cout << "The correct word was: " << _originalWord << endl;
		cout << endl;
		system("pause");
		cout << endl;
		Sleep(25);
		// Replay Option only if the user did not guess the word.
		ReplayOption();
	}
	else if (_movingToTheNextRound == true)
	{
		cout << "The correct word was: " << _originalWord << endl;
		cout << endl;
		system("pause");
		cout << endl;
		_round++;
		Sleep(25);
		BeginGuessing();
	}

	
}

string Game::DisplayRandomWord()
{
	srand((unsigned int)time(0));

	string getThisWord;

	// Keep looking for a word until you find one that is at least 6 letters long.
	do
	{
		// Grab a random bucket.
		// Does not get the upper bounds.
		// Make sure you do not mod by 0, so just add 1 and subtract it back for a true result.
		unsigned int randomBucket = (rand() % (hashTable._bucketCount + 1) - 1);


		// Grab a random word
		// Make sure you do not mod by 0, so just add 1 and subtract it back for a true result.
		unsigned int randomWord = (rand() % (hashTable.ArrayOfBuckets[randomBucket].size() + 1) - 1);




		//Once you have the random word just access it from your ArrayOfBuckets and display it.
		SLLIter<string> iter = hashTable.ArrayOfBuckets[randomBucket];

		// Loop through to move iterator to pull the word.
		for (unsigned int index = 0; index < randomWord; index++)
		{

			++iter;
		}

		// Save the random word that gets thrown out
		getThisWord = iter.current();


	} while (getThisWord.length() != 6);


	// Save the orignial word unscrambled.
	_originalWord = getThisWord;


	//Now that you have a 6 letter word, you need to scramble the words.
	string newScrambledWord = WordScramble(getThisWord);
	Sleep(20);

	// Send out the word that was randomly chosen.
	return newScrambledWord;

}

string Game::WordScramble(string WordToScramble)
{


	string scrambledWord;
	
	unsigned int end = WordToScramble.length();
	for (unsigned int start = 0; start <= end; start++, end--)
	{

		if (start != end)
		{
			scrambledWord += WordToScramble[end];
		}
		
		scrambledWord += WordToScramble[start];

	}

	return scrambledWord;
}

void Game::ComparePlayersGuesses(string Guess)
{

	// Compare if the word passed in is in your dictionary of valid words.
	int inDictionaryOfValidWords = -1;


	// check to see if the word is in your valid dictionary of words.
	inDictionaryOfValidWords = hashTable.find(Guess);
	Sleep(20);

	
	if (inDictionaryOfValidWords != -1)
	{	

		// Checking to see if the user will advance to the next round.
		CheckIfUserGuessedWord(Guess);
		Sleep(20);

		// You can not give them credit if they guess a word that is in your dictionary but not presented with those letters.
		// Also make sure that the player can only guess right if they are using the letters only presented.
		bool correctLettersUsed = false;

		correctLettersUsed = CheckToSeeIfCorrectLettersAreUsed(Guess);
		Sleep(20);
		
		// if true then add to binary tree and update score.
		if (correctLettersUsed == true)
		{
			binaryTree.insert(Guess);
			Sleep(20);
			UpdatePlayersScore(Guess);
			Sleep(20);
		}
		

	}
	

}




void Game::UpdatePlayersScore(string correctWord)
{
	
	unsigned int wordLength = correctWord.length();

	unsigned int score = 1;

	while (wordLength > 1)
	{
		score = score * wordLength;

		wordLength--;
	}

	_playersScore += score;
}


void Game::IsHighScoreGoodEnoughToSave()
{
	system("cls");

	// Create a bool to have access to continue and write to file.
	bool newHighScore = false;

	// Sort here before you check high scores.
	SortHighScores();

	
	// Check to see if the score is higher than the lowest score.
	for (unsigned int index = 0; index < ArrayOfHighScores.size(); index++)
	{
		if (_playersScore > ArrayOfHighScores[index].score)
		{
			newHighScore = true;
		}

	}


	// If we have a new high score go ahead and store into file and array.
	if (newHighScore == true || (ArrayOfHighScores.size() == 0 && _playersScore > 0) || (ArrayOfHighScores.size() != 5 && _playersScore > 0))
	{
		HighScores score;
		score.score = _playersScore;
		cout << "Your score: " << _playersScore << endl;
		cout << endl;

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		ofstream saveScoreFile;

		
		

		saveScoreFile.open("HighScores.txt");

		if (saveScoreFile.fail())
		{
			cout << "Error opening file. File may be opened elsewhere." << endl;
			cout << endl;
			system("pause");
		}
		else
		{
			
			// Sort again to make sure that the lowest score stays at teh bottom.
			SortHighScores();


			cout << "Enter your name to save high score: " << endl;
			cin >> score.name;


			if (ArrayOfHighScores.size() < 5)
			{
				// Go ahead and set the new players score.
				ArrayOfHighScores.push_back(score);
			}
			else if (ArrayOfHighScores.size() == 5)
			{
				ArrayOfHighScores.resize(4);

				ArrayOfHighScores.push_back(score);
			}
			

			// Sort the list.
			SortHighScores();

			// Write out array to file.
			for (unsigned int index = 0; index < ArrayOfHighScores.size(); index++)
			{
				saveScoreFile << "Name: " << ArrayOfHighScores[index].name << '\n';

				saveScoreFile << "Score: " << ArrayOfHighScores[index].score << '\n';

			}
			

		}

		// Close file.
		saveScoreFile.close();

	}


};


void Game::ReplayOption()
{
	// Save current high score.
	IsHighScoreGoodEnoughToSave();

	//Read in the file to present high scores
	ReadInHighScores();


	int choice;
	while (true)
	{
		system("cls");
		cout << "Your final score is: " << _playersScore << endl;
		cout << endl;
		cout << "Would you like to play again? " << endl;
		cout << endl;
		cout << "1) Yes" << endl;
		cout << "2) No" << endl;
		cout << endl;
		cout << "choice? ";
		cin >> choice;


		if (cin.good())
		{
			if (choice < 1 || choice > 2)
			{
				cout << "Please choose a correct number choice." << endl;
				cout << endl;
				system("pause");
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				continue;
			}
			break;
		}

		
		cout << "Please choose a correct number choice." << endl;
		cout << endl;
		system("pause");
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		Sleep(20);

	}

	if (choice == 2)
	{
		return;
	}
	else if (choice == 1)
	{
		binaryTree.clear();
		_playersScore = 0;
		_round = 1;
		BeginGuessing();
	}
}

bool Game::CheckToSeeIfCorrectLettersAreUsed(string playersGuess)
{

	unsigned int playersletters = 0;
	unsigned int originalLetters = 0;

	for (unsigned int index1 = 0; index1 < playersGuess.length(); index1++)
	{
		originalLetters += _originalWord[index1];

		for (unsigned int index2 = 0; index2 < _originalWord.length(); index2++)
		{
			
			if (playersGuess[index1] == _originalWord[index2])
			{

				playersletters += playersGuess[index1];
				break;
				

			}
			
		}

	}

	unsigned int playerGuessValue = playersGuess.length() * 97;
	// Now see if the player over guessed letters compared to their availability.
	if (playersletters <= originalLetters && playersletters >= playerGuessValue)
	{
		return true;
	}


	return false;


}

void Game::CheckIfUserGuessedWord(string playersGuess)
{

	unsigned int playersletters = 0;
	unsigned int originalLetters = 0;

	for (unsigned int index = 0; index < _originalWord.length() && index < playersGuess.length(); index++)
	{

		playersletters += playersGuess[index];
		originalLetters += _originalWord[index];

	}

	if (playersGuess.length() == 6 && playersletters == originalLetters)
	{
		int found = hashTable.find(playersGuess);

		if (found != -1)
		{
			_movingToTheNextRound = true;
		}

	}


	

}

void Game::ReadInHighScores()
{
	system("cls");

	ifstream inFile;

	inFile.open("HighScores.txt");

	if (inFile.fail())
	{
		cout << "Error opening file. File may be opened elsewhere." << endl;
		cout << endl;
	}
	else
	{
		string line;
		cout << "High scores: " << endl;
		cout << endl;
		while (getline(inFile, line))
		{
			cout << line << endl;
			cout << endl;
		}




		// Close file.
		inFile.close();
	}
	cout << endl;
}

void Game::SortHighScores()
{
	if (ArrayOfHighScores.size() == 0)
	{
		return;
	}
	// Start searching for high scores that you can sort if possible.
	for (unsigned int index = 0; index < ArrayOfHighScores.size() - 1; index++)
	{
		for (unsigned int index1 = index + 1; index1 < ArrayOfHighScores.size(); index1++)
		{

			if (ArrayOfHighScores[index].score < ArrayOfHighScores[index1].score)
			{
				HighScores temp = ArrayOfHighScores[index];

				ArrayOfHighScores[index] = ArrayOfHighScores[index1];

				ArrayOfHighScores[index1] = temp;
			}
		}
	}

}





