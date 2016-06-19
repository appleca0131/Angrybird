#ifndef PIG_H
#define PIG_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

#define PIG_DENSITY 10.0f
#define PIG_FRICTION 0.2f
#define PIG_RESTITUTION 0.2f

class Pig : public GameItem{
    Q_OBJECT
public:
    Pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    bool eliminate = false;
public slots:
    void velocityTest();
};



#endif // PIG_H
