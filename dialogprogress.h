#ifndef DIALOGPROGRESS_H
#define DIALOGPROGRESS_H

#include <QDialog>
#include "libpacker/packer.h"

namespace Ui {
class DialogProgress;
}

class DialogProgress : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProgress(Packer* packer, QWidget *parent = nullptr);
    ~DialogProgress();

private:
    Ui::DialogProgress *ui;
};

#endif // DIALOGPROGRESS_H
