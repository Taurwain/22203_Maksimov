#include "gamefield.h"

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

GameField::GameField(const QString& fileName) {
    game = new Game(fileName);
    setFocusPolicy(Qt::StrongFocus);
    connect(game, &Game::reportVictoryAchieved, this, &GameField::handleVictoryAchieved);
    restartButton = new QPushButton("Начать заново", this);
    connect(restartButton, &QPushButton::clicked, game, &Game::restartGame);
    connect(restartButton, &QPushButton::clicked, this, &GameField::handleRestartGame);
    update();
}

Game* GameField::getGame() {
    return game;
}

void GameField::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    int rowsNum = game->getGameFieldSize().first;
    int columnsNum = game->getGameFieldSize().second;

    int cellWidth = qMin(width() / columnsNum, height() / rowsNum) * 0.75;

    int totalWidth = cellWidth * columnsNum;
    int totalHeight = cellWidth * rowsNum;

    int startX = (width() - totalWidth) / 2;
    int startY = (height() - totalHeight) / 2;

    QVector<QVector<QColor>> cells = game->getCells();
    QVector<QPair<int, int>> targets = game->getTargets();

    for (int i = 0; i < rowsNum; i++) {
        for (int j = 0; j < columnsNum; j++) {
            QRect cellRect(startX + j * cellWidth, startY + i * cellWidth, cellWidth, cellWidth);
            painter.setBrush(cells[i][j]);
            painter.drawRect(cellRect);
        }
    }

    int pointRadius = cellWidth * 0.1;
    for (auto i : targets) {
        QRect cellRect(startX + i.second * cellWidth, startY + i.first * cellWidth, cellWidth, cellWidth);
        int centerX = cellRect.center().x();
        int centerY = cellRect.center().y();
        if (cells[i.first][i.second] == game->barrel) {
            painter.setBrush(game->capturedTarget);
        } else {
            painter.setBrush(game->target);
        }
        painter.drawEllipse(QPoint(centerX, centerY), pointRadius, pointRadius);
    }

    int buttonWidth = 100;
    int buttonHeight = 30;

    int buttonY = startY + totalHeight / 2 - buttonHeight / 2;

    restartButton->setGeometry(width() - buttonWidth, buttonY, buttonWidth, buttonHeight);
    if (victoryAndScoreLabel != nullptr) {
        victoryAndScoreLabel->setGeometry(startX, startY / 4, totalWidth, startY);
        victoryAndScoreLabel->show();
    }
}

void GameField::handleVictoryAchieved() {
    int rowsNum = game->getGameFieldSize().first;
    int columnsNum = game->getGameFieldSize().second;

    int cellWidth = qMin(width() / columnsNum, height() / rowsNum) * 0.75;

    int totalWidth = cellWidth * columnsNum;
    int totalHeight = cellWidth * rowsNum;

    int startX = (width() - totalWidth) / 2;
    int startY = (height() - totalHeight) / 2;

    QString score = QString::number(game->getScore());

    victoryAndScoreLabel = new QLabel(this);
    victoryAndScoreLabel->setText("Победа! Результат: " + score);
    victoryAndScoreLabel->setFont(QFont("Arial", 12, QFont::Bold));
    victoryAndScoreLabel->setAlignment(Qt::AlignCenter);
    victoryAndScoreLabel->setGeometry(startX, startY / 4, totalWidth, startY);
    victoryAndScoreLabel->show();
}

void GameField::handleRestartGame() {
    if (victoryAndScoreLabel != nullptr) {
        delete victoryAndScoreLabel;
        victoryAndScoreLabel = nullptr;
    }
    update();
}
