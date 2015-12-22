#include <vector>
#include <string>

class Score
{
public:
	static Score& Instance();
	void Init();
	void UpdateScores();
	std::vector<std::string> GetAndSortHighScores();

	int currentScore;
	std::string currentScoreText;
	std::string highestScoreText;


private:
	Score();
	std::vector<int> highScores;
	std::vector<std::string> highScoresText;
};