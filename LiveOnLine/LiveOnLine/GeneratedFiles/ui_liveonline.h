/********************************************************************************
** Form generated from reading UI file 'liveonline.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVEONLINE_H
#define UI_LIVEONLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiveOnLineClass
{
public:
    QFrame *line;

    void setupUi(QWidget *LiveOnLineClass)
    {
        if (LiveOnLineClass->objectName().isEmpty())
            LiveOnLineClass->setObjectName(QStringLiteral("LiveOnLineClass"));
        LiveOnLineClass->resize(600, 400);
        line = new QFrame(LiveOnLineClass);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(120, 310, 121, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(LiveOnLineClass);

        QMetaObject::connectSlotsByName(LiveOnLineClass);
    } // setupUi

    void retranslateUi(QWidget *LiveOnLineClass)
    {
        LiveOnLineClass->setWindowTitle(QApplication::translate("LiveOnLineClass", "LiveOnLine", 0));
    } // retranslateUi

};

namespace Ui {
    class LiveOnLineClass: public Ui_LiveOnLineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVEONLINE_H
