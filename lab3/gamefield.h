#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QColor>
#include <QPushButton>

#include "game.h"

class GameField : public QWidget {
    Q_OBJECT
public:
    GameField(const QString& fileName);
    Game* getGame();
    QPair<int, int> getCharacter();
    QPair<int, int> getSize();
    QVector<QVector<QColor>> getCells();
    QVector<QPair<int, int>> getTargets();
    void paintEvent(QPaintEvent* event) override;

private:
    Game* game = nullptr;
    QLabel* victoryAndScoreLabel = nullptr;
    QPushButton* restartButton = nullptr;

public slots:
    void handleVictoryAchieved();
    void handleRestartGame();
};

#endif // GAMEFIELD_H
