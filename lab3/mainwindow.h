#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamefield.h"

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void setLider();

protected:

private slots:
    void newGame();
    void resultGame();

private:
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *resultAct;
    QAction *exitAct;

    GameField *gameField;

    QString playerName;
    int numberOfLevels;
    int numberOfChosenLvl;
};

#endif // MAINWINDOW_H
