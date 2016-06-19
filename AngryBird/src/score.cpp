#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem * parent) : QGraphicsTextItem(parent){
    //initialize the score
    score = 0;

    //draw the text
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::black);
    setFont(QFont("Kristen ITC",35));
    setPos(20,10);
}

void Score::increase(){
    score++;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore(){
    return score;
}
