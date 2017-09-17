#ifndef QQTSELFCHECKFORM_H
#define QQTSELFCHECKFORM_H

#include <QWidget>

namespace Ui {
class QQTSelfCheckForm;
}

class QQTSelfCheckForm : public QWidget
{
    Q_OBJECT

public:
    explicit QQTSelfCheckForm(QWidget *parent = 0);
    ~QQTSelfCheckForm();

private:
    Ui::QQTSelfCheckForm *ui;
};

#endif // QQTSELFCHECKFORM_H
