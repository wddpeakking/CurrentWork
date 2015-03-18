/********************************************************************************
** Form generated from reading UI file 'cameraSelect.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASELECT_H
#define UI_CAMERASELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_cameraSelect
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *cameraSelect)
    {
        if (cameraSelect->objectName().isEmpty())
            cameraSelect->setObjectName(QStringLiteral("cameraSelect"));
        cameraSelect->resize(458, 96);
        comboBox = new QComboBox(cameraSelect);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(90, 20, 351, 22));
        label = new QLabel(cameraSelect);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 61, 21));
        okButton = new QPushButton(cameraSelect);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(289, 60, 75, 23));
        cancelButton = new QPushButton(cameraSelect);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(370, 60, 75, 23));

        retranslateUi(cameraSelect);
        QObject::connect(okButton, SIGNAL(clicked()), cameraSelect, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), cameraSelect, SLOT(reject()));

        QMetaObject::connectSlotsByName(cameraSelect);
    } // setupUi

    void retranslateUi(QDialog *cameraSelect)
    {
        cameraSelect->setWindowTitle(QApplication::translate("cameraSelect", "\351\200\211\346\213\251\350\256\276\345\244\207", 0));
        label->setText(QApplication::translate("cameraSelect", "\350\257\267\351\200\211\346\213\251\357\274\232", 0));
        okButton->setText(QApplication::translate("cameraSelect", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("cameraSelect", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class cameraSelect: public Ui_cameraSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASELECT_H
