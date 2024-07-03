#ifndef DIALOGPROGRESS_H
#define DIALOGPROGRESS_H

#include <QDialog>
#include "libpacker/packer.h"
#include <QThread>
#include <QTimer>
namespace Ui {
class DialogProgress;
}
class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(Packer* packer, QWidget *parent):packer_(packer){

    }
private:
    void run() override {
        packer_->doPack();
        QString result;
        /* ... here is the expensive or blocking operation ... */
        emit resultReady(result);
    }
    Packer* packer_;
signals:
    void resultReady(const QString &s);
};
class DialogProgress : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProgress(Packer* packer, QWidget *parent = nullptr);
    ~DialogProgress();

private:
    Ui::DialogProgress *ui;
    QTimer timer_;
};

#endif // DIALOGPROGRESS_H
