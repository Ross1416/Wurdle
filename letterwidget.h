#ifndef LETTERWIDGET_H
#define LETTERWIDGET_H

#include<QLabel>
#include <QWidget>
#include<QHBoxLayout>
#include<string>

// LETTER WIDGET
// Individual widget with a rounded square containing single character

class LetterWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *layout;
    QLabel *letter;
    std::string colour;
    bool highlightState;
//    std::string borderColour;

public:
    explicit LetterWidget(QWidget *parent = nullptr);
    virtual ~LetterWidget();

    void setLetter(char);
    std::string getLetter() {return letter->text().toStdString();};

    void setColour(std::string);
    void highlight();
    void unhighlight();

    void updateStyle();

};

#endif // LETTERWIDGET_H
