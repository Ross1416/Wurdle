#include<QLabel>
#include<QHBoxLayout>
#include<QFrame>
#include<QStyle>
#include "letterwidget.h"



LetterWidget::LetterWidget(QWidget *parent) : QWidget{parent}
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    letter = new QLabel(this);
    letter->setFrameShape(QFrame::StyledPanel);
//    letter->setFrameShadow(QFrame::Raised);
    letter->setLineWidth(1);
    letter->setStyleSheet("QFrame{border: 1px solid black;border-radius: 5px;font: 10pt 'Arial';background-color: white}");

//    letter->setStyleSheet(QString("font: 75 10pt 'Comic Sans MS'; border: 1px solid black; border-radius: 1 px;background-color: light grey;"));
//    letter->setLineWidth(2);
    letter->setAlignment(Qt::AlignCenter);
    letter->setMargin(0);
    letter->setMaximumHeight(40);
    letter->setMaximumWidth(40);
    letter->setMinimumHeight(40);
    letter->setMinimumWidth(40);
    layout->addWidget(letter);

}

void LetterWidget::setColour(std::string colour)
{
//    QVariant qColour = QString::fromStdString(colour);
//    letter->setProperty("background-color",qColour);
    std::string style = "QFrame{border: 1px solid black;border-radius: 5px;font: 10pt 'Arial';background-color: "+colour+"}";
    letter->setStyleSheet(QString::fromStdString(style));
}


