#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(starttimer()));
    connect(ui->start, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->pause, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(m_player, &QMediaPlayer::mediaStatusChanged, m_player, &QMediaPlayer::play);
    ui->pause->setEnabled(false);
    ui->cancel->setEnabled(false);
    timer->setInterval(1000);
    m_player = new QMediaPlayer(this);
    QAudioOutput *m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);
}

void MainWindow::setbgm()
{
    if (ui->music->currentText() == "bgm1")
    {
        m_player->setSource(QUrl::fromLocalFile("C:/Users/aki/Downloads/bgm1.mp3"));
    }
    else if (ui->music->currentText() == "bgm2")
    {
        m_player->setSource(QUrl::fromLocalFile("C:/Users/aki/Downloads/bgm2.mp3"));
    }
    else if (ui->music->currentText() == "bgm3")
    {
        m_player->setSource(QUrl::fromLocalFile("C:/Users/aki/Downloads/bgm3.mp3"));
    }
    else
    {
        m_player->setSource(QUrl(nullptr));
    }
    qInfo() << ui->music->currentText();
}

void MainWindow::start()
{
    time = ui->settime->text().toUInt() * 60;
    timer->start();
    setbgm();
    m_player->play();
}

void MainWindow::starttimer()
{
    ui->pause->setEnabled(true);
    ui->cancel->setEnabled(true);
    time -= 1;
    int minute = time / 60;
    int sec = time % 60;
    if (minute < 10)
    {
        ui->min->setText("0"+QString::number(minute));

    }
    else if (minute >=10)
    {
        ui->min->setText(QString::number(minute));
    }
    if (sec < 10)
    {
        ui->second->setText("0"+QString::number(sec));
    }
    else if (sec >= 10)
    {
        ui->second->setText(QString::number(sec));
    }
    if(time == 0)
    {
        timer->stop();
    }
}

void MainWindow::pause()
{
    if (ui->pause->text() == QString("继续"))
    {
        timer->start();
        ui->pause->setText("暂停");
        m_player->play();
    }
    else
    {
        timer->stop();
        ui->pause->setText("继续");
        m_player->pause();
    }
}

void MainWindow::cancel()
{
    ui->min->setText("00");
    ui->second->setText("00");
    timer->stop();
    m_player->stop();
    ui->pause->setEnabled(false);
    ui->cancel->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
