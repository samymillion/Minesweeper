/*
 * Author: Samuel Gebretsion (251173970)
 * Description: This file provides functionality for the MineButton class,
 * including custom signal emissions for left and right mouse clicks
 * and a reset method to return the button to its default state.
 * Date: 2024-02-07
 */

#include "MineButton.h"

// Constructor: Initializes a QPushButton with an optional parent
MineButton::MineButton(QWidget *parent) : QPushButton(parent) {
}

// MousePressEvent: Overrides the QPushButton mousePressEvent to handle custom click behavior
void MineButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit leftClicked(); // Emit leftClicked signal for a left mouse button press
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(); // Emit rightClicked signal for a right mouse button press
    }
    // Base class event handling is not called since we're fully handling the event here
}

// Reset: Resets the button to its default visual and functional state
void MineButton::reset() {
    this->setText("");
    this->setIcon(QIcon()); // Clear any icon set
    this->setEnabled(true);
    this->setStyleSheet("QPushButton {"
                         "border: 2px solid #959595;"
                         "border-radius: 3px;}"
                         "QPushButton:hover {"
                         "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                         "stop:0 #dadbde, stop:1 #f6f7fa);"
                         "}"); // Reset any custom styling
}
