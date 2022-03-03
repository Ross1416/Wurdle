#ifndef LETTERWIDGET_H
#define LETTERWIDGET_H

#include<QLabel>
#include <QWidget>
#include<string>

class LetterWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel *letter;
    int x;
    int y;
    std::string colour;


public:
    explicit LetterWidget(QWidget *parent = nullptr);
    void setLetter(char l) {letter->setText(QString(l));};
    std::string getLetter() {return letter->text().toStdString();};

    void setColour(std::string);
//    int getX() {return x;};
//    int getY() {return y;};


//    void setX(int a) {x = a;};
//    void setY(int b) {y = b;};

//public slots:

//signals:

};

#endif // LETTERWIDGET_H
