#ifndef UTNDRONE_H
#define UTNDRONE_H

#include <QWidget>
#include "QGCDockWidget.h"
#include "MAVLinkProtocol.h"
#include "Vehicle.h"

namespace Ui {
class UTNDrone;
}

class UTNDrone : public QGCDockWidget
{
    Q_OBJECT

public:
    explicit UTNDrone(const QString& title, QAction* action, MAVLinkProtocol* protocol, QWidget *parent = 0);
    ~UTNDrone();

public slots:
    void receiveMessage(LinkInterface* link,mavlink_message_t message);
    void modeChanged(const QString& flightMode);
    void testCheckboxStateChanged(int state);
    void activeVehicleChanged(Vehicle* vehicle);
    void activeVehicleRemoved(Vehicle* vehicle);
    void buttonClicked(int index);

private:
    Ui::UTNDrone *ui;
    Vehicle *activeVehicle;

    QVector<QWidget *> PWMLineEdits;
    QVector<QWidget *> PWMButtons;
};

#endif // UTNDRONE_H
