#include "game.h"
#include <QtWidgets>
#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    QWidget *info = new QWidget;
    setCentralWidget(info);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel *infoLabel = new QLabel(tr("SOKOBAN"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);
    info->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Sokoban"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

void MainWindow::newGame() {
    playerName = QInputDialog::getText(this, tr("Введите свое имя"), tr("Имя:"));
    playerName = playerName.left(20);
    playerName = playerName.replace('\n',' ');

    QStringList levelNames;
    QDir levelsDir("levels");
    QStringList levels = levelsDir.entryList(QStringList() << "*.txt", QDir::Files);

    for (const QString& level : levels) {
        QFileInfo fileInfo(level);
        levelNames.append(fileInfo.baseName());
    }

    QStringList levelNumbers;

    for (int i = 1; i <= levelNames.size(); i++) {
        levelNumbers.append(QString::number(i));
    }

    numberOfLevels = levels.size();

    QString selectedLevelNumber = QInputDialog::getItem(this, tr("Выбрать уровень"), tr("Уровень:"), levelNumbers, 0, false);

    if (!selectedLevelNumber.isEmpty()) {
        int index = selectedLevelNumber.toInt() - 1;
        if (index >= 0 && index < levels.size()) {
            numberOfChosenLvl = index + 1;
            gameField = new GameField(levelsDir.filePath(levels[index]));
            connect(gameField->getGame(), &Game::reportVictoryAchieved, this, &MainWindow::setLider);
            setCentralWidget(gameField);
        }
    }
}

void MainWindow::setLider() {
    QDir levelsDir("liders");
    QFile file(levelsDir.filePath("lid" + QString::number(numberOfChosenLvl) + ".txt"));
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream in(&file);
        QStringList leaders;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" ");
            QString name = parts.at(0);
            QString score = parts.at(1);
            if (name.isEmpty() || score.isEmpty()) continue;
            leaders.append(name + " " + score);
        }
        leaders.append(playerName + " " + QString::number(gameField->getGame()->getScore()));
        std::sort(leaders.begin(), leaders.end(), [](const QString &a, const QString &b) {
            return a.split(" ").at(1).toInt() < b.split(" ").at(1).toInt();
        });

        file.resize(0);
        QTextStream out(&file);
        for (int i = 0; i < 3 && i < leaders.size(); i++) {
            out << leaders.at(i);
            if (i != leaders.size() - 1) {
                out << '\n';
            }
        }

        file.close();
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
        gameField->getGame()->moveCharacter(0, -1);
        break;
    case Qt::Key_D:
        gameField->getGame()->moveCharacter(1, 0);
        break;
    case Qt::Key_S:
        gameField->getGame()->moveCharacter(0, 1);
        break;
    case Qt::Key_A:
        gameField->getGame()->moveCharacter(-1, 0);
        break;
    }
    gameField->update();
    QWidget::keyPressEvent(event);
}

void MainWindow::resultGame() {
    bool ok;
    QString message = tr("Номер уровня:");
    int selectedLevel = QInputDialog::getInt(this, tr("Выберите уровень"), message, 1, 1, numberOfLevels, 1, &ok);
    if (ok) {
        QFile file(QString("liders/lid%1.txt").arg(selectedLevel));
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("Ошибка"), tr("Невозможно открыть файл"));
                return;
            }
        QTextStream in(&file);
        QString fileContents = in.readAll();
        file.close();
        QStringList lines = fileContents.split("\n");
        if (!lines.empty() && lines.last().isEmpty()) {
                lines.removeLast();
        }
        QWidget *info = new QWidget;
        setCentralWidget(info);
        QGridLayout *layout = new QGridLayout;
        for (int i = 0; i < lines.size(); i++) {
            QString labelTemplate = "%1 место: %2";
            QString labelText = labelTemplate.arg(i+1).arg(lines.at(i));
            QLabel *infoLabel = new QLabel(labelText);
            infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
            infoLabel->setAlignment(Qt::AlignCenter);
            QFont font = infoLabel->font();
            font.setPointSize(16);
            infoLabel->setFont(font);
            layout->addWidget(infoLabel, i, 0);
        }
        info->setLayout(layout);
    }
}

void MainWindow::createActions() {
    newAct = new QAction(tr("Новая"), this);
    newAct->setStatusTip(tr("Начать игру"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newGame);

    resultAct = new QAction(tr("Результаты"), this);
    resultAct->setStatusTip(tr("Результаты"));
    connect(resultAct, &QAction::triggered, this, &MainWindow::resultGame);

    exitAct = new QAction(tr("Выход"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Выйти из игры"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&Игра"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(resultAct);
    fileMenu->addAction(exitAct);
}
