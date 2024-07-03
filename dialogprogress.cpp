#include "dialogprogress.h"
#include "ui_dialogprogress.h"
#include <QDesktopServices>
#include <QUrl>
DialogProgress::DialogProgress(Packer* packer, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogProgress)
    ,timer_(this)
{
    ui->setupUi(this);
    WorkerThread *workerThread = new WorkerThread(packer, this);
    connect(workerThread, &WorkerThread::resultReady, this,[this,packer](const QString &s){
        QDesktopServices::openUrl(QUrl(QString::fromStdString(packer->getDstPath())));
        close();
    });
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
    connect(&timer_, &QTimer::timeout, this, [this,packer](){
        ui->progressBar->setValue(packer->pack_status);
    });
    timer_.start(100);
}

DialogProgress::~DialogProgress()
{
    delete ui;
}
