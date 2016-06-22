#ifndef HNSELFCHECKFORM_H
#define HNSELFCHECKFORM_H

#include <QWidget>

namespace Ui {
class HNSelfCheckForm;
}

class HNSelfCheckForm : public QWidget
{
    Q_OBJECT

public:
    explicit HNSelfCheckForm(QWidget *parent = 0);
    ~HNSelfCheckForm();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HNSelfCheckForm *ui;
};

#endif // HNSELFCHECKFORM_H
