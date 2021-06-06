#include "board.h"

Board::Board(int width, int height, QMainWindow *parent) :
    QMainWindow(parent)
{
    this->width = width;
    this->height = height;

    setWindowTitle("2048");
    setWindowIcon(QIcon("main_icon.png"));
    getDataFromFile();

    restartButton = new QPushButton("New game", this);
    restartButton->setFocusPolicy(Qt::NoFocus);
    restartButton->setGeometry(22, 140, 155, 66);
    restartButton->setStyleSheet("color: rgb(119,110,101); background-color: rgb(249,246,242); border-style: outset; font: bold 28px");
    QObject::connect(restartButton, &QPushButton::clicked, this, &Board::restart);

    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(25, 30, 313, 40);
    scoreLabel->setStyleSheet("color: rgb(119,110,101); font: bold 40px");

    bestScoreLabel = new QLabel(this);
    bestScoreLabel->setGeometry(375, 90, 290, 40);
    bestScoreLabel->setStyleSheet("color: rgb(119,110,101); font: bold 40px");

    setFixedSize(width, height);
    fieldScene = new QPixmap(width, height);
    drawInitialField();
    updateFieldScene();

    if (showingLoseMessage)
    {
        showLoseMessage();
    }
    update();
}

Board::~Board()
{
    saveResults();
    delete bestScoreLabel;
    delete scoreLabel;
    delete restartButton;
    delete fieldScene;
    if (restartOption != nullptr)
    {
        delete restartOption;
    }
    if (continueOption != nullptr)
    {
        delete continueOption;
    }
}

void Board::getDataFromFile()
{
    QFile file(QDir::currentPath() + "/" + resultsFilename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
    }
    QJsonObject data = QJsonDocument::fromJson(file.readAll()).object();
    file.close();
    hasWon = data["prev_has_won"].toBool();
    for(int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            field[i][j] = data["prev_field"].toArray()[i].toArray()[j].toInt();
        }
    }
    score = data["prev_score"].toInt();
    bestScore = data["best_score"].toInt();
    showingLoseMessage = data["prev_has_lost"].toBool();
}

void Board::drawInitialField()
{
    QPainter pixmapPainter(fieldScene);
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.setBrush(QColor(250, 248, 239));
    pixmapPainter.drawRect(0, 0, width, height);
    pixmapPainter.setBrush(QColor(187, 173, 160));
    pixmapPainter.drawRoundedRect(10, 210, width - 20, height - 220, 2.5, 2.5, Qt::RelativeSize);
    pixmapPainter.setBrush(QColor(143, 122, 102));
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    scoreLabel->setText("Score: " + QString::number(score));
    bestScoreLabel->setText("Best: " + QString::number(bestScore));
    painter.drawPixmap(0, 0, *fieldScene);
}

void Board::updateFieldScene()
{
    QPainter pixmapPainter(fieldScene);
    pixmapPainter.setPen(Qt::NoPen);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (field[i][j] != 0)
            {
                pixmapPainter.setBrush(getTileColor(field[i][j]));
                pixmapPainter.drawRoundedRect(10 + (i + 1) * 12 + i * 155, 210 + (j + 1) * 12 + j * 155, 155, 155, 10, 10, Qt::RelativeSize);
                if (field[i][j] <= 4)
                {
                    pixmapPainter.setPen(QColor(119, 110, 101));
                }
                else
                {
                    pixmapPainter.setPen(QColor(249, 246, 242));
                }
                QFont font;
                font.setBold(true);
                if (field[i][j] >= 16384)
                {
                    font.setPixelSize(35);
                }
                else
                {
                    font.setPixelSize(50);
                }
                pixmapPainter.setFont(font);
                pixmapPainter.drawText(10 + (i + 1) * 12 + i * 155, 210 + (j + 1) * 12 + j * 155, 155, 155, Qt::AlignCenter, QString::number(field[i][j]));
                pixmapPainter.setPen(Qt::NoPen);
            }
            else
            {
                pixmapPainter.setBrush(QColor(205, 193, 180));
                pixmapPainter.drawRoundedRect(10 + (i + 1) * 12 + i * 155, 210 + (j + 1) * 12 + j * 155, 155, 155, 10, 10, Qt::RelativeSize);
            }
        }
    }
}

