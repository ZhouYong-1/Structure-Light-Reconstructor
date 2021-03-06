#include "projector.h"
#include <QLayout>
#include <QEvent>
#include <QPaintEvent>

int proj_w;
int proj_h;

Projector::Projector(QWidget *parent, int scanW, int scanH, int projW, int projH, int xos, int yos)
    : QWidget(parent)
{
    width = scanW;
    height = scanH;
    proj_w = projW;
    proj_h = projH;
    xoffset = xos;
    yoffset = yos;
    crossVisible = true;
    label = new QLabel;
    QHBoxLayout *lo = new QHBoxLayout;
    lo->addWidget(label);
    //setLayout(lo);
}

Projector::~Projector()
{
}

void Projector::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(crossVisible)//QEvent::User 1000
    {
        painter.setPen(QPen(Qt::yellow, 5));
    //else
        //painter.setPen(QPen(Qt::white, 5));
        painter.drawLine(proj_w/2 - 60, proj_h/2, proj_w/2 + 60, proj_h/2);
        painter.drawLine(proj_w/2, proj_h/2 - 60, proj_w/2, proj_h/2 + 60);
    }
    if(imageAva){
        painter.drawImage(0,0,pshow);
    }
}

void Projector::opencvWindow()
{
    cv::namedWindow("w");
    //cvResizeWindow("w",width,height);
    cv::moveWindow("w", xoffset, yoffset);
}

void Projector::showMatImg(cv::Mat img)
{
    cv::imshow("w", img);
}

void Projector::showImg(cv::Mat img)
{
    pshow = QImage(img.data,img.cols,img.rows,QImage::Format_Indexed8);
    imageAva = true;
    this->update();
    //QPixmap p = QPixmap::fromImage(pshow);
    //label->setPixmap(p);
}

void Projector::destoryWindow()
{
    cvDestroyWindow("w");
}

void Projector::displaySwitch(bool isWhite)
{
    if(isWhite)
        this->setPalette(Qt::white);
    else
        this->setPalette(Qt::black);
}

void Projector::setCrossVisable(bool flag)
{
    crossVisible = flag;
    this->update();
}
