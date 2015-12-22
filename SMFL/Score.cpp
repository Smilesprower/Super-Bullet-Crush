#include "stdafx.h"
#include "Score.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Text.hpp"

Score::Score() : currentScore(0)
{
}
void Score::Init()
{
	highScores = std::vector<int>();
	highScoresText = std::vector<std::string>();

	std::string line;
	std::ifstream myfile("../resources/highscores.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::istringstream iss(line);
			int n;
			while (iss >> n)
			{
				highScores.push_back(n);
			}
		}
		myfile.close();
	}
	for (int i = 0; i < highScores.size(); i++)
	{
		highScoresText.push_back(std::to_string(highScores.at(i)));
		highScoresText.at(i) = std::string(9 - highScoresText.at(i).size(), '0') + highScoresText.at(i);
	}
	highestScoreText = highScoresText.at(0);
}

Score& Score::Instance()
{
	static Score instance;
	return instance;
}

void Score::UpdateScores()
{
	currentScoreText = std::string(9 - std::to_string(currentScore).size(), '0') + std::to_string(currentScore);

	if (currentScore > highScores.at(0))
		highestScoreText = currentScoreText;

}

std::vector<std::string> Score::GetAndSortHighScores()
{
	int placeInTable = 0;
	int numOfLoops = highScores.size();
	// Go through all scores
	for (int i = 0; i < numOfLoops;)
	{
		// if current is greater then hiscore
		if (currentScore > highScores.at(i))
		{
			// 5 = 4, 4 = 3, etc
			for (int j = numOfLoops - 1; j > i; j--)
				highScoresText.at(j) = highScoresText.at(j - 1);
			highScoresText.at(i) = std::string(9 - std::to_string(currentScore).size(), '0') + std::to_string(currentScore);
			break;
		}
		else
			i++;
	}
	return highScoresText;
}