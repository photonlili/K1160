#ifndef QQTPRINTINFODIALOG_H
#define QQTPRINTINFODIALOG_H

#include <QDialog>

namespace Ui {
class QQTPrintInfoDialog;
}

class QQTPrintInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QQTPrintInfoDialog(QWidget *parent = 0);
    ~QQTPrintInfoDialog();

    void initAll();
    void printInfo(QString& title, QString& header, QString& footer);

private slots:

private:
    Ui::QQTPrintInfoDialog *ui;
};

#endif // QQTPRINTINFODIALOG_H
