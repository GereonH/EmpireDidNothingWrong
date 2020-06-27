#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recruitsheetdialog.h"
#include "gamescene.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_rsd(new RecruitSheetDialog)
{
    // setup styles
    ui->setupUi(this);

    QFile qss(":/qss/qss/main.qss");
    if(qss.open(QFile::ReadOnly)) {
        QString styleString = QLatin1String(qss.readAll());
        setStyleSheet(styleString);
    }
    qss.close();

    // Qt can't create the same effect on multiple widgets. Even memcpy doesn't work. Therefore create a drop shadow effect for every button
    QGraphicsDropShadowEffect* button1Shadow = new QGraphicsDropShadowEffect;
    button1Shadow->setColor(QColor(255, 0, 0, 27));
    button1Shadow->setBlurRadius(0);
    button1Shadow->setOffset(6.0);
    QGraphicsDropShadowEffect* button2Shadow = new QGraphicsDropShadowEffect;
    button2Shadow->setColor(QColor(255, 0, 0, 27));
    button2Shadow->setBlurRadius(0);
    button2Shadow->setOffset(6.0);
    QGraphicsDropShadowEffect* button3Shadow = new QGraphicsDropShadowEffect;
    button3Shadow->setColor(QColor(255, 0, 0, 27));
    button3Shadow->setBlurRadius(0);
    button3Shadow->setOffset(6.0);
    QGraphicsDropShadowEffect* logoShadow = new QGraphicsDropShadowEffect;
    logoShadow->setColor(QColor(255, 0, 0, 27));
    logoShadow->setBlurRadius(0);
    logoShadow->setOffset(6.0);
    QGraphicsDropShadowEffect* etaLabelShadow = new QGraphicsDropShadowEffect;
    etaLabelShadow->setColor(QColor(255, 0, 0, 27));
    etaLabelShadow->setBlurRadius(0);
    etaLabelShadow->setOffset(6.0);
    QGraphicsDropShadowEffect* countdownLabelShadow = new QGraphicsDropShadowEffect;
    countdownLabelShadow->setColor(QColor(255, 0, 0, 27));
    countdownLabelShadow->setBlurRadius(0);
    countdownLabelShadow->setOffset(6.0);

    ui->gameStartButton1->setGraphicsEffect(button1Shadow);
    ui->gameStartButton2->setGraphicsEffect(button2Shadow);
    ui->gameStartButton3->setGraphicsEffect(button3Shadow);
    ui->logo->setGraphicsEffect(logoShadow);
    ui->eta_label->setGraphicsEffect(etaLabelShadow);
    ui->countdownLabel->setGraphicsEffect(countdownLabelShadow);




    // main part
    ui->countdownLabel->hide();

    m_rsd.setModal(true);
    if(m_rsd.exec() == QDialog::Accepted) {
        ui->profileNameLable->setText(m_rsd.getName());
        ui->profileRankLable->setText(m_rsd.getRank());
        if(m_rsd.getAppearanceChoice() == 1) {
            ui->profilePicLable->setPixmap(QPixmap(":/images/images/StormTrooper.png"));
        } else if (m_rsd.getAppearanceChoice() == 2) {
            ui->profilePicLable->setPixmap(QPixmap(":/images/images/villain.svg"));
        } else if(m_rsd.getAppearanceChoice() == 3) {
            ui->profilePicLable->setPixmap(QPixmap(":/images/images/BobaFett.png"));
        }


        QString welcomeMessage = "Welcome aboard " + m_rsd.getName() + ".";
        QMessageBox::information(this, "Accepted", welcomeMessage);
    } else {
        close();
    }

    ui->graphicsView->setFixedSize(1300, 900);
    ui->graphicsView->setSceneRect(0, 0, 1300, 900);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setMouseTracking(true);
    m_gameScene = new GameScene(this);
    ui->graphicsView->setScene(m_gameScene);

    // the syntax from the lecture script didn't work.
    // according to https://forum.qt.io/topic/90588/how-to-solve-object-connect-no-such-signal/2
    // there is a new way to connect Signals and Slots
    connect(m_gameScene, &GameScene::updateScore, this, &MainWindow::decreaseScore);
    connect(m_gameScene, &GameScene::gameLost, this, &MainWindow::gameLost);
    connect(m_gameScene, &GameScene::gameWon, this, &MainWindow::gameWon);
    connect(m_gameScene, &GameScene::timer, this, &MainWindow::countdown);

    connect(this, &MainWindow::prepareGame, m_gameScene, &GameScene::prepareGame);
    connect(this, &MainWindow::startTheGame, m_gameScene, &GameScene::startTheGame);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_gameStartButton1_clicked()
{
    ui->missionNameLabel->setText(ui->gameStartButton1->text());
    startGame();
}

// the paypal advertisement is meant to be a joke. Please to transfer money.
void MainWindow::on_gameStartButton2_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game mode unavailable");
    msgBox.setTextFormat(Qt::RichText);   // links clickable
    msgBox.setText("This game mode is not available in the alpha version of the game.\n<br>Please visit <br>paypal.me/GereonHeinemann/10 for supporting the development of the game.");
    msgBox.exec();
}

