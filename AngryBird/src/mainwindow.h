#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include <QObject>
#include <QMediaPlayer>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <pig.h>
#include <wood.h>
#include <score.h>
#include <button.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void gameOver();
    void start();
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
signals:
    // Signal for closing the game
    void quitGame();
private slots:
    void restartGame();
    void tick();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QGraphicsPixmapItem * slingshot;
    Score * score;
    Wood * invisibleBox;
    static int species;
    Bird * redBirdie;
    Bird * blueBirdie;
    Bird * newBlueBirdie;
    Bird * yellowBirdie;
    Bird * whiteBirdie;
    Bird * newEgg;
    Wood * verticalWood1;
    Wood * verticalWood2;
    Wood * verticalWood3;
    Wood * verticalWood4;
    Wood * verticalWood5;
    Wood * horizontalWood1;
    Wood * horizontalWood2;
    Pig * piggy1;
    Pig * piggy2;
    Pig * piggy3;
    Pig * piggy4;
    Land * ground;
};

#endif // MAINWINDOW_H
