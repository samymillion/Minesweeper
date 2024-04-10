/*
 * Author: Samuel Gebretsion (251173970)
 * Description: Defines the GameLogic class responsible for managing the game state of Minesweeper, including
 *              mine placement, game state updates, and win/loss detection.
 * Date: 2024-02-07
 */

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>

// Represents the game logic for a Minesweeper game
class GameLogic {
public:
    GameLogic(int rows, int cols, int mines);
    bool uncoverCell(int row, int col);
    void toggleFlag(int row, int col);
    bool isMine(int row, int col) const;
    bool isCovered(int row, int col) const;
    bool isFlagged(int row, int col) const;
    int adjacentMinesCount(int row, int col) const;
    bool checkWinCondition() const;
    bool isQuestioned(int row, int col) const;
    bool explosionCheck(int row, int col) const;
    void exploded(int row, int col);
    void reset(int rows, int cols, int mines);

private:
    struct Cell {
        bool isMine = false;
        int adjacentMines = 0;
        bool uncovered = false;
        bool questioned = false;
        bool flagged = false;
        bool exploded = false;
    };

    std::vector<std::vector<Cell>> grid;
    int rowCount;
    int columnCount;
    int mineCount=99;
    int uncoveredCellsCount = 0;

    void placeMines();
    void calculateAdjacentMines();
};

#endif // GAMELOGIC_H
