/********************************************************************************
** Form generated from reading UI file 'mainwindowui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWUI_H
#define UI_MAINWINDOWUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>

QT_BEGIN_NAMESPACE

class Ui_MainWindowUI
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindowUI)
    {
        if (MainWindowUI->objectName().isEmpty())
            MainWindowUI->setObjectName(QString::fromUtf8("MainWindowUI"));
        MainWindowUI->resize(838, 618);
        action = new QAction(MainWindowUI);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(MainWindowUI);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(MainWindowUI);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        menuBar = new QMenuBar(MainWindowUI);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 838, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindowUI->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(action_3);

        retranslateUi(MainWindowUI);

        QMetaObject::connectSlotsByName(MainWindowUI);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowUI)
    {
        MainWindowUI->setWindowTitle(QCoreApplication::translate("MainWindowUI", "MainWindowUI", nullptr));
        action->setText(QCoreApplication::translate("MainWindowUI", "\346\211\223\345\274\200", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindowUI", "\344\277\235\345\255\230", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindowUI", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindowUI", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowUI: public Ui_MainWindowUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWUI_H
