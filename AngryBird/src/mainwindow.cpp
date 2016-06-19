#include "mainwindow.h"
#include "ui_mainwindow.h"

QMediaPlayer * music;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Setting the background
    ui->graphicsView->setObjectName("background");
    ui->graphicsView->setStyleSheet("#background{border-image:url(:/Background.png);}");
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    start();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

void MainWindow::start()
{
    // Create ground (You can edit here)
    ground = new Land(16,1.5,32,3,QPixmap().scaled(width(),height()/6.0),world,scene);
    itemList.push_back(ground);
    // Create woods
    verticalWood1 = new Wood(15.0f,8.0f,1.0f,4.0f,&timer,QPixmap(":/VerticalWood.png").scaled(30,120),world,scene);
    verticalWood2 = new Wood(19.0f,8.0f,1.0f,4.0f,&timer,QPixmap(":/VerticalWood.png").scaled(30,120),world,scene);
    verticalWood3 = new Wood(23.0f,8.0f,1.0f,4.0f,&timer,QPixmap(":/VerticalWood.png").scaled(30,120),world,scene);
    verticalWood4 = new Wood(17.0f,12.0f,1.0f,4.0f,&timer,QPixmap(":/VerticalWood.png").scaled(30,120),world,scene);
    verticalWood5 = new Wood(21.0f,12.0f,1.0f,4.0f,&timer,QPixmap(":/VerticalWood.png").scaled(30,120),world,scene);
    horizontalWood1 = new Wood(18.9f,10.0f,10.0f,1.0f,&timer,QPixmap(":/HorizontalWood.png").scaled(300,30),world,scene);
    horizontalWood2 = new Wood(19.2f,14.0f,6.0f,1.0f,&timer,QPixmap(":/HorizontalWood.png").scaled(180,30),world,scene);
    // Create enemies
    piggy1 = new Pig(17.0f,8.0f,1.0f,&timer,QPixmap(":/GreenPig.png").scaled(1.0*60,1.0*60),world,scene);
    piggy2 = new Pig(21.0f,8.0f,1.0f,&timer,QPixmap(":/GreenPig.png").scaled(1.0*60,1.0*60),world,scene);
    piggy3 = new Pig(19.0f,12.0f,1.0f,&timer,QPixmap(":/GreenPig.png").scaled(1.0*60,1.0*60),world,scene);
    piggy4 = new Pig(19.0f,16.0f,1.0f,&timer,QPixmap(":/GreenPig.png").scaled(1.0*60,1.0*60),world,scene);
    // Push back
    itemList.push_back(verticalWood1);
    itemList.push_back(verticalWood2);
    itemList.push_back(verticalWood3);
    itemList.push_back(verticalWood4);
    itemList.push_back(verticalWood5);
    itemList.push_back(horizontalWood1);
    itemList.push_back(horizontalWood2);
    itemList.push_back(piggy1);
    itemList.push_back(piggy2);
    itemList.push_back(piggy3);
    itemList.push_back(piggy4);
    // Create sling shot
    slingshot = new QGraphicsPixmapItem();
    slingshot->setPos(80,300);
    slingshot->setPixmap(QPixmap(":/SlingShot.png"));
    scene->addItem(slingshot);
    // Create score
    score = new Score();
    scene->addItem(score);
    // Play background music
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/BGM.mp3"));
    music->play();
}

