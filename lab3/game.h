#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QColor>
#include <QPushButton>

class Game : public QObject {
    Q_OBJECT
public:
    Game(const QString& fileName);
    void setGameField(QTextStream&& in);
    void moveCharacter(int dx, int dy);
    bool isWithinBounds(int i, int j);
    bool isVictoryAchieved();
    QPair<int, int> getGameFieldSize();
    QVector<QVector<QColor>> getCells();
    QVector<QPair<int, int>> getTargets();
    int getScore();

    QColor wall = Qt::darkBlue;
    QColor grass = Qt::cyan;
    QColor barrel = Qt::darkCyan;
    QColor target = Qt::darkRed;
    QColor capturedTarget = Qt::red;
    QColor character = Qt::blue;

private:
    bool victoryAchieved = false;
    int score = 0;

    int rowsNum;
    int columnsNum;

    int characterI;
    int characterJ;

    QVector<QVector<QColor>> cells;
    QVector<QPair<int, int>> targets;

    QString originalFileName;

signals:
    void reportVictoryAchieved();

public slots:
    void restartGame();
};

#endif // GAME_H
