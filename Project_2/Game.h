#pragma once
#include "HTable.h"
#include "BST.h"
#include <vector>




class Game
{
public:
	Game();
	~Game();


	struct HighScores
	{
		char name[64];

		unsigned int score = 0;

	};

	void LoadArrayUpWithSavedValues();

	vector<HighScores> ArrayOfHighScores;

	void LoadDictionary(string FilePath = "engldict.txt");

	HTable<string> hashTable;

	BST<string> binaryTree;

	void BeginGuessing();

	string DisplayRandomWord();

	string WordScramble(string WordToScramble);

	void ComparePlayersGuesses(string Guess);

	void UpdatePlayersScore(string correctWord);

	void IsHighScoreGoodEnoughToSave();

	bool _play = true;

	bool _movingToTheNextRound = false;

	unsigned int _playersScore = 0;

	unsigned int _round = 1;

	void ReplayOption();

	string _originalWord;

	bool CheckToSeeIfCorrectLettersAreUsed(string playersGuess);

	void CheckIfUserGuessedWord(string playersGuess);

	void ReadInHighScores();

	void SortHighScores();

};



