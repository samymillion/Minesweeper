/*
 * Author: Samuel Gebretsion (251173970)
 * Description: Defines the MineButton class, a custom QPushButton that emits signals on left and right clicks
 * Date: 2024-02-07
 */

#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MineButton : public QPushButton {
    Q_OBJECT

public:
    explicit MineButton(QWidget *parent = nullptr); // Constructor with optional parent widget
    void reset(); // Resets the button to its default state

signals:
    void leftClicked(); // Emitted when the button is clicked with the left mouse button
    void rightClicked(); // Emitted when the button is clicked with the right mouse button

protected:
    // Override mouse event handler to detect right and left clicks
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // MINEBUTTON_H
