#include <cstdio>
#include "Game.h"
#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
	font = create_font("fonts/glyphs.ppm", "fonts/glyphs.csv");
}

ScoreManager::~ScoreManager()
{
	SaveScoreIfHighScore();
	destroy_font(font);
}

void ScoreManager::Init()
{
	LoadHighScore();
	ResetScore();
}
void ScoreManager::Reset(){
	SaveScoreIfHighScore();
	ResetScore();
}
void ScoreManager::ResetScore()
{
	score = 0;
	sprintf(scoreBuffer, "Score: %d", score);
}

void ScoreManager::IncrementScore()
{
	++score;
	sprintf(scoreBuffer, "Score: %d", score);
}

void ScoreManager::DisplayScore(bool gameOver)
{
	if (!gameOver){
		rasterizer_draw_text(font, 50, 50, scoreBuffer);
	}
	else{
		//rasterizer_clear();
		rasterizer_draw_text(font, 50, 50, scoreBuffer);
		rasterizer_draw_text(font, 50, 70, highScoreBuffer);
		rasterizer_draw_text(font, GAME_RESOLUTION_X / 2, GAME_RESOLUTION_Y / 2, "Game Over!");
	}
}


void ScoreManager::SaveScoreIfHighScore()
{
	if (score <= highScore) {
		return;
	}
	FILE* fp = fopen("score.sav", "w");
	if (fp == NULL) {
		printf("\ncannot save high score");
		return;
	}
	fprintf(fp, "%d", score);
	fclose(fp);
	sprintf(highScoreBuffer, "HighScore: %d", score);
}

void ScoreManager::LoadHighScore()
{
	FILE* fp = fopen("score.sav", "r");
	if (fp == NULL) {
		highScore = 0;
		sprintf(highScoreBuffer, "HighScore: %d", highScore);
		return;
	}
	fscanf(fp, "%d", &highScore);
	sprintf(highScoreBuffer, "HighScore: %d", highScore);
	fclose(fp);
}
