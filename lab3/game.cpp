#include "game.h"

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

Game::Game(const QString& fileName) : originalFileName(fileName) {
    restartGame();
}

QVector<QVector<QColor>> Game::getCells() {
    return cells;
}

QVector<QPair<int, int>> Game::getTargets() {
    return targets;
}

QPair<int, int> Game::getGameFieldSize() {
    return {rowsNum, columnsNum};
}

int Game::getScore() {
    return score;
}

void Game::moveCharacter(int dx, int dy) {
    if (victoryAchieved) {
        return;
    }

    if (!isWithinBounds(characterI + dy, characterJ + dx)) {
        return;
    }

    int nextCellI = characterI + 2 * dy;
    int nextCellJ = characterJ + 2 * dx;

    if (cells[characterI + dy][characterJ + dx] != wall) {
        if (cells[characterI + dy][characterJ + dx] == barrel) {
            if (!isWithinBounds(nextCellI, nextCellJ)) {
                return;
            }

            if (cells[nextCellI][nextCellJ] == grass) {
                std::swap(cells[nextCellI][nextCellJ], cells[characterI + dy][characterJ + dx]);
            } else {
                return;
            }
        }
        std::swap(cells[characterI + dy][characterJ + dx], cells[characterI][characterJ]);
        characterI = characterI + dy;
        characterJ = characterJ + dx;
        score++;
    }

    if (isVictoryAchieved()) {
        emit reportVictoryAchieved();
    }
}

bool Game::isWithinBounds(int i, int j) {
    return i >= 0 && i < rowsNum && j >= 0 && j < columnsNum;
}

bool Game::isVictoryAchieved() {
    int targetsNum = 0;
    for (auto i : targets) {
        if (cells[i.first][i.second] == barrel) {
            targetsNum++;
        }
    }
    if (targets.size() == targetsNum) {
        victoryAchieved = true;
    }
    return victoryAchieved;
}

void Game::restartGame() {
    victoryAchieved = false;
    score = 0;
    QFile file(originalFileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open the file!";
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    QStringList parts = line.split(' ', Qt::SkipEmptyParts);
    rowsNum = parts.at(0).toInt();
    columnsNum = parts.at(1).toInt();

    cells = QVector<QVector<QColor>>(rowsNum, QVector<QColor>(columnsNum, grass));
    setGameField(std::move(in));
    file.close();
}

void Game::setGameField(QTextStream&& in) {
    for (int row = 0; row < rowsNum; row++) {
        QString line = in.readLine();
        for (int column = 0; column < columnsNum; column++) {
            QChar c = line.at(column);
            if(c == '#') {
                cells[row][column] = wall;
            } else if(c == '.') {
                targets.append({row, column});
                cells[row][column] = grass;
            } else if(c == 'B') {
                cells[row][column] = barrel;
            } else if(c == 'X') {
                cells[row][column] = barrel;
                targets.append({row, column});
            } else if(c == '@') {
                characterI = row;
                characterJ = column;
                cells[characterI][characterJ] = character;
            } else if(c == '+') {
                characterI = row;
                characterJ = column;
                cells[characterI][characterJ] = character;
                targets.append({row, column});
            } else if(c == ' ') {
                cells[row][column] = grass;
            } else {
                qDebug() << "The unknown symbol:" << c << "!";
                return;
            }
        }
    }
}
