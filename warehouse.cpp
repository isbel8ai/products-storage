#include "warehouse.h"
#include "ui_warehouse.h"

#include "inputdialog.h"
#include "outputdialog.h"

#include <QSqlQueryModel>
#include <QSqlQuery>


Warehouse::Warehouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Warehouse)
{
    ui->setupUi(this);
    wareModel = new QSqlQueryModel();
    on_searchEdit_textChanged("");
}

Warehouse::~Warehouse()
{    
    delete wareModel;
    delete ui;
}

void Warehouse::on_searchEdit_textChanged(const QString &text)
{
    wareModel->setQuery(QString("SELECT deposito.id, producto.nombre, producto.codigo, "
            "producto.descripcion, deposito.costo, deposito.existencia "
            "FROM deposito INNER JOIN producto ON producto.id = deposito.productoid "
            "WHERE producto.nombre LIKE '%%1%' ORDER BY producto.nombre ASC").arg(text));

    wareModel->setHeaderData(1, Qt::Horizontal,"Producto");
    wareModel->setHeaderData(2, Qt::Horizontal,"Código");
    wareModel->setHeaderData(3, Qt::Horizontal,"Descripción");
    wareModel->setHeaderData(4, Qt::Horizontal,"Costo");
    wareModel->setHeaderData(5, Qt::Horizontal,"Cantidad");
    ui->tableView->setModel(wareModel);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView->hideColumn(0);

    if (text.isEmpty()) {
        ui->searchButton->setEnabled(false);
        ui->searchButton->setIcon(QIcon(":/icons/search_48.png"));
    } else {
        ui->searchButton->setEnabled(true);
        ui->searchButton->setIcon(QIcon(":/icons/cross_48.png"));
    }
}

void Warehouse::on_searchButton_clicked()
{
    ui->searchEdit->clear();
    ui->searchButton->setEnabled(false);
}

void Warehouse::on_inputButton_clicked()
{
    InputDialog input(this);
    input.exec();
}

void Warehouse::on_outputButton_clicked()
{
    OutputDialog output(this);
    output.exec();
}
