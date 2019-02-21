#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TABLE_COUNT 8

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionAlmacen_triggered();

    void on_actionAlmacenTienda_triggered();

    void on_actionSalir_triggered();

    void on_actionGestionarProductos_triggered();

    void on_actionGestionarTiendas_triggered();

    void on_actionEntrada_triggered();

    void on_actionSalida_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
