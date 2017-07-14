#include "utndrone.h"
#include "ui_utndrone.h"

UTNDrone::UTNDrone(const QString& title, QAction* action, QWidget *parent) :
    QGCDockWidget(title, action, parent),
    ui(new Ui::UTNDrone)
{
    ui->setupUi(this);
}

UTNDrone::~UTNDrone()
{
    delete ui;
}
