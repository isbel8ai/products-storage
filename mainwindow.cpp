#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "warehouse.h"
#include "storehouse.h"
#include "productmanager.h"
#include "storemanager.h"
#include "inputdialog.h"
#include "outputdialog.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase::addDatabase("QSQLITE").setDatabaseName("almacen.sqlite");
    QSqlDatabase::database().open();

    if (QSqlDatabase::database().tables().size() != TABLE_COUNT) {
        QFile scriptFile(":/sql/almacen.sql");
        scriptFile.open(QIODevice::ReadOnly);
        QStringList tables = QTextStream(&scriptFile).readAll().split(';',
                QString::SkipEmptyParts);
        QSqlQuery query;
        foreach (QString tableQry, tables) {
            if (!tableQry.trimmed().isEmpty()) {
                if (!query.exec(tableQry)) {
                    QMessageBox::critical(this, "Error de base de datos",
                            query.lastError().text());
                    return;
                }
                query.finish();
            }
        }
    }

    setCentralWidget(new Warehouse(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAlmacen_triggered()
{
    setCentralWidget(new Warehouse(this));
}

void MainWindow::on_actionAlmacenTienda_triggered()
{
    setCentralWidget(new StoreHouse(this));
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionGestionarProductos_triggered()
{
    setCentralWidget(new ProductManager(this));
}

void MainWindow::on_actionGestionarTiendas_triggered()
{
    setCentralWidget(new StoreManager(this));
}

void MainWindow::on_actionEntrada_triggered()
{
    InputDialog input(this);
    input.exec();
}

void MainWindow::on_actionSalida_triggered()
{
    OutputDialog output(this);
    output.exec();
}