void Board::keyPressEvent(QKeyEvent *event)
{
    if (showingWinMessage) { return; }
    switch (event->key())
    {
    case Qt::Key_Up:
        moveUp();
        break;
    case Qt::Key_Left:
        moveLeft();
        break;
    case Qt::Key_Right:
        moveRight();
        break;
    case Qt::Key_Down:
        moveDown();
        break;
    }
}

void Board::moveLeft()
{
    bool moved = false;
    for (int j = 0; j < 4; ++j)
    {
        bool haveMerged[4];
        for (int i = 0; i < 4; ++i)
        {
            haveMerged[i] = false;
        }
        for (int i = 1; i < 4; ++i)
        {
            if (field[i][j] != 0)
            {
                for (int k = i - 1; k >= 0; --k)
                {
                    if (haveMerged[k]) { break; }
                    if (field[k][j] == field[i][j])
                    {
                        field[k][j] *= 2;
                        field[i][j] = 0;
                        score += field[k][j];
                        haveMerged[i] = haveMerged[k] = true;
                        moved = true;
                    }
                    else if (field[k][j] != 0) { break; }
                }
            }
        }
    }
    for (int i = 1; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (field[i][j] != 0)
            {
                int k = i - 1;
                while (k >= 0)
                {
                    if(field[k][j] != 0) { break; }
                    --k;
                }
                if (i != k + 1)
                {
                    field[k + 1][j] = field[i][j];
                    field[i][j] = 0;
                    moved = true;
                }
            }
        }
    }
    if (moved)
    {
        addNewTile();
    }
}

void Board::moveRight()
{
    bool moved = false;
    for (int j = 0; j < 4; ++j)
    {
        bool haveMerged[4];
        for (int i = 0; i < 4; ++i)
        {
            haveMerged[i] = false;
        }
        for (int i = 2; i >= 0; --i)
        {
            if (field[i][j] != 0)
            {
                for (int k = i + 1; k < 4; ++k)
                {
                    if (haveMerged[k]) { break; }
                    if (field[i][j] == field[k][j])
                    {
                        field[k][j] *= 2;
                        field[i][j] = 0;
                        score += field[k][j];
                        haveMerged[i] = haveMerged[k] = true;
                        moved = true;
                    }
                    else if (field[k][j] != 0) { break; }
                }
            }
        }
    }
    for (int i = 2; i >= 0 ; --i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (field[i][j] != 0)
            {
                int k = i + 1;
                while (k < 4)
                {
                    if (field[k][j] != 0) { break; }
                    ++k;
                }
                if (i != k - 1)
                {
                    field[k - 1][j] = field[i][j];
                    field[i][j] = 0;
                    moved = true;
                }
            }
        }
    }
    if (moved)
    {
        addNewTile();
    }
}

void Board::moveUp()
{
    bool moved = false;
    for (int i = 0; i < 4; ++i)
    {
        bool haveMerged[4];
        for (int c = 0; c < 4; ++c)
        {
            haveMerged[c] = false;
        }
        for (int j = 1; j < 4; ++j)
        {
            if (field[i][j] != 0)
            {
                for (int k = j - 1; k >= 0; --k)
                {
                    if (haveMerged[k]) { break; }
                    if (field[i][j] == field[i][k])
                    {
                        field[i][k] *= 2;
                        field[i][j] = 0;
                        score += field[i][k];
                        haveMerged[j] = haveMerged[k] = true;
                        moved = true;
                    }
                    else if (field[i][k] != 0) { break; }
                }
            }
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 1; j < 4; ++j)
        {
            if (field[i][j] != 0)
            {
                int k = j - 1;
                while (k >= 0)
                {
                    if (field[i][k] != 0) { break; }
                    --k;
                }
                if (j != k + 1)
                {
                    field[i][k + 1] = field[i][j];
                    field[i][j] = 0;
                    moved = true;
                }
            }
        }
    }
    if (moved)
    {
        addNewTile();
    }
}

