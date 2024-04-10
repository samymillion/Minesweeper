/*
 * Author: Samuel Gebretsion (251173970)
 * Description: Implementation of the GameLogic class functions for Minesweeper game logic, including initializing the game board,
 *              handling cell uncovering, flagging, and checking win conditions.
 * Date: 2024-02-07
 */

#include "gamelogic.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

// Constructor initializes the game with a given size and number of mines
GameLogic::GameLogic(int rows, int cols, int mines)
    : rowCount(rows), columnCount(cols), mineCount(mines), uncoveredCellsCount(0) {
    grid.resize(rowCount, std::vector<Cell>(columnCount));
    placeMines();
    calculateAdjacentMines();
}

// Randomly places mines on the grid
void GameLogic::placeMines() {
    srand(time(NULL)); // Seed the random number generator
    int placedMines = 0;
    while (placedMines < mineCount) {
        int row = rand() % rowCount;
        int col = rand() % columnCount;
        if (!grid[row][col].isMine) {
            grid[row][col].isMine = true;
            ++placedMines;
        }
    }
}

// Calculates the number of adjacent mines for each cell
void GameLogic::calculateAdjacentMines() {
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            if (grid[row][col].isMine) continue;
            // Increment adjacent mine count for neighboring cells
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < rowCount && newCol >= 0 && newCol < columnCount && grid[newRow][newCol].isMine) {
                        grid[row][col].adjacentMines++;
                    }
                }
            }
        }
    }
}

// Uncover a cell and recursively uncover adjacent cells if they have no adjacent mines
bool GameLogic::uncoverCell(int row, int col) {
    if (row < 0 || row >= rowCount || col < 0 || col >= columnCount || grid[row][col].uncovered) {
        return false;
    }

    grid[row][col].uncovered = true;
    grid[row][col].flagged = false;
    grid[row][col].questioned = false;
    uncoveredCellsCount++;

    // If the cell has no adjacent mines, recursively uncover adjacent cells
    if (grid[row][col].adjacentMines == 0 && !grid[row][col].isMine) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < rowCount && newCol >= 0 && newCol < columnCount) {
                    uncoverCell(newRow, newCol); // Recursive call
                }
            }
        }
    }

    return grid[row][col].isMine;
}

// Reset the game with a new configuration
void GameLogic::reset(int rows, int cols, int mines) {
    rowCount = rows;
    columnCount = cols;
    mineCount = mines;
    uncoveredCellsCount = 0;

    // Clear and resize the grid
    grid.clear();
    grid.resize(rowCount, std::vector<Cell>(columnCount));

    // Re-initialize the game state
    placeMines();
    calculateAdjacentMines();
}

// Toggle a flag on a cell, function handles right clicks on cells
void GameLogic::toggleFlag(int row, int col) {

    if (!grid[row][col].uncovered) {
        if (!grid[row][col].flagged && !grid[row][col].questioned) { //if covered, flag the cell
            grid[row][col].flagged = true;
        } else if (grid[row][col].flagged) { //if flagged, question mark the cell
            grid[row][col].flagged = false;
            grid[row][col].questioned = true;
        } else if (grid[row][col].questioned) { //if questioned, cover the cell
            grid[row][col].questioned = false;
        }
    }
}

//Return whether a given cell is mined or not
bool GameLogic::isMine(int row, int col) const {
    return grid[row][col].isMine;
}

//Return whether a given cell is covered(not uncovered)
bool GameLogic::isCovered(int row, int col) const {
    return !grid[row][col].uncovered;
}

//Return whether a given cell is flagged
bool GameLogic::isFlagged(int row, int col) const {
    return grid[row][col].flagged;
}

//Return whether a given cell is questioned
bool GameLogic::isQuestioned(int row, int col) const {
    return grid[row][col].questioned;
}

//Return the number of adjacent mines to an uncovered cell
int GameLogic::adjacentMinesCount(int row, int col) const {
    return grid[row][col].adjacentMines;
}

//Return whether a cell has exploded(lost you the game)
bool GameLogic::explosionCheck(int row, int col) const {
    return grid[row][col].exploded;
}

//Set given cell to exploded
void GameLogic::exploded(int row, int col){
    grid[row][col].exploded = true;
}

//Return whether the user has cleared all the mines or not
bool GameLogic::checkWinCondition() const {
    return uncoveredCellsCount == rowCount * columnCount - mineCount;
}
