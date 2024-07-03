#ifndef DIALOGADVANCE_H
#define DIALOGADVANCE_H

#include <QDialog>

namespace Ui {
class DialogAdvance;
}

class DialogAdvance : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdvance(QWidget *parent = nullptr);
    ~DialogAdvance();

private:
    Ui::DialogAdvance *ui;
};

#endif // DIALOGADVANCE_H
