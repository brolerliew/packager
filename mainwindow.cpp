#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>
void MainWindow::updateLabels(){
    ui->label_contact->setText(QString::fromStdString(packer.contact));
    ui->label_desc->setText(QString::fromStdString(packer.desc));
    ui->label_icon->setText(QString::fromStdString(packer.icon.string()));
    ui->label_license->setText(QString::fromStdString(packer.license));
    ui->label_packageName->setText(QString::fromStdString(packer.packageName));
    ui->label_url->setText(QString::fromStdString(packer.url));
    ui->label_version->setText(QString::fromStdString(packer.version));
}

void itemAddRecur(QTreeWidgetItem* item, std::vector<LddTreeNode>& lddNodes){
    for(auto& node: lddNodes){
        QTreeWidgetItem* itemAdd = new QTreeWidgetItem(item, QStringList(QString::fromStdString(node.path.string())));
        item->addChild(itemAdd);
        itemAddRecur(itemAdd, node.nodes);
    }
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

        ui->treeWidget->clear();
        QTreeWidgetItem* root = new QTreeWidgetItem(ui->treeWidget, QStringList(fileName));
        ui->treeWidget->insertTopLevelItem(0, root);
        std::vector<LddTreeNode> lddNodes = packer.get_lddNodes();
        itemAddRecur(root, lddNodes);
        ui->treeWidget->expandAll();

        ui->listWidget->clear();
        for(auto path:packer.get_lddPaths()){
            ui->listWidget->addItem(QString::fromStdString(path.string()));
        }
        updateLabels();
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
        packer.out_appimg = ui->checkBox_appimg->isChecked();
        packer.out_deb = ui->checkBox_deb->isChecked();
        packer.out_rpm = ui->checkBox_rpm->isChecked();
        packer.out_zip = ui->checkBox_zip->isChecked();
        packer.doPack();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

