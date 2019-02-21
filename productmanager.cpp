#include "productmanager.h"
#include "ui_productmanager.h"

#include "productadddialog.h"
#include "productupdatedialog.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

ProductManager::ProductManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManager)
{
    ui->setupUi(this);
    prodModel = new QSqlTableModel();
    prodModel->setTable("producto");
    prodModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    prodModel->setHeaderData(1, Qt::Horizontal, "Producto");
    prodModel->setHeaderData(2, Qt::Horizontal, "Código");
    prodModel->setHeaderData(3, Qt::Horizontal, "Descripción");
    prodModel->select();
    ui->tableView->setModel(prodModel);
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

ProductManager::~ProductManager()
{    
    delete prodModel;
    delete ui;
}

void ProductManager::on_addButton_clicked()
{
    QSqlRecord record = prodModel->record();
    ProductAddDialog addDiag(&record);
    if (addDiag.exec() == QDialog::Accepted) {
        prodModel->insertRecord(-1, record);
        prodModel->submitAll();
    }
}

void ProductManager::on_updateButton_clicked()
{
    int row = ui->tableView->currentIndex().row();

    if (row < 0) {
        return;
    }

    QSqlRecord record = prodModel->record(row);
    ProductUpdateDialog updateDiag(&record);
    if (updateDiag.exec() == QDialog::Accepted) {
        prodModel->setRecord(row, record);
        prodModel->submitAll();
    }
}

void ProductManager::on_delButton_clicked()
{
    int row = ui->tableView->currentIndex().row();

    if (row < 0) {
        return;
    }

    int resp = QMessageBox::question(this, "Eliminar producto",
            "¿Seguro desea eliminar el producto seleccionado?",
             QMessageBox::Ok | QMessageBox::Cancel);

    if (resp == QMessageBox::Ok) {
        prodModel->removeRow(row);
        prodModel->submitAll();
    }
}

void ProductManager::on_searchEdit_textChanged(const QString &text)
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

void ProductManager::on_searchButton_clicked()
{
    prodModel->setFilter("");
    ui->searchEdit->clear();
    ui->searchButton->setEnabled(false);
}
