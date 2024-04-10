/*
 * Author: Samuel Gebretsion (251173970)
 * Description: This file contains the main function which initializes the QApplication,
 * sets up the main window of the application, and enters the main event loop.
 * Date: 2024-02-07
 */

#include <QApplication>
#include "MainWindow.h"


int main(int argc, char *argv[]) {
    // Initialize the QApplication with any command line arguments
    QApplication a(argc, argv);

    // Create and display the main window of the application
    MainWindow w;
    w.setWindowIcon(QIcon(":/Icons/bomb.png"));
    w.show();

    // Executes the application and returns the exit code
    return a.exec();

}
