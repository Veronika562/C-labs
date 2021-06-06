#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QRandomGenerator>
#include <QPushButton>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>

class Board : public QMainWindow
{
    Q_OBJECT

public:
    explicit Board(int width, int height, QMainWindow *parent = nullptr);
    ~Board() override;

public slots:
    void restart();
    void onRestartOption();
    void onContinueOption();

private:
    void addNewTile();
    void drawInitialField();
    void getDataFromFile();
    void paintEvent(QPaintEvent *event) override;
    QColor getTileColor(int value);
    void keyPressEvent(QKeyEvent *event) override;
    void updateFieldScene();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool win();
    void showWinMessage();
    void showLoseMessage();
    bool isAbleToMove();
    bool isGameOver();
    void saveResults();

    QPixmap *fieldScene;
    QPushButton *restartButton;
    QLabel *scoreLabel;
    QLabel *bestScoreLabel;
    int field[4][4];
    long long score, bestScore;
    int width, height;
    bool hasWon;
    bool showingWinMessage = false;
    bool showingLoseMessage = false;
    QString resultsFilename = "data.json";
    QPushButton *restartOption = nullptr, *continueOption = nullptr;

};

#endif // BOARD_H
