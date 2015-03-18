/********************************************************************************
** Form generated from reading UI file 'LkSettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LKSETTINGDLG_H
#define UI_LKSETTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LkSetting
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_4;
    QLabel *label_4;
    QSpinBox *spinBox_LkFPS;
    QLabel *label_6;
    QComboBox *comboBox_LkMl;
    QCheckBox *checkBox_LkZxh;
    QLabel *label_5;
    QCheckBox *checkBox_LkXssb;
    QComboBox *comboBox_LkFbl;
    QCheckBox *checkBox_LkAero;
    QCheckBox *checkBox_LkSaveFile;
    QLabel *label_12;
    QLineEdit *lineEdit_LkSavePath;
    QPushButton *pushButton_SelectPath;
    QCheckBox *checkBox_LkDesktop;
    QPushButton *pushButton_More;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QLabel *label_10;
    QComboBox *comboBox_LkCPUys;
    QComboBox *comboBox_LkGjzsm;
    QLabel *label_9;
    QLabel *label_3;
    QLabel *label;
    QComboBox *comboBox_LkPSYTj;
    QLineEdit *lineEdit;
    QComboBox *comboBox_LkBxbmzs;
    QCheckBox *checkBox_LkBgjz;
    QLabel *label_7;
    QLabel *label_2;
    QLabel *label_11;
    QComboBox *comboBox_LkPzwj;
    QComboBox *comboBox_LkMllx;
    QLabel *label_8;
    QSpinBox *spinBox_LkPz;
    QGroupBox *groupBox_2;
    QLabel *label_24;
    QComboBox *comboBox_LkSb;
    QComboBox *comboBox_LkBmgs;
    QLabel *label_25;
    QComboBox *comboBox_LkPd;
    QLabel *label_26;
    QComboBox *comboBox_LkCyl;
    QLabel *label_27;
    QComboBox *comboBox_LkBl;
    QLabel *label_28;
    QGroupBox *groupBox_3;
    QLabel *label_23;
    QLineEdit *lineEdit_LkURL;
    QPushButton *pushButton_back;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *LkSetting)
    {
        if (LkSetting->objectName().isEmpty())
            LkSetting->setObjectName(QStringLiteral("LkSetting"));
        LkSetting->resize(592, 540);
        tabWidget = new QTabWidget(LkSetting);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 571, 541));
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 571, 461));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 120, 54, 12));
        spinBox_LkFPS = new QSpinBox(groupBox_4);
        spinBox_LkFPS->setObjectName(QStringLiteral("spinBox_LkFPS"));
        spinBox_LkFPS->setGeometry(QRect(90, 110, 71, 22));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 80, 54, 12));
        comboBox_LkMl = new QComboBox(groupBox_4);
        comboBox_LkMl->setObjectName(QStringLiteral("comboBox_LkMl"));
        comboBox_LkMl->setGeometry(QRect(90, 70, 321, 22));
        checkBox_LkZxh = new QCheckBox(groupBox_4);
        checkBox_LkZxh->setObjectName(QStringLiteral("checkBox_LkZxh"));
        checkBox_LkZxh->setGeometry(QRect(30, 170, 151, 16));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 40, 54, 12));
        checkBox_LkXssb = new QCheckBox(groupBox_4);
        checkBox_LkXssb->setObjectName(QStringLiteral("checkBox_LkXssb"));
        checkBox_LkXssb->setGeometry(QRect(30, 210, 71, 16));
        comboBox_LkFbl = new QComboBox(groupBox_4);
        comboBox_LkFbl->setObjectName(QStringLiteral("comboBox_LkFbl"));
        comboBox_LkFbl->setGeometry(QRect(90, 30, 321, 22));
        checkBox_LkAero = new QCheckBox(groupBox_4);
        checkBox_LkAero->setObjectName(QStringLiteral("checkBox_LkAero"));
        checkBox_LkAero->setGeometry(QRect(30, 250, 131, 16));
        checkBox_LkSaveFile = new QCheckBox(groupBox_4);
        checkBox_LkSaveFile->setObjectName(QStringLiteral("checkBox_LkSaveFile"));
        checkBox_LkSaveFile->setGeometry(QRect(30, 350, 171, 16));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(30, 390, 61, 16));
        lineEdit_LkSavePath = new QLineEdit(groupBox_4);
        lineEdit_LkSavePath->setObjectName(QStringLiteral("lineEdit_LkSavePath"));
        lineEdit_LkSavePath->setGeometry(QRect(90, 380, 261, 31));
        lineEdit_LkSavePath->setReadOnly(true);
        pushButton_SelectPath = new QPushButton(groupBox_4);
        pushButton_SelectPath->setObjectName(QStringLiteral("pushButton_SelectPath"));
        pushButton_SelectPath->setGeometry(QRect(360, 380, 51, 31));
        checkBox_LkDesktop = new QCheckBox(groupBox_4);
        checkBox_LkDesktop->setObjectName(QStringLiteral("checkBox_LkDesktop"));
        checkBox_LkDesktop->setGeometry(QRect(30, 290, 131, 16));
        pushButton_More = new QPushButton(tab);
        pushButton_More->setObjectName(QStringLiteral("pushButton_More"));
        pushButton_More->setGeometry(QRect(0, 490, 111, 31));
        pushButton_More->setDefault(false);
        pushButton_More->setFlat(false);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 281, 401));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 155, 71, 16));
        comboBox_LkCPUys = new QComboBox(groupBox);
        comboBox_LkCPUys->setObjectName(QStringLiteral("comboBox_LkCPUys"));
        comboBox_LkCPUys->setGeometry(QRect(140, 190, 101, 22));
        comboBox_LkGjzsm = new QComboBox(groupBox);
        comboBox_LkGjzsm->setObjectName(QStringLiteral("comboBox_LkGjzsm"));
        comboBox_LkGjzsm->setGeometry(QRect(140, 150, 101, 22));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 275, 54, 12));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 35, 51, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 195, 81, 16));
        comboBox_LkPSYTj = new QComboBox(groupBox);
        comboBox_LkPSYTj->setObjectName(QStringLiteral("comboBox_LkPSYTj"));
        comboBox_LkPSYTj->setGeometry(QRect(140, 70, 101, 22));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(140, 30, 101, 20));
        lineEdit->setEchoMode(QLineEdit::Normal);
        lineEdit->setReadOnly(true);
        comboBox_LkBxbmzs = new QComboBox(groupBox);
        comboBox_LkBxbmzs->setObjectName(QStringLiteral("comboBox_LkBxbmzs"));
        comboBox_LkBxbmzs->setGeometry(QRect(140, 230, 101, 22));
        checkBox_LkBgjz = new QCheckBox(groupBox);
        checkBox_LkBgjz->setObjectName(QStringLiteral("checkBox_LkBgjz"));
        checkBox_LkBgjz->setGeometry(QRect(20, 320, 141, 16));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 75, 54, 12));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 360, 31, 16));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 235, 81, 16));
        comboBox_LkPzwj = new QComboBox(groupBox);
        comboBox_LkPzwj->setObjectName(QStringLiteral("comboBox_LkPzwj"));
        comboBox_LkPzwj->setGeometry(QRect(140, 110, 101, 22));
        comboBox_LkMllx = new QComboBox(groupBox);
        comboBox_LkMllx->setObjectName(QStringLiteral("comboBox_LkMllx"));
        comboBox_LkMllx->setGeometry(QRect(140, 270, 101, 22));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 115, 91, 16));
        spinBox_LkPz = new QSpinBox(groupBox);
        spinBox_LkPz->setObjectName(QStringLiteral("spinBox_LkPz"));
        spinBox_LkPz->setGeometry(QRect(140, 360, 101, 22));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(300, 0, 261, 401));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(20, 35, 54, 12));
        comboBox_LkSb = new QComboBox(groupBox_2);
        comboBox_LkSb->setObjectName(QStringLiteral("comboBox_LkSb"));
        comboBox_LkSb->setGeometry(QRect(120, 30, 101, 22));
        comboBox_LkBmgs = new QComboBox(groupBox_2);
        comboBox_LkBmgs->setObjectName(QStringLiteral("comboBox_LkBmgs"));
        comboBox_LkBmgs->setGeometry(QRect(120, 70, 101, 22));
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(20, 75, 54, 12));
        comboBox_LkPd = new QComboBox(groupBox_2);
        comboBox_LkPd->setObjectName(QStringLiteral("comboBox_LkPd"));
        comboBox_LkPd->setGeometry(QRect(120, 110, 101, 22));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(20, 115, 54, 12));
        comboBox_LkCyl = new QComboBox(groupBox_2);
        comboBox_LkCyl->setObjectName(QStringLiteral("comboBox_LkCyl"));
        comboBox_LkCyl->setGeometry(QRect(120, 150, 101, 22));
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(20, 155, 54, 12));
        comboBox_LkBl = new QComboBox(groupBox_2);
        comboBox_LkBl->setObjectName(QStringLiteral("comboBox_LkBl"));
        comboBox_LkBl->setGeometry(QRect(120, 190, 101, 22));
        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(20, 195, 54, 12));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 410, 561, 61));
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(20, 30, 71, 16));
        lineEdit_LkURL = new QLineEdit(groupBox_3);
        lineEdit_LkURL->setObjectName(QStringLiteral("lineEdit_LkURL"));
        lineEdit_LkURL->setGeometry(QRect(100, 19, 431, 31));
        pushButton_back = new QPushButton(tab_2);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));
        pushButton_back->setGeometry(QRect(0, 490, 111, 31));
        tabWidget->addTab(tab_2, QString());
        okButton = new QPushButton(LkSetting);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(380, 500, 91, 31));
        cancelButton = new QPushButton(LkSetting);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(484, 500, 91, 31));

        retranslateUi(LkSetting);
        QObject::connect(okButton, SIGNAL(clicked()), LkSetting, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), LkSetting, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LkSetting);
    } // setupUi

    void retranslateUi(QDialog *LkSetting)
    {
        LkSetting->setWindowTitle(QApplication::translate("LkSetting", "\350\256\276\347\275\256", 0));
        groupBox_4->setTitle(QApplication::translate("LkSetting", "\344\270\200\350\210\254\350\256\276\347\275\256", 0));
        label_4->setText(QApplication::translate("LkSetting", "FPS\357\274\232", 0));
        label_6->setText(QApplication::translate("LkSetting", "\347\240\201\347\216\207\357\274\232", 0));
        checkBox_LkZxh->setText(QApplication::translate("LkSetting", "\347\202\271\345\207\273\346\216\250\351\200\201\345\220\216\350\207\252\345\212\250\346\234\200\345\260\217\345\214\226", 0));
        label_5->setText(QApplication::translate("LkSetting", "\345\210\206\350\276\250\347\216\207\357\274\232", 0));
        checkBox_LkXssb->setText(QApplication::translate("LkSetting", "\346\230\276\347\244\272\351\274\240\346\240\207", 0));
        checkBox_LkAero->setText(QApplication::translate("LkSetting", "\345\220\257\345\212\250\346\227\266\347\246\201\347\224\250Aero\346\225\210\346\236\234", 0));
        checkBox_LkSaveFile->setText(QApplication::translate("LkSetting", "\345\260\206\347\233\264\346\222\255\350\247\206\351\242\221\344\277\235\345\255\230\345\234\250\346\234\254\345\234\260", 0));
        label_12->setText(QApplication::translate("LkSetting", "\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", 0));
        pushButton_SelectPath->setText(QApplication::translate("LkSetting", "...", 0));
        checkBox_LkDesktop->setText(QApplication::translate("LkSetting", "\346\267\273\345\212\240\346\241\214\351\235\242\346\272\220\346\227\266\346\234\200\345\260\217\345\214\226", 0));
        pushButton_More->setText(QApplication::translate("LkSetting", "\351\253\230\347\272\247", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("LkSetting", "\350\247\206\351\242\221", 0));
        groupBox->setTitle(QApplication::translate("LkSetting", "\350\247\206\351\242\221", 0));
        label_10->setText(QApplication::translate("LkSetting", "\345\205\263\351\224\256\345\270\247\346\225\260\347\233\256\357\274\232", 0));
        label_9->setText(QApplication::translate("LkSetting", "\347\240\201\347\216\207\347\261\273\345\236\213\357\274\232", 0));
        label_3->setText(QApplication::translate("LkSetting", "\347\274\226\347\240\201\345\231\250\357\274\232", 0));
        label->setText(QApplication::translate("LkSetting", "x264 CPU\351\242\204\350\256\276\357\274\232", 0));
        lineEdit->setText(QApplication::translate("LkSetting", "x264", 0));
        checkBox_LkBgjz->setText(QApplication::translate("LkSetting", "\344\275\277\347\224\250 B \345\271\200\344\275\234\344\270\272\345\205\263\351\224\256\345\270\247", 0));
        label_7->setText(QApplication::translate("LkSetting", "PSY\350\260\203\350\212\202\357\274\232", 0));
        label_2->setText(QApplication::translate("LkSetting", "\345\223\201\350\264\250\357\274\232", 0));
        label_11->setText(QApplication::translate("LkSetting", "\345\271\266\350\241\214\347\274\226\347\240\201\345\270\247\346\225\260\357\274\232", 0));
        label_8->setText(QApplication::translate("LkSetting", "\347\274\226\347\240\201\351\205\215\347\275\256\346\226\207\344\273\266\357\274\232", 0));
        groupBox_2->setTitle(QApplication::translate("LkSetting", "\351\237\263\351\242\221", 0));
        label_24->setText(QApplication::translate("LkSetting", "\350\256\276\345\244\207\357\274\232", 0));
        label_25->setText(QApplication::translate("LkSetting", "\347\274\226\347\240\201\346\240\274\345\274\217\357\274\232", 0));
        label_26->setText(QApplication::translate("LkSetting", "\351\242\221\351\201\223\357\274\232", 0));
        label_27->setText(QApplication::translate("LkSetting", "\351\207\207\346\240\267\347\216\207\357\274\232", 0));
        label_28->setText(QApplication::translate("LkSetting", "\345\210\253\347\216\207\357\274\232", 0));
        groupBox_3->setTitle(QApplication::translate("LkSetting", "\347\275\221\347\273\234", 0));
        label_23->setText(QApplication::translate("LkSetting", "\346\265\201\345\252\222\344\275\223\345\234\260\345\235\200\357\274\232", 0));
        pushButton_back->setText(QApplication::translate("LkSetting", "\350\277\224\345\233\236", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("LkSetting", "\351\253\230\347\272\247", 0));
        okButton->setText(QApplication::translate("LkSetting", "\347\241\256\345\256\232", 0));
        cancelButton->setText(QApplication::translate("LkSetting", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class LkSetting: public Ui_LkSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LKSETTINGDLG_H
