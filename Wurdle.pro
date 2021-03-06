QT += core gui
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Word.cpp \
    answerWord.cpp \
    entropy.cpp \
    functions.cpp \
    game.cpp \
    guessWord.cpp \
    letterscontainer.cpp \
    letterwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    possAnswerWord.cpp \
    possGuessWord.cpp \
    settingsfilehandler.cpp \
    settingsmenu.cpp

HEADERS += \
    Word.h \
    answerWord.h \
    entropy.h \
    functions.h \
    game.h \
    guessWord.h \
    letterscontainer.h \
    letterwidget.h \
    mainwindow.h \
    possAnswerWord.h \
    possGuessWord.h \
    settingsfilehandler.h \
    settingsmenu.h

FORMS += \
    mainwindow.ui \
    settingsmenu.ui

TRANSLATIONS += \
    languages/wurdle_en.ts \
    languages/wurdle_fr.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    languages.qrc

DISTFILES +=
