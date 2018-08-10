/********************************************************************************
** Form generated from reading UI file 'entrance.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_2D_ENTRANCE_H
#define UI_2D_ENTRANCE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Entrance
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit;

    void setupUi(QDialog *Entrance)
    {
        if (Entrance->objectName().isEmpty())
            Entrance->setObjectName(QString::fromUtf8("Entrance"));
        Entrance->resize(400, 300);
        gridLayoutWidget = new QWidget(Entrance);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 40, 363, 211));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 2);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 6, 0, 1, 2);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 4, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        dateTimeEdit = new QDateTimeEdit(gridLayoutWidget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setEnabled(true);
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        dateTimeEdit->setFont(font);
        dateTimeEdit->setLayoutDirection(Qt::LeftToRight);
        dateTimeEdit->setAlignment(Qt::AlignCenter);
        dateTimeEdit->setReadOnly(true);
        dateTimeEdit->setDateTime(QDateTime(QDate(2018, 4, 16), QTime(0, 0, 0)));
        dateTimeEdit->setCurrentSection(QDateTimeEdit::DaySection);

        gridLayout->addWidget(dateTimeEdit, 1, 0, 1, 2);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(comboBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(Entrance);

        QMetaObject::connectSlotsByName(Entrance);
    } // setupUi

    void retranslateUi(QDialog *Entrance)
    {
        Entrance->setWindowTitle(QApplication::translate("Entrance", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Entrance", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt;\">No vehicle selected</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Entrance", "Select", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Entrance", "Item 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Entrance", "Item 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Entrance", "Item 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Entrance", "Item 4", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("Entrance", "Please select a vehicle among all of these:", 0, QApplication::UnicodeUTF8));
        dateTimeEdit->setDisplayFormat(QApplication::translate("Entrance", "dddd dd MMMM - HH:mm:ss", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Entrance: public Ui_Entrance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_2D_ENTRANCE_H
