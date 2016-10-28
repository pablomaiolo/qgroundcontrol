#include "pruebacomunicacion.h"
#include "ui_pruebacomunicacion.h"
#include "Vehicle.h"
#include <QMessageBox>
#include "QGCApplication.h"
#include <QtDebug>

PruebaComunicacion::PruebaComunicacion(const QString& title, QAction* action, QWidget *parent):
    QGCDockWidget(title, action, parent),
    ui(new Ui::PruebaComunicacion)
{
    ui->setupUi(this);

    QDoubleValidator *validator = new QDoubleValidator(-100, 100, 2, this);
    ui->alturaLineEdit->setValidator(validator);
}

PruebaComunicacion::~PruebaComunicacion()
{
    delete ui;
}

void PruebaComunicacion::on_cambiarAlturaButton_clicked()
{
    QGCApplication *app = qgcApp();
    Vehicle *vehiculoActivo = app->toolbox()->multiVehicleManager()->activeVehicle();

    if(vehiculoActivo == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("No hay un vehículo activo.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }

    if(vehiculoActivo->flying())
    {
        vehiculoActivo->guidedModeChangeAltitude(ui->alturaLineEdit->text().toDouble());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("El dron no está volando.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void PruebaComunicacion::on_aterrizarButton_clicked()
{
    QGCApplication *app = qgcApp();
    Vehicle *vehiculoActivo = app->toolbox()->multiVehicleManager()->activeVehicle();

    if(vehiculoActivo == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("No hay un vehículo activo.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }

    if(vehiculoActivo->flying())
    {
        vehiculoActivo->guidedModeLand();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("El dron no está volando.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}
