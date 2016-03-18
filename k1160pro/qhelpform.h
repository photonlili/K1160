#ifndef QHELPFORM_H
#define QHELPFORM_H

#include <QWidget>

namespace Ui {
class QHelpForm;
}

class QHelpForm : public QWidget
{
    Q_OBJECT

public:
    explicit QHelpForm(QWidget *parent = 0);
    ~QHelpForm();
private:
    void InitOCX();
    void InitSings();
private:
    Ui::QHelpForm *ui;
};

#endif // QHELPFORM_H
