#include "wood.h"

Wood::Wood(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);

    // Create body
    //b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.userData = this;
    bodydef.position.Set(x,y);
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(w/2,h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = WOOD_DENSITY;
    fixturedef.friction = WOOD_FRICTION;
    fixturedef.restitution = WOOD_RESTITUTION;
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}
