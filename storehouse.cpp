#include "storehouse.h"
#include "ui_storehouse.h"

#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>

StoreHouse::StoreHouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreHouse)
{
    ui->setupUi(this);

    sthoseModel = new QSqlQueryModel;

    storeModel = new QSqlTableModel;
    storeModel->setTable("tienda");
    storeModel->select();

    ui->storeBox->setModel(storeModel);
    ui->storeBox->setModelColumn(1);
}

StoreHouse::~StoreHouse()
{
    delete ui;
}

void StoreHouse::on_storeBox_currentIndexChanged(int index)
{
    if (index >= 0) {
        QString filter = ui->searchEdit->text();
        on_searchEdit_textChanged(filter);
    }
}


void StoreHouse::on_searchEdit_textChanged(const QString &filter)
{
    int stidx = ui->storeBox->currentIndex();
    if (stidx >= 0) {
        QString stId = storeModel->record(stidx).value("id").toString();
        sthoseModel->setQuery(QString("SELECT producto.nombre, producto.codigo, "
                "deposito.costo, lote.precio, lote.existencia FROM lote "
                "INNER JOIN deposito ON lote.depositoid = deposito.id "
                "INNER JOIN producto ON deposito.productoid = producto.id "
                "WHERE lote.tiendaid = %1 AND producto.nombre LIKE '%%2%' "
                "ORDER BY producto.nombre ASC").arg(stId, filter));
        ui->tableView->setModel(sthoseModel);
        ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    }
}
