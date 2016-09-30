#ifndef PRUEBACOMUNICACION_H
#define PRUEBACOMUNICACION_H

#include <QWidget>
#include "QGCDockWidget.h"

namespace Ui {
class PruebaComunicacion;
}

class PruebaComunicacion : public QGCDockWidget
{
    Q_OBJECT

public:
    explicit PruebaComunicacion(const QString& title, QAction* action, QWidget *parent = 0);
    ~PruebaComunicacion();

private slots:
    void on_cambiarAlturaButton_clicked();

    void on_aterrizarButton_clicked();

private:
    Ui::PruebaComunicacion *ui;
};

#endif // PRUEBACOMUNICACION_H
