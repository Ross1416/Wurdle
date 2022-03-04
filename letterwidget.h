#ifndef LETTERWIDGET_H
#define LETTERWIDGET_H

#include<QLabel>
#include <QWidget>
#include<QHBoxLayout>
#include<string>

class LetterWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *layout;
    QLabel *letter;
    std::string colour;
    bool highlight;
//    std::string borderColour;

public:
    explicit LetterWidget(QWidget *parent = nullptr);
    virtual ~LetterWidget();

    void setLetter(char);
    std::string getLetter() {return letter->text().toStdString();};

    void setColour(std::string);
    void setHighlight();
    void setUnhighlight();

    void updateStyle();

};

#endif // LETTERWIDGET_H
