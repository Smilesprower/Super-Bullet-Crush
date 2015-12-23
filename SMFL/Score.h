#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>

class Score
{
public:
	static Score& Instance();
	void Init();
	void UpdateScores();
	std::string getCurrentScore();
	std::string getHighestScore();
	void SaveScoresToFile();
	std::vector<std::string> GetAndSortHighScores();

	int currentScore;

private:
	Score();
	int highestScore;
	std::vector<std::string> highScoresText;
	std::string currentScoreText;
	std::string highestScoreText;
};