#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dstPath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    ui->pushButton_dst->setText("Output Dir:"+dstPath);

    connect(ui->pushButton_src,&QPushButton::clicked,this, [this](){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Select Binary"), "/bin");
        if(fileName.isEmpty()){
            return;
        }
        srcFile = fileName;
        ui->pushButton_src->setText("Selected ELF:"+fileName);
    });
    connect(ui->pushButton_dst,&QPushButton::clicked,this, [this](){
        QString dirName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "/home",
                                                        QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        if(dirName.isEmpty()){
            return;
        }
        dstPath = dirName;
        ui->pushButton_dst->setText("Output Dir:"+dstPath);
    });
    connect(ui->pushButton_do,&QPushButton::clicked,this, [this](){
        if(srcFile.isEmpty()){
            int ret = QMessageBox::warning(this, tr("Packager"),
                                           tr("Not select ELF file to Package"),
                                           QMessageBox::Ok,
                                           QMessageBox::Ok);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

