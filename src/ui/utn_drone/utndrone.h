#ifndef UTNDRONE_H
#define UTNDRONE_H

#include <QWidget>
#include "QGCDockWidget.h"

namespace Ui {
class UTNDrone;
}

class UTNDrone : public QGCDockWidget
{
    Q_OBJECT

public:
    explicit UTNDrone(const QString& title, QAction* action, QWidget *parent = 0);
    ~UTNDrone();

private:
    Ui::UTNDrone *ui;
};

#endif // UTNDRONE_H
