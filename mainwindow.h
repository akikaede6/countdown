#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void starttimer();
    void start();
    void pause();
    void cancel();
    void setbgm();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int time;
    QMediaPlayer *m_player;
};

#endif // MAINWINDOW_H
