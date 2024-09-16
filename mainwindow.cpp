#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), buttons2DVector(3), player("X"), numMoves(0) {

    //title
    setWindowTitle("tic tac toe");

    //root widget
    QWidget *center = new QWidget();
    setCentralWidget(center);

    //add tic tac toe board
    QGridLayout *gameGrid = new QGridLayout();

    //layout to arrange vertically
    QVBoxLayout *boxLayout = new QVBoxLayout;
    center->setLayout(boxLayout);

    //header
    QLabel *gameTitle = new QLabel ("tic tac toe game!");
    gameTitle->setAlignment(Qt::AlignCenter);
    QFont font = gameTitle->font();
    font.setBold(true);
    font.setPixelSize(26);
    gameTitle->setFont(font);

    //description
    QLabel *gamedescription = new QLabel ("switch turns placing X's and O's on the board");
    QLabel *gamedescription2 = new QLabel ("first one to get 3 in a row wins");
    gamedescription->setAlignment(Qt::AlignCenter);
    gamedescription2->setAlignment(Qt::AlignCenter);

    boxLayout->addWidget(gameTitle);
    boxLayout->addWidget(gamedescription);
    boxLayout->addWidget(gamedescription2);
    boxLayout->addLayout(gameGrid);

    //putting buttons on the grid and connecting them...
    //add the button pointers to an array to perform operations later
        //access buttons using -- buttons2DVector[row][column]->func();
    for (int row=0; row<3; row++) {
        buttons2DVector[row].resize(3);

        for (int column=0; column<3; column++) {
            QPushButton *gridButton = new QPushButton();
            gameGrid->addWidget(gridButton, row, column, Qt::AlignCenter);
            connect(gridButton, &QPushButton::clicked, this, &MainWindow::buttonClicked);
            buttons2DVector[row][column] = gridButton;
        }
    }
}

MainWindow::~MainWindow() {}

void MainWindow::buttonClicked() {
    //record that a move was made
    numMoves ++;

    //disable the selected button and update it to an X or O
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    buttonSender->setEnabled(false);
    buttonSender->setText(player);

    //check for a win & end game if true
    if (checkWin()) {
        //show message
        QMessageBox::critical(this, "win message", player + "'s won the game!");
        //clear board & start new game
        resetBoard();
    }
    //end game if it's a tie
    else if (numMoves == 9) {
        QMessageBox::information(this, "tie message", "it's a tie!");
        //clear board & start new game
        resetBoard();
    }

    //switch the player each turn
    if (player == "X") {
        player = "O";
    }
    else {
        player = "X";
    }
}

bool MainWindow::checkWin () {
    //check columns
    for (int row=0; row<3; row++) {
        if (buttons2DVector[row][0]->text() == player && buttons2DVector[row][1]->text() == player && buttons2DVector[row][2]->text() == player) {
                return true;
            }
    }
    //check rows
    for (int column=0; column<3; column++){
        if (buttons2DVector[0][column]->text() == player && buttons2DVector[1][column]->text() == player && buttons2DVector[2][column]->text() == player) {
                return true;
            }
    }
    //check diagonals
    if ((buttons2DVector[0][0]->text() == player && buttons2DVector[1][1]->text() == player && buttons2DVector[2][2]->text() == player) ||
        (buttons2DVector[0][2]->text() == player && buttons2DVector[1][1]->text() == player && buttons2DVector[2][0]->text() == player)) {
        return true;
    }
    return false;
}

void MainWindow::resetBoard () {
    for (int row=0; row<3; row++) {
        for (int column=0; column<3; column++) {
            buttons2DVector[row][column]->setEnabled(true);
            buttons2DVector[row][column]->setText("");
            numMoves = 0;
            player = "X";
        }
    }
}
