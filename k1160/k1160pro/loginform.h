#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include "qcheckfrom.h"
#include "qdatabasequery.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
    void SetUser();
    void setLevel(int ilevel);
    int  getLevel();
    void setusername(int id);
    void setpasswd(QString pwd);
public slots:
    void on_pb_logindlg_login_clicked();

private slots:
    void changescreen(int index);
    void on_le_logindlg_username_textChanged(const QString &arg1);

    void on_le_logindlg_username_textEdited(const QString &arg1);

    void on_cb_username_currentTextChanged(const QString &arg1);

private:
    void InitOCX();


    void mousePressEvent(QMouseEvent *e);

private:
    QString     m_strexpress;
    QStringList linstname;
    QStringList linstvalues;
    QStringList linstvaluestemp;
    QString     strtable;
    QDatabasequery *pdataquery;
    QCheckFrom  *m_pCheckDlg;
    QTextCodec  *m_ptc;
    Ui::LoginForm *ui;
    int m_ilevel;

};

#endif // MAINWINDOW_H
