#include "stdafx.h"
#include "Score.h"


Score::Score() : currentScore(0)
{
}
void Score::Init()
{
	std::string line;
	std::ifstream myfile("../resources/highscores.txt");
	if (myfile.is_open())
	{
		std::string str;
		while (std::getline(myfile, str))
			highScoresText.push_back(str);
		myfile.close();
	}
	for (int i = 0; i < highScoresText.size(); i++)
		highScoresText.at(i) = std::string(9 - highScoresText.at(i).size(), '0') + highScoresText.at(i);
	highestScoreText = highScoresText.at(0);
	highestScore = stoi(highestScoreText);
}

Score& Score::Instance()
{
	static Score instance;
	return instance;
}

void Score::UpdateScores()
{
	currentScoreText = std::string(9 - std::to_string(currentScore).size(), '0') + std::to_string(currentScore);

	if (currentScore > highestScore)
		highestScoreText = currentScoreText;

}

/* 
	Method to insert the current score 
	once its greater than any previous highscores.
	Instead of using a sort method we push the 
	scores down the leaderboard
*/
std::vector<std::string> Score::GetAndSortHighScores()
{
	int numOfLoops = highScoresText.size();
	// Go through all scores
	for (int i = 0; i < numOfLoops;)
	{
		// if current is greater then hiscore
		if (currentScore > stoi(highScoresText.at(i)))
		{
			// score 3 becomes score 4 etc
			for (int j = numOfLoops - 1; j > i; j--)
				highScoresText.at(j) = highScoresText.at(j - 1);
			highScoresText.at(i) = std::string(9 - std::to_string(currentScore).size(), '0') + std::to_string(currentScore);
			break;
		}
		else
			i++;
	}
	// Reset Scores so there updated for next game
	currentScore = 0;
	highestScoreText = highScoresText.at(0);
	highestScore = stoi(highestScoreText);

	return highScoresText;
}

void Score::SaveScoresToFile()
{
	int numOfLoops = highScoresText.size();
	std::ofstream myfile("../resources/highscores.txt");

	for (int i = 0; i < numOfLoops; i++)
		myfile << highScoresText.at(i) << std::endl;

	myfile.close();
}

std::string Score::getCurrentScore()
{
	return currentScoreText;
}
std::string Score::getHighestScore()
{
	return highestScoreText;
}
