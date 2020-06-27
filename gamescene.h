#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QList>

#include "particle.h"
#include "tiefighter.h"


class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = nullptr);
    virtual ~GameScene();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void timerEvent(QTimerEvent *event);

signals:
    void updateScore(int);
    void setHighscore(int);
    void gameLost();
    void gameWon();
    void timer(int);

private:
    QGraphicsPixmapItem* m_tieFighterItem;
    int m_gamePhase; // 0 = idle, 1 = preparation phase, 2 = game phase

    void drawMaze();
    void keepSpaceshipWithinBounds();

    bool spaceShipCollision();
    bool spaceShipHitBounds();
    bool spaceShipHitMaze();
    bool spaceShipHitMazeRect1();
    bool spaceShipHitMazeRect2();
    bool spaceShipHitMazeRect3();
    bool spaceShipHitMazeRect4();

    void spaceShipHitGoal();


public slots:
    void prepareGame();
    void startTheGame();
    int getGamePhase();
};

#endif // GAMESCENE_H
