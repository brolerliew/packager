#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>
#include "dialogprogress.h"
void itemAddRecur(QTreeWidgetItem* item, std::vector<LddTreeNode>& lddNodes){
    for(auto& node: lddNodes){
        QTreeWidgetItem* itemAdd = new QTreeWidgetItem(item, QStringList(QString::fromStdString(node.path.string())));
        item->addChild(itemAdd);
        itemAddRecur(itemAdd, node.nodes);
    }
}
void MainWindow::updateLabels(){
    ui->lineEdit_contact->setText(QString::fromStdString(packer.contact));
    ui->lineEdit_desc->setText(QString::fromStdString(packer.desc));
    ui->label_icon->setText(QString::fromStdString(packer.icon.string()));
    ui->lineEdit_license->setText(QString::fromStdString(packer.license));
    ui->lineEdit_url->setText(QString::fromStdString(packer.url));
    ui->lineEdit_version->setText(QString::fromStdString(packer.version));
    ui->treeWidget->clear();
    QTreeWidgetItem* root = new QTreeWidgetItem(ui->treeWidget, QStringList("root"));
    ui->treeWidget->insertTopLevelItem(0, root);
    std::vector<LddTreeNode> lddNodes = packer.get_lddNodes();
    itemAddRecur(root, lddNodes);
    ui->treeWidget->expandAll();

    ui->listWidget->clear();
    for(auto path:packer.get_lddPaths()){
        ui->listWidget->addItem(QString::fromStdString(path.string()));
    }
    for(auto path:packer.getExtra()){
        ui->listWidget->addItem(QString::fromStdString(path.string()));
    }
    ui->pushButton_dst->setText("Output Dir:"+ QString::fromStdString(packer.getDstPath()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Ldd Tree");

    packer.setDstPath(QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0].toStdString());
    updateLabels();

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
        updateLabels();
    });
    connect(ui->pushButton_dst,&QPushButton::clicked,this, [this](){
        QString dirName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0],
                                                        QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        if(dirName.isEmpty()){
            return;
        }
        packer.setDstPath(dirName.toStdString());
        ui->pushButton_dst->setText("Output Dir:"+ QString::fromStdString(packer.getDstPath()));
    });
    connect(ui->pushButton_do,&QPushButton::clicked,this, [this](){
        if(packer.getBin().empty()){
            QMessageBox::warning(this, tr("Packager"),
                                 tr("Bin not selected"),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
            return;
        }
        packer.out_appimg = ui->checkBox_appimg->isChecked();
        if(packer.out_appimg&& ui->label_icon->text().isEmpty()){
            QMessageBox::warning(this, tr("Packager"),
                                 tr("Appimg need select icon"),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
            return;
        }
        packer.out_deb = ui->checkBox_deb->isChecked();
        packer.out_rpm = ui->checkBox_rpm->isChecked();
        packer.out_zip = ui->checkBox_zip->isChecked();
        packer.out_dir = ui->checkBox_dir->isChecked();

        packer.contact=ui->lineEdit_contact->text().toStdString();
        packer.version = ui->lineEdit_version->text().toStdString();
        packer.url = ui->lineEdit_url->text().toStdString();
        packer.desc = ui->lineEdit_desc->text().toStdString();
        packer.icon = ui->label_icon->text().toStdString();
        DialogProgress progress(&packer);
        progress.exec();
    });
    connect(ui->pushButton_additional,&QPushButton::clicked,this, [this](){
        QString path = QFileDialog::getOpenFileName(this,tr("Select File, if Binary file selected, will load dependency"), "/bin");
        if(path.isEmpty()){
            return;
        }
        if(!packer.addExtra(path.toStdString())){
            QMessageBox::warning(this, tr("Packager"),
                                 tr((path +" add failed").toStdString().c_str()),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
            return;
        }
        updateLabels();
    });
    connect(ui->pushButton_additional_data,&QPushButton::clicked,this, [this](){
        QString path = QFileDialog::getExistingDirectory(this,tr("Select Data Dir"), QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0]);
        if(path.isEmpty()){
            return;
        }
        if(!packer.addExtra(path.toStdString())){
            QMessageBox::warning(this, tr("Packager"),
                                 tr((path +" add failed").toStdString().c_str()),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
            return;
        }
        updateLabels();
    });
    connect(ui->pushButton_icon,&QPushButton::clicked,this, [this](){
        QString path = QFileDialog::getOpenFileName(this,tr("Select Icon file"),
                                                    QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0],
                                                    tr("Images (*.png *.svg *.jpg *.jpeg)"));
        if(path.isEmpty()){
            return;
        }
        packer.icon = path.toStdString();
        ui->label_icon->setText(path);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

