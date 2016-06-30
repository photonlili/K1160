#ifndef QTANKAPP_H
#define QTANKAPP_H

#include <QApplication>

class HNApp : public QApplication
{
    Q_OBJECT
public:
    explicit HNApp(int &argc, char **argv);
    virtual ~HNApp();

    void setTheme();

    void setLanguage();

signals:

public slots:
    void slotUPanAutoRun(int status);

private:
    QTranslator* language;
};

#endif // QTANKAPP_H
