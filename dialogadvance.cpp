#include "dialogadvance.h"
#include "ui_dialogadvance.h"

DialogAdvance::DialogAdvance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAdvance)
{
    ui->setupUi(this);
}

DialogAdvance::~DialogAdvance()
{
    delete ui;
}
