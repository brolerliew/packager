#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    packer.setDstPath(QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0].toStdString());
    ui->pushButton_dst->setText("Output Dir:"+ QString::fromStdString(packer.getDstPath().string()));

    connect(ui->pushButton_src,&QPushButton::clicked,this, [this](){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Select Binary"), "/bin");
        if(fileName.isEmpty()){
            return;
        }
        if(!packer.setBin(fileName.toStdString())){
            QMessageBox::warning(this, tr("Packager"),
                                 tr((fileName +"File not ELF").toStdString().c_str()),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
            return;
        }

        ui->pushButton_src->setText("Selected ELF:"+fileName);
    });
    connect(ui->pushButton_dst,&QPushButton::clicked,this, [this](){
        QString dirName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "/home",
                                                        QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        if(dirName.isEmpty()){
            return;
        }
        packer.setDstPath(dirName.toStdString());
        ui->pushButton_dst->setText("Output Dir:"+ dirName);
    });
    connect(ui->pushButton_do,&QPushButton::clicked,this, [this](){
        packer.doPack();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

