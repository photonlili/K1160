#ifndef HNWINDOW_H
#define HNWINDOW_H

#include <QObject>

#include "hnmainform.h"
#include "hnloginform.h"

class HNWindow : public QObject
{
    Q_OBJECT
public:
    explicit HNWindow(QObject *parent = 0);

signals:

public slots:

};

#endif // HNWINDOW_H