void Board::moveDown()
{
    bool moved = false;
    for (int i = 0; i < 4; ++i)
    {
        bool haveMerged[4];
        for (int c = 0; c < 4; ++c)
        {
            haveMerged[c] = false;
        }
        for (int j = 2; j >= 0; --j)
        {
            if (field[i][j] != 0)
            {
                for (int k = j + 1; k < 4; ++k)
                {
                    if (haveMerged[k]) { break; }
                    if (field[i][j] == field[i][k])
                    {
                        field[i][k] *= 2;
                        field[i][j] = 0;
                        score += field[i][k];
                        haveMerged[j] = haveMerged[k] = true;
                        moved = true;
                    }
                    else if (field[i][k] != 0) { break; }
                }
            }
        }
    }
    for (int j = 2; j >= 0; --j)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (field[i][j] != 0)
            {
                int k = j + 1;
                while (k < 4)
                {
                    if(field[i][k] != 0) { break; }
                    ++k;
                }
                if (j != k - 1)
                {
                    field[i][k - 1] = field[i][j];
                    field[i][j] = 0;
                    moved = true;
                }
            }
        }
    }
    if (moved)
    {
        addNewTile();
    }
}

bool Board::win()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (field[i][j] == 2048) { return true; }
        }
    }
    return false;
}

void Board::showWinMessage()
{
    showingWinMessage = true;
    hasWon = true;

    QPainter pixmapPainter(fieldScene);
    pixmapPainter.setBrush( QColor(220, 220, 220, 170));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawRoundedRect(10, 210, width - 20, height - 220, 2.5, 2.5, Qt::RelativeSize);
    QFont font;
    font.setPixelSize(90);
    font.setBold(true);
    pixmapPainter.setPen(QColor(119, 110, 101));
    pixmapPainter.setFont(font);
    pixmapPainter.drawText(90, 421, 540, 90, Qt::AlignCenter, "You win!");

    restartOption = new QPushButton("Restart", this);
    restartOption->setGeometry(150, 564, 175, 70);
    restartOption->setStyleSheet("color: white; background-color: rgb(143, 122, 102); border-style: outset; border-radius: 5px; font: bold 28px");
    restartOption->show();

    continueOption = new QPushButton("Continue", this);
    continueOption->setGeometry(375, 564, 175, 70);
    continueOption->setStyleSheet("color: white; background-color: rgb(143, 122, 102); border-style: outset; border-radius: 5px; font: bold 28px");
    continueOption->show();

    QObject::connect(restartOption, &QPushButton::clicked, this, &Board::onRestartOption);
    QObject::connect(continueOption, &QPushButton::clicked, this, &Board::onContinueOption);
    update();
}

void Board::onRestartOption()
{
    delete restartOption;
    restartOption = nullptr;
    if (continueOption != nullptr)
    {
        delete continueOption;
        continueOption = nullptr;
    }
    restart();
}

void Board::onContinueOption()
{
    delete restartOption;
    restartOption = nullptr;
    delete continueOption;
    continueOption = nullptr;
    drawInitialField();
    updateFieldScene();
    showingWinMessage = false;
    update();
}

bool Board::isGameOver()
{
    int tilesCounter = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (field[i][j] == 0) { break; }
            ++tilesCounter;
        }
    }
    if (tilesCounter == 16 && !isAbleToMove())
    {
        return true;
    }
    return false;
}

bool Board::isAbleToMove()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (i < 3 && field[i][j] == field[i + 1][j])
            {
                return true;
            }
            if (j < 3 && field[i][j] == field[i][j + 1])
            {
                return true;
            }
        }
    }
    return false;
}

