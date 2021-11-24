//
// Created by nhatv on 24 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_temp.h" resolved

#include "temp.h"
#include "ui_temp.h"


temp::temp(QWidget *parent) :
        QWidget(parent), ui(new Ui::temp) {
    ui->setupUi(this);
}

temp::~temp() {
    delete ui;
}

