#include "inputdialog.h"
#include "ui_inputdialog.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDateTime>

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    prodModel = new QSqlTableModel();
    prodModel->setTable("producto");
    prodModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    prodModel->setHeaderData(1, Qt::Horizontal, "Producto");
    prodModel->setHeaderData(2, Qt::Horizontal, "Código");
    prodModel->setSort(1, Qt::AscendingOrder);
    prodModel->select();
    ui->tableView->setModel(prodModel);
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

InputDialog::~InputDialog()
{    
    delete prodModel;
    delete ui;
}

void InputDialog::on_searchEdit_textChanged(const QString &text)
{
     prodModel->setFilter(QString("producto.nombre LIKE '%%1%'").arg(text));

     if (text.isEmpty()) {
        ui->searchButton->setEnabled(false);
        ui->searchButton->setIcon(QIcon(":/icons/search_48.png"));
    } else {
        ui->searchButton->setEnabled(true);
        ui->searchButton->setIcon(QIcon(":/icons/cross_48.png"));
    }
}

void InputDialog::on_searchButton_clicked()
{
    prodModel->setFilter("");
    ui->searchEdit->clear();
    ui->searchButton->setEnabled(false);
}

void InputDialog::on_costBox_editingFinished()
{
    edited = (ui->costBox->value() > 0);
}

void InputDialog::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();

    if (!edited && row >= 0) {

        QSqlQuery query;
        query.prepare("SELECT deposito.costo FROM deposito "
                "WHERE deposito.productoid = ? ORDER BY deposito.id DESC "
                "LIMIT 1");
        query.addBindValue(prodModel->record(row).value("id"));
        query.exec();

        if (query.next()) {
            ui->costBox->setValue(query.value(0).toDouble());
        } else {
            ui->costBox->setValue(0);
        }
    }
}

void InputDialog::on_acceptButton_clicked()
{
    int row = ui->tableView->currentIndex().row();

    if (row < 0) {
        return;
    }

    QString prodId = prodModel->record(row).value("id").toString();
    QString cost = QString::number(ui->costBox->value());
    QSqlTableModel depModel;
    depModel.setTable("deposito");
    depModel.setFilter(QString("deposito.productoid = %1 "
            "AND deposito.costo = %2 ").arg(prodId, cost));
    depModel.select();

    int amount = ui->amountBox->value();
    QSqlRecord record;

    if (depModel.rowCount() > 0) {
        int upcount = depModel.record(0).value("existencia").toInt() + amount;
        record = depModel.record(0);
        record.setValue("existencia", upcount);
        depModel.setRecord(0, record);
    } else {
        record = depModel.record();
        record.setValue("costo", cost);
        record.setValue("productoid", prodId);
        record.setValue("existencia", amount);
        depModel.insertRecord(-1, record);
    }

    int depId = depModel.record(0).value("id").toInt();
    QSqlTableModel inpModel;
    inpModel.setTable("entrada");
    QSqlRecord inpRecord = inpModel.record();
    inpRecord.setValue("fecha", QDateTime::currentDateTime());
    inpRecord.setValue("cantidad", amount);
    inpRecord.setValue("depositoid", depId);
    inpModel.insertRecord(-1, inpRecord);

    depModel.submitAll();
    inpModel.submitAll();

    accept();
}
