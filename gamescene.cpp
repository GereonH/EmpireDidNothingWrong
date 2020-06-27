#include "gamescene.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>

static int s_timerInterval = 10;

static int s_tieFighterSceneBoundsLeft = 2;
static int s_tieFighterSceneBoundsRight = 1189;
static int s_tieFighterSceneBoundsTop = 0;
static int s_tieFighterSceneBoundsBottom = 793;

GameScene::GameScene(QObject *parent) : QGraphicsScene(parent)
{
    startTimer(s_timerInterval);



    // TieFighter
    QPixmap tieFighterPixmap(":/images/gameIcons/images/gameIcons/TieFighter.png");
    QPointF tfpt;
    tfpt.setX(550);
    tfpt.setY(780);

    m_tieFighterItem = new QGraphicsPixmapItem();
    m_tieFighterItem->setPos(tfpt);
    m_tieFighterItem->setPixmap(tieFighterPixmap);
    m_tieFighterItem->setScale(0.25);
    addItem(m_tieFighterItem);

    // StarDestroyer
    QPixmap starDestroyerPixmap(":/images/gameIcons/images/gameIcons/StarDestroyer.png");
    QPointF sdpt;
    sdpt.setX(1015);
    sdpt.setY(-45);

    QGraphicsPixmapItem* starDestroyerPixmapItem = new QGraphicsPixmapItem();
    starDestroyerPixmapItem->setPos(sdpt);
    starDestroyerPixmapItem->setPixmap(starDestroyerPixmap);
    starDestroyerPixmapItem->setScale(0.5);
    addItem(starDestroyerPixmapItem);

    drawMaze();


}

GameScene::~GameScene() {
    delete m_tieFighterItem;
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    // center tiefighter graphic to mouse
    QPointF pt;
    pt.setX(mouseEvent->scenePos().x() - 55);
    pt.setY(mouseEvent->scenePos().y() - 50);
    m_tieFighterItem->setPos(pt);

    spaceShipCollision();
    keepSpaceshipWithinBounds();
    spaceShipHitGoal();


//    qInfo() << m_tieFighterItem->pos().x() << " / " << m_tieFighterItem->pos().y();

}

void GameScene::timerEvent(QTimerEvent *event) {
    emit timer(s_timerInterval);
    emit updateScore(1);
}

void GameScene::drawMaze()
{

    addRect(-50, 550, 400, 150); // 1
    addRect(500, 700, 1600, -300); // 2
    addRect(150, 400, 550, -275); // 3
    addRect(835, -20, 100, 300); //4
}

// prevents tiefighter graphic to escape scene
void GameScene::keepSpaceshipWithinBounds()
{
    if(m_gamePhase == 1) {
        if (m_tieFighterItem->pos().x() < s_tieFighterSceneBoundsLeft)
            m_tieFighterItem->setPos(s_tieFighterSceneBoundsLeft, m_tieFighterItem->pos().y());
        else if (m_tieFighterItem->pos().x() > s_tieFighterSceneBoundsRight)
            m_tieFighterItem->setPos(s_tieFighterSceneBoundsRight, m_tieFighterItem->pos().y());

        if (m_tieFighterItem->pos().y() < 705)
            m_tieFighterItem->setPos(m_tieFighterItem->pos().x(), 705);
        else if (m_tieFighterItem->pos().y() > s_tieFighterSceneBoundsBottom)
            m_tieFighterItem->setPos(m_tieFighterItem->pos().x(), s_tieFighterSceneBoundsBottom);

    } else if (m_gamePhase == 2) {

    if (m_tieFighterItem->pos().x() < s_tieFighterSceneBoundsLeft)
        m_tieFighterItem->setPos(s_tieFighterSceneBoundsLeft, m_tieFighterItem->pos().y());
    else if (m_tieFighterItem->pos().x() > s_tieFighterSceneBoundsRight)
        m_tieFighterItem->setPos(s_tieFighterSceneBoundsRight, m_tieFighterItem->pos().y());

    if (m_tieFighterItem->pos().y() < s_tieFighterSceneBoundsTop)
        m_tieFighterItem->setPos(m_tieFighterItem->pos().x(), s_tieFighterSceneBoundsTop);
    else if (m_tieFighterItem->pos().y() > s_tieFighterSceneBoundsBottom)
        m_tieFighterItem->setPos(m_tieFighterItem->pos().x(), s_tieFighterSceneBoundsBottom);
    }
}

