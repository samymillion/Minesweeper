#include "DifficultyDialog.h"

DifficultyDialog::DifficultyDialog(QWidget *parent) : QDialog(parent) {
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->addItem("Easy", QVariant(10)); // 10 mines
    difficultyComboBox->addItem("Medium", QVariant(40)); // 40 mines
    difficultyComboBox->addItem("Hard", QVariant(99)); // 99 mines

    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &DifficultyDialog::accept);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(difficultyComboBox);
    layout->addWidget(okButton);

    setLayout(layout);
    setWindowTitle("Select Difficulty");
}

int DifficultyDialog::selectedDifficulty() const {
    return difficultyComboBox->currentData().toInt();
}
