#ifndef _SCORE_MANAGER_H_
#define _SCORE_MANAGER_H_

#include "../swr/swr_rfont.h"
#include "../swr/swr_rasterizer.h"

class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();
	void Init();
	void Reset();
	void ResetScore();
	void IncrementScore();
	void DisplayScore(bool gameOver);
	void SaveScoreIfHighScore();
	void LoadHighScore();
private:
	int score;
	int highScore;
	swr_rfont* font;
	char scoreBuffer[256];
	char highScoreBuffer[256];
};
#endif