int MainWindow::species = 1;

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent * keyEvent = (QKeyEvent*)event;
        if(keyEvent->key() == Qt::Key_Space){
            species = 1;
            return true;
        }
        if(keyEvent->key() == Qt::Key_1){
            float xPos = blueBirdie->getBirdXPos();
            float yPos = blueBirdie->getBirdYPos();
            newBlueBirdie = new Bird(xPos,yPos,1.0f,&timer,QPixmap(":/BlueBird.png").scaled(1.0*60,1.0*60),world,scene);
            newBlueBirdie->setLinearVelocity(b2Vec2(15,4));
            itemList.push_back(newBlueBirdie);
            return true;
        }
        if(keyEvent->key() == Qt::Key_2){
            yellowBirdie->setLinearVelocity(b2Vec2(35,8));
            return true;
        }
        if(keyEvent->key() == Qt::Key_3){
            float xPos = whiteBirdie->getBirdXPos();
            float yPos = whiteBirdie->getBirdYPos();
            newEgg = new Bird(xPos,yPos,1.0f,&timer,QPixmap(":/Egg.png").scaled(1.0*60,1.0*60),world,scene);
            itemList.push_back(newEgg);
            whiteBirdie->setLinearVelocity(b2Vec2(20,10));
            return true;
        }
        return false;
    }
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        /* TODO : add your code here */
        //std::cout << "Press !" << std::endl ;
        // Set invisible box under the slingshot
        //if(1<=species && species<=4){
            //invisibleBox = new Wood(4.0f,5.0f,2.0f,2.5f,&timer,QPixmap().scaled(60,75),world,scene);
            //invisibleBox->bodydef.type = b2_staticBody;
        //}
        // Create birds
        if(species == 1){
            redBirdie = new Bird(3.6f,8.0f,1.0f,&timer,QPixmap(":/RedBird.png").scaled(1.0*60,1.0*60),world,scene);
            ++species;
            return true;
        }
        else if(species == 2){
            blueBirdie = new Bird(3.6f,8.0f,1.0f,&timer,QPixmap(":/BlueBird.png").scaled(1.0*60,1.0*60),world,scene);
            ++species;
            return true;
        }
        else if(species == 3){
            yellowBirdie = new Bird(3.6f,8.0f,1.0f,&timer,QPixmap(":/YellowBird.png").scaled(1.0*60,1.0*60),world,scene);
            ++species;
            return true;
        }
        else if(species == 4){
            whiteBirdie = new Bird(3.6f,8.0f,1.0f,&timer,QPixmap(":/WhiteBird.png").scaled(1.0*60,1.0*60),world,scene);
            ++species;
            return true;
        }
        return false;
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */
        //std::cout << "Release !" << std::endl ;
        // Delete the invisible box
        //if(1<=species && species<=4){
            //delete invisibleBox;
        //}
        // Shoot the birds
        if(species == 2){
            redBirdie->setLinearVelocity(b2Vec2(15,2));
            itemList.push_back(redBirdie);
            QMediaPlayer * soundeffect = new QMediaPlayer();
            soundeffect->setMedia(QUrl("qrc:/SE1.mp3"));
            soundeffect->play();
            return true;
        }
        else if(species == 3){
            blueBirdie->setLinearVelocity(b2Vec2(15,6));
            itemList.push_back(blueBirdie);
            QMediaPlayer * soundeffect = new QMediaPlayer();
            soundeffect->setMedia(QUrl("qrc:/SE2.mp3"));
            soundeffect->play();
            return true;
        }
        else if(species == 4){
            yellowBirdie->setLinearVelocity(b2Vec2(10,6));
            itemList.push_back(yellowBirdie);
            QMediaPlayer * soundeffect = new QMediaPlayer();
            soundeffect->setMedia(QUrl("qrc:/SE1.mp3"));
            soundeffect->play();
            return true;
        }
        else if(species == 5){
            whiteBirdie->setLinearVelocity(b2Vec2(15,6));
            itemList.push_back(whiteBirdie);
            QMediaPlayer * soundeffect = new QMediaPlayer();
            soundeffect->setMedia(QUrl("qrc:/SE2.mp3"));
            soundeffect->play();
            species = 10;
            gameOver();
            return true;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::gameOver()
{
    //disable all scene items
    //for(size_t i=0 ; i<scene->items().size() ; i++){
        //scene->items()[i]->setEnabled(false);
    //}

    //draw panel
    drawPanel(0,0,1442,843,Qt::lightGray,0);

    //create playAgain button
    Button * playAgain = new Button(QString("Play Again"));
    playAgain->setPos(370,330);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    //create quit button
    Button * quit = new Button(QString("Quit Game"));
    quit->setPos(505,330);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    //show result
    QGraphicsTextItem * resultscore = new QGraphicsTextItem();
    resultscore->setPlainText(QString("Win"));
    resultscore->setDefaultTextColor(Qt::black);
    resultscore->setFont(QFont("Kristen ITC",35));
    resultscore->setPos(420,180);
    scene->addItem(resultscore);
}

void MainWindow::restartGame()
{
    music->stop();
    //for(int i=0;i<itemList.size();i++)
        //delete itemList[i];
    if(piggy1->eliminate == false){
        delete piggy1;
    }
    if(piggy2->eliminate == false){
        delete piggy2;
    }
    if(piggy3->eliminate == false){
        delete piggy3;
    }
    if(piggy4->eliminate == false){
        delete piggy4;
    }
    delete verticalWood1;
    delete verticalWood2;
    delete verticalWood3;
    delete verticalWood4;
    delete verticalWood5;
    delete horizontalWood1;
    delete horizontalWood2;
    delete redBirdie;
    delete blueBirdie;
    delete newBlueBirdie;
    delete yellowBirdie;
    delete whiteBirdie;
    delete newEgg;
    delete slingshot;
    delete ground;
    itemList.clear();
    scene->clear();
    start();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    //draw a panel at the specified location with the specified properties
    QGraphicsRectItem * panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
