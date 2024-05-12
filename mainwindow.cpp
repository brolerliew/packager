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
    dstDir = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
    ui->pushButton_dst->setText("Output Dir:"+dstDir.absolutePath());

    connect(ui->pushButton_src,&QPushButton::clicked,this, [this](){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Select Binary"), "/bin");
        if(fileName.isEmpty()){
            return;
        }
        srcFile.setFile(fileName);
        if(!srcFile.isExecutable()){
            QMessageBox::warning(this, tr("Packager"),
                                 tr("File not ELF"),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
            srcFile.setFile("");
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
        dstDir = dirName;
        ui->pushButton_dst->setText("Output Dir:"+dstDir.absolutePath());
    });
    connect(ui->pushButton_do,&QPushButton::clicked,this, [this](){
        if(!srcFile.exists()){
            QMessageBox::warning(this, tr("Packager"),
                                           tr("Not select ELF file to Package"),
                                           QMessageBox::Ok,
                                           QMessageBox::Ok);
            return;
        }
        QString name = srcFile.fileName();
        QString rootDir = "pack/deb/"+name+"/opt/"+name;
        if(!dstDir.mkpath(rootDir)){
            return;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

