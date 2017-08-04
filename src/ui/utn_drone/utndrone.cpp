#include "utndrone.h"
#include "QGCMAVLink.h"
#include "MultiVehicleManager.h"
#include "UAS.h"
#include "QGCApplication.h"
#include <QMessageBox>

#include "ui_utndrone.h"

UTNDrone::UTNDrone(const QString& title, QAction* action, MAVLinkProtocol* protocol, QWidget *parent) :
    QGCDockWidget(title, action, parent),
    ui(new Ui::UTNDrone)
{
    ui->setupUi(this);
    ui->lblAccelX->setText(QString::number(0));
    ui->lblAccelY->setText(QString::number(0));
    ui->lblAccelZ->setText(QString::number(0));
    ui->lblGyroX->setText(QString::number(0));
    ui->lblGyroY->setText(QString::number(0));
    ui->lblGyroZ->setText(QString::number(0));
    ui->lblMagX->setText(QString::number(0));
    ui->lblMagY->setText(QString::number(0));
    ui->lblMagZ->setText(QString::number(0));

    activeVehicle = qgcApp()->toolbox()->multiVehicleManager()->activeVehicle();

    if(activeVehicle == NULL)
    {
        this->close();
        return;
    }

    // Me conecto al receptor de mensajes para procesar lo que manda el dron
    connect(protocol, &MAVLinkProtocol::messageReceived, this, &UTNDrone::receiveMessage);

    connect(qgcApp()->toolbox()->multiVehicleManager(), &MultiVehicleManager::activeVehicleChanged, this, &UTNDrone::activeVehicleChanged);
    connect(activeVehicle, &Vehicle::flightModeChanged, this, &UTNDrone::modeChanged);
    connect(qgcApp()->toolbox()->multiVehicleManager(), &MultiVehicleManager::vehicleRemoved, this, &UTNDrone::activeVehicleRemoved);

    connect(ui->chkTestMode, &QCheckBox::stateChanged, this, &UTNDrone::testCheckboxStateChanged);
}

void UTNDrone::receiveMessage(LinkInterface* link,mavlink_message_t message)
{
    mavlink_raw_imu_t rawIMU;
    mavlink_highres_imu_t highresIMU;
    Q_UNUSED(link);

    if (message.sysid != activeVehicle->id()) {
        return;
    }

    switch (message.msgid)
    {
    case MAVLINK_MSG_ID_RAW_IMU:
        mavlink_msg_raw_imu_decode(&message, &rawIMU);
        ui->lblAccelX->setText(QString::number(rawIMU.xacc));
        ui->lblAccelY->setText(QString::number(rawIMU.yacc));
        ui->lblAccelZ->setText(QString::number(rawIMU.zacc));

        ui->lblGyroX->setText(QString::number(rawIMU.xgyro));
        ui->lblGyroY->setText(QString::number(rawIMU.ygyro));
        ui->lblGyroZ->setText(QString::number(rawIMU.zgyro));

        ui->lblMagX->setText(QString::number(rawIMU.xmag));
        ui->lblMagY->setText(QString::number(rawIMU.ymag));
        ui->lblMagZ->setText(QString::number(rawIMU.zmag));
        break;

    case MAVLINK_MSG_ID_HIGHRES_IMU:
        mavlink_msg_highres_imu_decode(&message, &highresIMU);
        ui->lblAccelX->setText(QString::number(highresIMU.xacc));
        ui->lblAccelY->setText(QString::number(highresIMU.yacc));
        ui->lblAccelZ->setText(QString::number(highresIMU.zacc));

        ui->lblGyroX->setText(QString::number(highresIMU.xgyro));
        ui->lblGyroY->setText(QString::number(highresIMU.ygyro));
        ui->lblGyroZ->setText(QString::number(highresIMU.zgyro));

        ui->lblMagX->setText(QString::number(highresIMU.xmag));
        ui->lblMagY->setText(QString::number(highresIMU.ymag));
        ui->lblMagZ->setText(QString::number(highresIMU.zmag));
        break;
    }
}

void UTNDrone::activeVehicleChanged(Vehicle *vehicle)
{
    // Reconecto la señal del nuevo vehículo activo
    if(activeVehicle != NULL)
    {
        disconnect(activeVehicle, 0, this, 0);
        activeVehicle = vehicle;
        connect(activeVehicle, &Vehicle::flightModeChanged, this, &UTNDrone::modeChanged);
    }
}

void UTNDrone::activeVehicleRemoved(Vehicle *vehicle)
{
    // Si se remueve un vehículo, me fijo si es el activo
    if(vehicle->id() == activeVehicle->id())
    {
        activeVehicle = NULL;
    }
}

void UTNDrone::modeChanged(const QString& flightMode)
{
    // Sincronizo el checkbox con el estado del dron
    if(flightMode.contains("Test"))
    {
        ui->chkTestMode->setChecked(true);
    }
    else
    {
        ui->chkTestMode->setChecked(false);
    }
}

void UTNDrone::testCheckboxStateChanged(int state)
{
    if(activeVehicle == NULL)
    {
        QMessageBox::critical(this, "Error", "No hay un vehículo activo.");
        return;
    }

    if(activeVehicle->armed())
    {
        QMessageBox msgBox;
        msgBox.setText("Esta opción no está disponible si el vehículo está ARMED.");
        msgBox.exec();
    }
    else
    {
        if(state == Qt::Checked)
        {
            // Paso al modo de pruebas
            activeVehicle->sendMavCommand(MAV_COMP_ID_ALL, MAV_CMD_DO_SET_MODE, false, (float)(MAV_MODE_FLAG_TEST_ENABLED));
        }
        else if(state == Qt::Unchecked)
        {
            // Vuelvo al modo base
            activeVehicle->sendMavCommand(MAV_COMP_ID_ALL, MAV_CMD_DO_SET_MODE, false, 0.0f);
        }
    }
}

UTNDrone::~UTNDrone()
{
    delete ui;
}
