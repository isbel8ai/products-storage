#include "outputdialog.h"
#include "ui_outputdialog.h"

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>

OutputDialog::OutputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutputDialog)
{
    ui->setupUi(this);

    storeModel = new QSqlTableModel();
    storeModel->setTable("tienda");
    storeModel->select();
    ui->storeBox->setModel(storeModel);
    ui->storeBox->setModelColumn(1);
    ui->storeBox->setCurrentIndex(-1);

    wareModel = new QSqlQueryModel;
    on_searchEdit_textChanged("");
    wareModel->setHeaderData(1, Qt::Horizontal,"Producto");
    wareModel->setHeaderData(2, Qt::Horizontal,"Código");
    wareModel->setHeaderData(3, Qt::Horizontal,"Costo");    
    wareModel->setHeaderData(4, Qt::Horizontal,"Existencia");

    ui->tableView->setModel(wareModel);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView->hideColumn(0);
}

OutputDialog::~OutputDialog()
{
    delete wareModel;
    delete storeModel;
    delete ui;
}

void OutputDialog::on_searchEdit_textChanged(const QString &text)
{
    wareModel->setQuery(QString("SELECT deposito.id, producto.nombre, producto.codigo, "
            "deposito.costo, deposito.existencia "
            "FROM deposito INNER JOIN producto ON producto.id = deposito.productoid "
            "WHERE producto.nombre LIKE '%%1%' ORDER BY producto.nombre").arg(text));

    if (text.isEmpty()) {
        ui->searchButton->setEnabled(false);
        ui->searchButton->setIcon(QIcon(":/icons/search_48.png"));
    } else {
        ui->searchButton->setEnabled(true);
        ui->searchButton->setIcon(QIcon(":/icons/cross_48.png"));
    }
}

void OutputDialog::on_searchButton_clicked()
{
    ui->searchEdit->clear();
}

void OutputDialog::on_priceBox_editingFinished()
{
    edited = (ui->priceBox->value() > 0);
}

void OutputDialog::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();

    if (!edited && row >= 0) {

        QSqlQuery query;
        query.prepare("SELECT lote.precio FROM lote "
                "WHERE lote.depositoid = ? ORDER BY lote.id DESC "
                "LIMIT 1");
        query.addBindValue(wareModel->record(row).value("id"));
        query.exec();

        if (query.next()) {
            ui->priceBox->setValue(query.value(0).toDouble());
        } else {
            ui->priceBox->setValue(0);
        }

        int amount = wareModel->record(row).value("existencia").toInt();
        ui->amountBox->setMaximum(amount);
    }
}

void OutputDialog::on_acceptButton_clicked()
{
    int stidx = ui->storeBox->currentIndex();

    if (stidx < 0) {
        return;
    }

    int row = ui->tableView->currentIndex().row();

    if (row < 0) {
        return;
    }

    int amount = ui->amountBox->value();

    QString depId = wareModel->record(row).value("id").toString();
    QSqlTableModel depModel;
    depModel.setTable("deposito");
    depModel.setFilter(QString("deposito.id = %1").arg(depId));
    depModel.select();

    QSqlRecord  depRecord = depModel.record(0);

    int downcount = depRecord.value("existencia").toInt() - amount;
    if (downcount < 0) {
        return;
    }
    depRecord.setValue("existencia", downcount);
    depModel.setRecord(0,depRecord);

    QString stId = storeModel->record(stidx).value("id").toString();
    QString price = QString::number(ui->priceBox->value());
    QSqlTableModel lotModel;
    lotModel.setTable("lote");
    lotModel.setFilter(QString("lote.depositoid = %1 AND lote.tiendaid = %2 "
            "AND lote.precio = %3").arg(depId, stId, price));
    lotModel.select();
    QSqlRecord lotRecord;

    if (lotModel.rowCount() > 0) {
        int upcount = lotModel.record(0).value("existencia").toInt() + amount;
        lotRecord = lotModel.record(0);
        lotRecord.setValue("existencia", upcount);
        lotModel.setRecord(0, lotRecord);
    } else {
        lotRecord = lotModel.record();
        lotRecord.setValue("precio", price);
        lotRecord.setValue("existencia", amount);
        lotRecord.setValue("tiendaid", stId);
        lotRecord.setValue("depositoid", depId);
        lotModel.insertRecord(-1, lotRecord);
    }


    int lotId = lotModel.record(0).value("id").toInt();
    QSqlTableModel outModel;
    outModel.setTable("salida");
    QSqlRecord outRecord = outModel.record();
    outRecord.setValue("fecha", QDateTime::currentDateTime());
    outRecord.setValue("cantidad", amount);
    outRecord.setValue("depositoid", depId);
    outRecord.setValue("loteid", lotId);
    outModel.insertRecord(-1, outRecord);

    lotModel.submitAll();
    depModel.submitAll();
    outModel.submitAll();

    accept();
}
