#ifndef HNREPORT_H
#define HNREPORT_H

#include "hnwordexpress.h"

class HNReport : public HNWordExpress
{
    Q_OBJECT
public:
    explicit HNReport(QObject *parent = 0);

    void createSampleReport(const QString& head, const QString& foot, const QString& title,
                              const QTableView* table);
    void GenerateComplexReport();
signals:

public slots:


    // HNWordExpress interface
protected:

private:
};

HNReport* HNReportInstance(QObject* parent);

#endif // HNREPORT_H
