#include "dialogprogress.h"
#include "ui_dialogprogress.h"

DialogProgress::DialogProgress(Packer* packer, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogProgress)
{
    ui->setupUi(this);
    ui->progressBar->setValue(50);
    packer->doPack();
}

DialogProgress::~DialogProgress()
{
    delete ui;
}