void Board::showLoseMessage()
{
    showingLoseMessage = true;
    QPainter pixmapPainter(fieldScene);
    pixmapPainter.setBrush( QColor(220, 220, 220, 170));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawRoundedRect(10, 210, width - 20, height - 220, 2.5, 2.5, Qt::RelativeSize);
    QFont font;
    font.setPixelSize(90);
    font.setBold(true);
    pixmapPainter.setPen(QColor(119, 110, 101));
    pixmapPainter.setFont(font);
    pixmapPainter.drawText(80, 421, 540, 90, Qt::AlignCenter, "Game over!");

    restartOption = new QPushButton("Restart", this);
    restartOption->setGeometry(263, 564, 175, 70);
    restartOption->setStyleSheet("color: white; background-color: rgb(143, 122, 102); border-style: outset; border-radius: 5px; font: bold 28px");
    restartOption->show();

    QObject::connect(restartOption, &QPushButton::clicked, this, &Board::onRestartOption);
    update();
}

void Board::addNewTile()
{
    uint *empties = new uint[16];
    uint emptiesCounter = 0;
    for (uint i = 0; i < 4; ++i)
    {
        for (uint j = 0; j < 4; ++j)
        {
            if (field[i][j] == 0)
            {
                empties[emptiesCounter++] = i * 10 + j;
            }
        }
    }

    int randomNum = QRandomGenerator::global()->generate() % 10;
    uint pos = empties[QRandomGenerator::global()->generate() % emptiesCounter];
    if (randomNum == 0)
    {
        field[pos / 10][pos % 10] = 4;
    }
    else
    {
        field[pos / 10][pos % 10] = 2;
    }
    delete[] empties;
    updateFieldScene();
    update();
    if (!hasWon && win())
    {
        showWinMessage();
        update();
    }
    if (isGameOver())
    {
        showLoseMessage();
        update();
    }
}

QColor Board::getTileColor(int value)
{
    switch (value)
    {
    case 2:
        return QColor(238, 228, 218);
    case 4:
        return QColor(238, 225, 201);
    case 8:
        return QColor(243, 178, 122);
    case 16:
        return QColor(246, 150, 100);
    case 32:
        return QColor(247, 125, 95);
    case 64:
        return QColor(247, 95, 59);
    case 128:
        return QColor(237, 208, 115);
    case 256:
        return QColor(237, 204, 98);
    case 512:
        return QColor(237, 201, 80);
    case 1024:
        return QColor(237, 197, 66);
    case 2048:
        return QColor(236, 196, 2);
    case 4096:
        return QColor(96, 217, 148);
    case 8192:
        return QColor(96, 197, 158);
    case 16384:
        return QColor(96, 177, 209);
    case 32768:
        return QColor(96, 157, 209);
    case 65536:
        return QColor(146, 157, 209);
    case 131072:
        return QColor(180, 117, 209);
    default:
        return QColor(150, 150, 100);
    }
}

void Board::restart()
{
    showingWinMessage = false;
    showingLoseMessage = false;
    if (restartOption != nullptr)
    {
        delete restartOption;
        restartOption = nullptr;
    }
    if (continueOption != nullptr)
    {
        delete continueOption;
        continueOption = nullptr;
    }
    saveResults();

    score = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            field[i][j] = 0;
        }
    }
    hasWon = false;
    addNewTile();
    addNewTile();
    drawInitialField();
    updateFieldScene();
    update();
}

void Board::saveResults()
{
    QFile resultsFile(QDir::currentPath() + "/" + resultsFilename);
    if (!resultsFile.open(QIODevice::ReadOnly))
    {
        qDebug() << resultsFile.errorString();
    }
    QJsonObject results = QJsonDocument::fromJson(resultsFile.readAll()).object();
    resultsFile.close();

    if (score > results["best_score"].toInt())
    {
        results["best_score"] = score;
        bestScore = score;
    }

    results["prev_has_won"] = hasWon;
    results["prev_has_lost"] = showingLoseMessage;
    results["prev_score"] = score;
    QJsonArray fieldJson;
    for (int i = 0; i < 4; ++i)
    {
        QJsonArray line;
        for (int j = 0; j < 4; ++j)
        {
            line.append(field[i][j]);
        }
        fieldJson.append(line);
    }
    results["prev_field"] = fieldJson;

    if (!resultsFile.open(QIODevice::WriteOnly))
    {
        qDebug() << resultsFile.errorString();
    }
    resultsFile.write(QJsonDocument(results).toJson());
    resultsFile.close();
}
