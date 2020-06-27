#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "recruitsheetdialog.h"
#include "gamescene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RecruitSheetDialog m_rsd;
    GameScene* m_gameScene;
    int m_time = 0;

signals:
    void prepareGame();
    void startTheGame();

public slots:
    void on_gameStartButton1_clicked();
    void on_gameStartButton2_clicked();
    void on_gameStartButton3_clicked();
    void decreaseScore(int increment);
    void finishGame();
    void startGame();
    void gameWon();
    void gameLost();
    void countdown(int time);

    void on_actionCredits_triggered();
};
#endif // MAINWINDOW_H
