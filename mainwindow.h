/*
 * Author: Samuel Gebretsion (251173970)
 * Description: Defines the MainWindow class, which sets up the GUI for the Minesweeper game, including the game grid and game logic integration.
 * Date: 2024-02-07
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QIcon>
#include <QSizePolicy>
#include <QPushButton>
#include "gamelogic.h"
#include "minebutton.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLeftClick(int row, int col);
    void handleRightClick(int row, int col);

private:
    void updateButtonStyles();
    void resetGame();
    void revealMines();
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVector<QVector<MineButton*>> buttons; // 2D vector of MineButton pointers
    GameLogic *gameLogic; // Instance of the game logic
};

#endif // MAINWINDOW_H
