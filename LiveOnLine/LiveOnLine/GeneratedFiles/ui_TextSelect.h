/********************************************************************************
** Form generated from reading UI file 'TextSelect.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTSELECT_H
#define UI_TEXTSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TextDlg
{
public:
    QLabel *label;
    QLineEdit *lineEdit_Input;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(458, 96);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 51, 16));
        lineEdit_Input = new QLineEdit(Dialog);
        lineEdit_Input->setObjectName(QStringLiteral("lineEdit_Input"));
        lineEdit_Input->setGeometry(QRect(90, 20, 351, 31));
        okButton = new QPushButton(Dialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(280, 70, 75, 23));
        cancelButton = new QPushButton(Dialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(370, 70, 75, 23));

        retranslateUi(Dialog);
        QObject::connect(okButton, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("TextDlg", "\346\226\207\345\255\227\350\276\223\345\205\245\345\257\271\350\257\235\346\241\206", 0));
        label->setText(QApplication::translate("TextDlg", "\350\257\267\350\276\223\345\205\245\357\274\232", 0));
        okButton->setText(QApplication::translate("TextDlg", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("TextDlg", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class TextDlg: public Ui_TextDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTSELECT_H
