#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "sl.h"

void check();
void end();
void win();
void drawGrid(int numColumns, int numRows, int width, int height, int xOffset, int yOffset, int borderSize);
void drawFood(int gridX, int gridY, int xOffset, int yOffset, int blockWidth, int blockHeight, int borderSize);
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
	const int MAX_SNAKE_LENGTH = 5;
	int x, y, speed = 100;
	int snakeLength = 1;
	int foodPosX = 10, foodPosY = 10;
	enum direction currentDirection = UP;
	
	int blockWidth = (WINDOW_WIDTH - BORDER_SIZE) / NUM_COL - BORDER_SIZE;
	int blockHeight = (WINDOW_HEIGHT - BORDER_SIZE) / NUM_ROW - BORDER_SIZE;
	int totalWidth = (blockWidth + BORDER_SIZE) * NUM_COL + BORDER_SIZE;
	int totalHeight = (blockHeight + BORDER_SIZE) * NUM_ROW + BORDER_SIZE;
	int xOffset = WINDOW_WIDTH > totalWidth ? (WINDOW_WIDTH - totalWidth) / 2 : (totalWidth - WINDOW_WIDTH) / 2;
	int yOffset = WINDOW_HEIGHT > totalHeight ? (WINDOW_HEIGHT - totalHeight) / 2 : (totalHeight - WINDOW_HEIGHT) / 2;

	slWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, World", 0);
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE)) {
		slSetForeColor(1.0, 0.2, 0.2, 0.5);
		slCircleFill(slGetMouseX(), slGetMouseY(), 30.0, 12);
		
		drawGrid(NUM_COL, NUM_ROW, blockWidth, blockHeight, xOffset, yOffset, BORDER_SIZE);
		drawFood(foodPosX, foodPosY, xOffset, yOffset, blockWidth, blockHeight, BORDER_SIZE);

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

void drawSnake(int xs[], int ys[], int size) {

}