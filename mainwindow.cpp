/*
 * Author: Samuel Gebretsion (251173970)
 * Description: Implementation file for the MainWindow class.
 * This file contains the constructor, destructor, and member functions
 * for initializing the game, handling user interactions, and updating the GUI
 * Date: 2024-02-07
 */

#include "mainwindow.h"
#include <QSizePolicy>
#include <QMessageBox>
#include <QFont>

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameLogic(new GameLogic(16, 30, 99))
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(5, 5, 5, 5);
    const int rowSize = 16;
    const int colSize = 30;

    buttons.resize(rowSize);

    for (int row = 0; row < rowSize; ++row) {
        buttons[row].resize(colSize);
    }

    gameLogic = new GameLogic(rowSize, colSize, 99);

    for (int row = 0; row < rowSize; ++row) {
        for (int col = 0; col < colSize; ++col) {

            MineButton *button = new MineButton(this);
            QSizePolicy policy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            policy.setHeightForWidth(true); // Ensure height depends on width for aspect ratio
            button->setSizePolicy(policy);
            button->setMinimumSize(40, 40);
            button->setMaximumSize(50, 50);

            button->setStyleSheet("QPushButton {"
                                  "border: 2px solid #959595;"
                                  "border-radius: 3px;}"
                                  "QPushButton:hover {"
                                  "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                                  "stop:0 #dadbde, stop:1 #f6f7fa);"
                                  "}");
            connect(button, &MineButton::leftClicked, this, [this, row, col]() { handleLeftClick(row, col); });
            connect(button, &MineButton::rightClicked, this, [this, row, col]() { handleRightClick(row, col); });
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;
        }
    }
    mainLayout->addLayout(gridLayout);
    centralWidget->setLayout(mainLayout);
    setWindowTitle("Minesweeper");
    updateButtonStyles();
}

// Destructor
MainWindow::~MainWindow()
{
    delete gameLogic;
}

/*
 * Function name: handleLeftClick
 * Description: Handles left-click events on the game grid, either uncovering cells or triggering game over/win scenarios.
 * Parameters:
 *  - int row: The row number of the clicked cell.
 *  - int col: The column number of the clicked cell.
 * Return: void
 */
void MainWindow::handleLeftClick(int row, int col) {
    if (gameLogic->isCovered(row, col)) {
        bool hitMine = gameLogic->uncoverCell(row, col);
        updateButtonStyles();
        if (hitMine) {
            gameLogic->exploded(row, col);
            revealMines();
            int ret = QMessageBox::critical(this, "Game Over", "You hit a mine!\nWould you like to play again?", QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                resetGame();
            } else {
                close();
            }
        } else if (gameLogic->checkWinCondition()) {
            gameLogic->exploded(row, col);
            revealMines();
            int ret = QMessageBox::information(this, "Congratulations", "You've cleared all mines!\nWould you like to play again?", QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                resetGame();
            } else {
                close();
            }
        }
    }
}

/*
 * Function name: handleRightClick
 * Description: Handles right-click events on the game grid, toggling flags & ?s on cells to mark potential mines.
 * Parameters:
 *  - int row: The row number of the clicked cell.
 *  - int col: The column number of the clicked cell.
 * Return: void
 */
void MainWindow::handleRightClick(int row, int col) {
    if (gameLogic->isCovered(row, col)) {
        gameLogic->toggleFlag(row, col);
        updateButtonStyles();
    }
}

/*
 * Function name: updateButtonStyles
 * Description: Updates the appearance of buttons based on their current state (covered, flagged, etc.).
 * Parameters: None
 * Return: void
 */
void MainWindow::updateButtonStyles() {
    for (int row = 0; row < buttons.size(); ++row) {
        for (int col = 0; col < buttons[row].size(); ++col) {
            MineButton *button = buttons[row][col];
            if (gameLogic->isCovered(row, col)||gameLogic->isFlagged(row, col)||gameLogic->isQuestioned(row, col)) {
                button->setStyleSheet("QPushButton {"
                                      "border: 2px solid #959595;"
                                      "border-radius: 3px;}"
                                      "QPushButton:hover {"
                                      "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                                      "stop:0 #dadbde, stop:1 #f6f7fa);"
                                      "}");
                button->setText("");
                if (gameLogic->isFlagged(row, col)) {
                    button->setStyleSheet("border-image: url(:/Icons/mine_flag.png)");
                }
                else if(gameLogic->isQuestioned(row, col)){
                    button->setText("?");
                    QFont font = button->font();
                    font.setPointSize(24);
                    button->setFont(font);
                }
            } else {
                button->setStyleSheet("2px solid #ababab");
                if (gameLogic->isMine(row, col)) {
                    button->setStyleSheet("border-image: url(:/Icons/bomb_explode.png)");
                } else {
                    int adjacentMines = gameLogic->adjacentMinesCount(row, col);
                    if (adjacentMines > 0) {
                        button->setText(QString::number(adjacentMines));
                        QFont font = button->font();
                        font.setPointSize(24);
                        button->setFont(font);
                    } else {
                        button->setText("");
                    }
                }
            }
        }
    }
}

/*
 * Function name: revealMines
 * Description: Reveals all mines on the grid when the game is over.
 * Parameters: None
 * Return: void
 */
void MainWindow::revealMines() {
    for (int row = 0; row < buttons.size(); ++row) {
        for (int col = 0; col < buttons[row].size(); ++col) {
            if ((gameLogic->isMine(row, col) && !gameLogic->explosionCheck(row, col))) {
                MineButton* button = buttons[row][col];

                button->setStyleSheet("border-image: url(:/Icons/bomb.png)");
                button->setEnabled(false);
            }
        }
    }
}

/*
 * Function name: resetGame
 * Description: Resets the game to its initial state, clearing the grid and reinitializing the game logic.
 * Parameters: None
 * Return: void
 */
void MainWindow::resetGame() {
    gameLogic->reset(16, 30, 99);

    // Reset each button in the grid
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            MineButton *button = buttons[row][col];
            button->reset();
       }
    }
}
