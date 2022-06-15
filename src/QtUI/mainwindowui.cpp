//
// Created by bigdata-wgf on 2022/6/2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindowUI.h" resolved

#include "mainwindowui.h"
#include "ui_mainwindowui.h"


MainWindowUI::MainWindowUI(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindowUI) {
    ui->setupUi(this);
}

MainWindowUI::~MainWindowUI() {
    delete ui;
}
