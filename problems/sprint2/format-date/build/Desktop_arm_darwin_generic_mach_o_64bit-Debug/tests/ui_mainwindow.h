/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QLineEdit *le_date;
    QLabel *label;
    QLineEdit *le_day;
    QLabel *label_2;
    QLineEdit *le_month;
    QLabel *label_3;
    QLineEdit *le_year;
    QLabel *label_4;
    QLabel *lbl_format_type1;
    QLabel *label_5;
    QLabel *lbl_format_type2;
    QLabel *label_6;
    QLabel *lbl_format_type3;
    QLabel *lbl_message;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(294, 439);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        verticalLayout->addWidget(label_7);

        le_date = new QLineEdit(centralwidget);
        le_date->setObjectName("le_date");

        verticalLayout->addWidget(le_date);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        le_day = new QLineEdit(centralwidget);
        le_day->setObjectName("le_day");

        verticalLayout->addWidget(le_day);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        le_month = new QLineEdit(centralwidget);
        le_month->setObjectName("le_month");

        verticalLayout->addWidget(le_month);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        le_year = new QLineEdit(centralwidget);
        le_year->setObjectName("le_year");

        verticalLayout->addWidget(le_year);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        QFont font;
        font.setBold(true);
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        lbl_format_type1 = new QLabel(centralwidget);
        lbl_format_type1->setObjectName("lbl_format_type1");

        verticalLayout->addWidget(lbl_format_type1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        lbl_format_type2 = new QLabel(centralwidget);
        lbl_format_type2->setObjectName("lbl_format_type2");

        verticalLayout->addWidget(lbl_format_type2);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        lbl_format_type3 = new QLabel(centralwidget);
        lbl_format_type3->setObjectName("lbl_format_type3");

        verticalLayout->addWidget(lbl_format_type3);

        lbl_message = new QLabel(centralwidget);
        lbl_message->setObjectName("lbl_message");

        verticalLayout->addWidget(lbl_message);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202 \320\264\320\260\321\202\321\213", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\321\202\321\203:", nullptr));
        le_date->setInputMask(QCoreApplication::translate("MainWindow", "00.00.0000", nullptr));
        le_date->setPlaceholderText(QCoreApplication::translate("MainWindow", "00.00.0000", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\275\321\214:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\201\321\217\321\206:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\320\264:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202 \320\264\320\264.\320\274\320\274.\320\263\320\263\320\263\320\263", nullptr));
        lbl_format_type1->setText(QCoreApplication::translate("MainWindow", "QLabel lbl_format_type1", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202 \320\274\320\274/\320\264\320\264/\320\263\320\263\320\263\320\263", nullptr));
        lbl_format_type2->setText(QCoreApplication::translate("MainWindow", "QLabel lbl_format_type2", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202: \320\264\320\264 \320\274\320\265\321\201\321\217\321\206 \320\263\320\263\320\263\320\263", nullptr));
        lbl_format_type3->setText(QCoreApplication::translate("MainWindow", "QLabel lbl_format_type3", nullptr));
        lbl_message->setText(QCoreApplication::translate("MainWindow", "QLabel lbl_message", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
