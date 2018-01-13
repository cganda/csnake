#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "sl.h"

#define MAX_SNAKE_LENGTH 5

void check();
void end();
void win();
void drawGrid(int numColumns, int numRows, int width, int height, int xOffset, int yOffset, int borderSize);
void drawFood(int gridX, int gridY, int xOffset, int yOffset, int blockWidth, int blockHeight, int borderSize);
void drawSnake(int xs[], int ys[], int size, int xOffset, int yOffset, int blockWidth, int blockHeight, int borderSize);
void moveSnake(int xs[], int ys[], int size, enum direction dir, int numCols, int numRows);
int m[500], n[500], con = 20;
clock_t start, stop;
enum direction{UP, RIGHT, DOWN, LEFT};

int main() {
	printf("Hello, World!\n");

	const int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;
	const int BORDER_SIZE = 1;
	const int NUM_COL = 15;
	const int NUM_ROW = 15;
	const int BLOCK_SIZE = WINDOW_WIDTH / NUM_COL;
	const int MAX_X = 500;
	double movesPerSecond = 3.0;
	int snakeLength = 2;
	int xCoords[MAX_SNAKE_LENGTH] = { NUM_COL / 2, NUM_COL / 2 };
	int yCoords[MAX_SNAKE_LENGTH] = { NUM_ROW / 2, NUM_ROW / 2 - 1 };
	int foodPosX = 10, foodPosY = 10;
	enum direction currentDirection = UP;
	double elapsedTime = 0.0;
	
	int blockWidth = (WINDOW_WIDTH - BORDER_SIZE) / NUM_COL - BORDER_SIZE;
	int blockHeight = (WINDOW_HEIGHT - BORDER_SIZE) / NUM_ROW - BORDER_SIZE;
	int totalWidth = (blockWidth + BORDER_SIZE) * NUM_COL + BORDER_SIZE;
	int totalHeight = (blockHeight + BORDER_SIZE) * NUM_ROW + BORDER_SIZE;
	int xOffset = WINDOW_WIDTH > totalWidth ? (WINDOW_WIDTH - totalWidth) / 2 : (totalWidth - WINDOW_WIDTH) / 2;
	int yOffset = WINDOW_HEIGHT > totalHeight ? (WINDOW_HEIGHT - totalHeight) / 2 : (totalHeight - WINDOW_HEIGHT) / 2;

	slWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, World", 0);
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE)) {
		if (slGetKey(SL_KEY_UP)) {
			currentDirection = UP;
		}
		else if (slGetKey(SL_KEY_RIGHT)) {
			currentDirection = RIGHT;
		}
		else if (slGetKey(SL_KEY_LEFT)) {
			currentDirection = LEFT;
		}
		else if (slGetKey(SL_KEY_DOWN)) {
			currentDirection = DOWN;
		}

		slSetForeColor(1.0, 0.2, 0.2, 0.5);
		slCircleFill(slGetMouseX(), slGetMouseY(), 30.0, 12);

		elapsedTime += slGetDeltaTime();
		if (elapsedTime >= 1 / movesPerSecond) {
			elapsedTime -= (1 / movesPerSecond);
			moveSnake(xCoords, yCoords, snakeLength, currentDirection, NUM_COL, NUM_ROW);
		}
		
		drawGrid(NUM_COL, NUM_ROW, blockWidth, blockHeight, xOffset, yOffset, BORDER_SIZE);
		drawFood(foodPosX, foodPosY, xOffset, yOffset, blockWidth, blockHeight, BORDER_SIZE);
		drawSnake(xCoords, yCoords, snakeLength, xOffset, yOffset, blockWidth, blockHeight, BORDER_SIZE);
		slRender();
	}
	slClose();

	return 0;
}

void drawGrid(int numColumns, int numRows, int width, int height, int xOffset, int yOffset, int borderSize){
	int row, col;
	
	slSetForeColor(0.2, 0.2, 1.0, 0.8);
	for (col = 0; col < numColumns; col++) {
		for (row = 0; row < numRows; row++) {
			slRectangleFill(
				xOffset + (borderSize + width) * col + borderSize + width/2, 
				yOffset + (borderSize + height) * row + borderSize + height/2, 
				width, height
			);
		}
	}
}

void drawFood(int col, int row, int xOffset, int yOffset, int blockWidth, int blockHeight, int borderSize) {
	slSetForeColor(1.0, 0.2, 0.2, 0.8);
	slRectangleFill(
		xOffset + (blockWidth + borderSize) * col + borderSize + blockWidth/2,
		yOffset + (blockHeight + borderSize) * row + borderSize + blockHeight/2,
		blockWidth, blockHeight
	);
	slCircleFill(
		xOffset + (blockWidth + borderSize) * col + borderSize + blockWidth / 2,
		yOffset + (blockHeight + borderSize) * row + borderSize + blockHeight / 2, 
		blockWidth / 2, 12
	);
}

void drawSnake(int xs[], int ys[], int size, int xOffset, int yOffset, int blockWidth, int blockHeight, int borderSize) {
	slSetForeColor(0.2, 1.0, 0.2, 1.0);
	for (int i = 0; i < size; i++) {
		slCircleFill(
			xOffset + (blockWidth + borderSize) * xs[i] + borderSize + blockWidth / 2,
			yOffset + (blockHeight + borderSize) * ys[i] + borderSize + blockHeight / 2,
			blockWidth / 2, 12
		);
	}
}

void moveSnake(int xs[], int ys[], int size, enum direction dir, int numCols, int numRows) {
	int nextX = xs[0], nextY = ys[0];
	switch (dir)
	{
	case UP:
		nextY = (ys[0] + 1) % numRows;
		break;
	case RIGHT:
		nextX = (xs[0] + 1) % numCols;
		break;
	case DOWN:
		nextY = (ys[0] - 1) % numRows;
		break;
	case LEFT:
		nextX = (xs[0] - 1) % numCols;
		break;
	default:
		break;
	}

	for (int i = size - 1; i > 0; i--) {
		xs[i] = xs[i - 1];
		ys[i] = ys[i - 1];
	}
	xs[0] = nextX;
	ys[0] = nextY;
}