bool GameScene::spaceShipCollision()
{
    if(m_gamePhase == 2) {
        if(!spaceShipHitBounds() && !spaceShipHitMaze()) {
            return false;
        } else {
            emit gameLost();
            return true;
        }
    }
    return false;
}

bool GameScene::spaceShipHitBounds()
{
    if(m_tieFighterItem->pos().x() < s_tieFighterSceneBoundsLeft
            || m_tieFighterItem->pos().x() > s_tieFighterSceneBoundsRight
            || m_tieFighterItem->pos().y() < s_tieFighterSceneBoundsTop
            || m_tieFighterItem->pos().y() > s_tieFighterSceneBoundsBottom) {
        qInfo() << "TieFighter hit Bounds";
        return true;
    } else {
//        qInfo() << "TieFighter within Bounds";
        return false;
    }
}

bool GameScene::spaceShipHitMaze()
{
    return spaceShipHitMazeRect1()
            || spaceShipHitMazeRect2()
            || spaceShipHitMazeRect3()
            || spaceShipHitMazeRect4()
            ;
}

bool GameScene::spaceShipHitMazeRect1()
{
    int bot = 700;
    int right = 350;
    int top = 445;

    if(m_tieFighterItem->pos().y() < bot
            && m_tieFighterItem->pos().x() < right
            && m_tieFighterItem->pos().y() > top)
    {
//        qInfo() << "Spacehip hit Rect1";
        return true;

    } else {
        return false;
    }

}

bool GameScene::spaceShipHitMazeRect2()
{
    int bot = 702;
    int top = 296;
    int left = 389;

    if(m_tieFighterItem->pos().y() < bot
            && m_tieFighterItem->pos().x() > left
            && m_tieFighterItem->pos().y() > top)
    {
//        qInfo() << "Spacehip hit Rect2";
        return true;

    } else {
        return false;
    }

}

bool GameScene::spaceShipHitMazeRect3()
{
    int bot = 401;
    int right = 702;
    int top = 19;
    int left = 38;

    if(m_tieFighterItem->pos().y() < bot
            && m_tieFighterItem->pos().x() < right
            && m_tieFighterItem->pos().x() > left
            && m_tieFighterItem->pos().y() > top)
    {
//        qInfo() << "Spacehip hit Rect3";
        return true;

    } else {
        return false;
    }

}

bool GameScene::spaceShipHitMazeRect4()
{
    int bot = 280;
    int right = 936;
    int left = 724;

    if(m_tieFighterItem->pos().y() < bot
            && m_tieFighterItem->pos().x() < right
            && m_tieFighterItem->pos().x() > left)
    {
//        qInfo() << "Spacehip hit Rect4";
        return true;

    } else {
        return false;
    }

}

void GameScene::spaceShipHitGoal()
{
    if(m_tieFighterItem->pos().x() > 1000
            && m_tieFighterItem->pos().y() < 75) {
        emit gameWon();
    }
}

void GameScene::prepareGame()
{
    m_gamePhase = 1;

    QPointF tfpt;
    tfpt.setX(550);
    tfpt.setY(780);
    m_tieFighterItem->setPos(tfpt);
    qInfo() << "Game prepared!";
}

void GameScene::startTheGame()
{
    m_gamePhase = 2;
}

int GameScene::getGamePhase()
{
    return m_gamePhase;
}