// the paypal advertisement is meant to be a joke. Please to transfer money.
void MainWindow::on_gameStartButton3_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game mode unavailable");
    msgBox.setTextFormat(Qt::RichText);   // links clickable
    msgBox.setText("This game mode is not available in the alpha version of the game.\n<br>Please visit <br>paypal.me/GereonHeinemann/10 for supporting the development of the game.");
    msgBox.exec();
}

void MainWindow::decreaseScore(int decrement)
{
    if(ui->graphicsView->isEnabled() && m_gameScene->getGamePhase() == 2) {
        int scorePoints = ui->scorePointsLabel->text().toInt();
            if(scorePoints > 0) {
                ui->scorePointsLabel->setText(QString::number(scorePoints - decrement));
            } else {
                ui->scorePointsLabel->setText("0");
            }
    }

}

void MainWindow::finishGame()
{
    ui->graphicsView->setEnabled(false);

}

void MainWindow::startGame()
{
    ui->logo->hide();
    ui->countdownLabel->show();
    ui->scorePointsLabel->setText("10000");
    ui->graphicsView->setEnabled(true);
    ui->countdownLabel->setText("5");

    emit prepareGame();
}

void MainWindow::gameWon()
{
    finishGame();
    QString pointMsg = "You reached a score of: " + ui->scorePointsLabel->text();
    QMessageBox::information(this, "Congratulations, you won", pointMsg);

}

void MainWindow::gameLost()
{
    QMessageBox::information(this, "Lost", "Try again.");
    finishGame();
}

void MainWindow::countdown(int time)
{
    m_time += time;
    int oldCD = ui->countdownLabel->text().toInt();
    if(m_time % 1000 == 0 && ui->countdownLabel->isVisible() && oldCD > 0) {
        int newCD = oldCD - 1;
        ui->countdownLabel->setText(QString::number(newCD));
    }
    if(oldCD == 0) {
        ui->countdownLabel->hide();
        ui->logo->show();
        emit startTheGame();
    }
}

void MainWindow::on_actionCredits_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Credits");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("This game was developed by using a lot of icons.<br>"
                   "Please visit the following artists:<br>"
                   "https://pngio.com/images/png-a1077427.html<br>"
                   "https://thenounproject.com/PeterEmil/<br>"
                   "https://thenounproject.com/linker/<br>"
                   "https://www.flaticon.com/search/3?word=rocket<br>"
                   "https://thenounproject.com/henningg/<br>"
                   "<br>"
                   "I hope that I did not forget anybody.<br>"
                   "I want to make it clear that none of the icons<br>"
                   "where designed by me.<br>Thank you!");
    msgBox.exec();
}

