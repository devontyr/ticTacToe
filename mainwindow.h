#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton *gridButton;
    QPushButton *buttonSender;

    QVector<QVector<QPushButton *>> buttons2DVector;

    QString player;
    int numMoves;

    bool checkWin();
    void resetBoard();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void buttonClicked();
};
#endif // MAINWINDOW_H
