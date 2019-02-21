#include "storemanager.h"
#include "ui_storemanager.h"

#include "storeadddialog.h"
#include "storeupdatedialog.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

StoreManager::StoreManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreManager)
{
    ui->setupUi(this);
    storeModel = new QSqlTableModel();
    storeModel->setTable("tienda");
    storeModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    storeModel->setHeaderData(1, Qt::Horizontal, "Nombre");
    storeModel->setHeaderData(2, Qt::Horizontal, "Descripción");
    storeModel->select();
    ui->tableView->setModel(storeModel);
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

}

StoreManager::~StoreManager()
{
    delete storeModel;
    delete ui;
}

void StoreManager::on_addButton_clicked()
{
    QSqlRecord record = storeModel->record();
    StoreAddDialog addDiag(&record);
    if (addDiag.exec() == QDialog::Accepted) {
        storeModel->insertRecord(-1, record);
        storeModel->submitAll();
    }
}

void StoreManager::on_updateButton_clicked()
{
    int row = ui->tableView->currentIndex().row();

    if (row < 0) {
        return;
    }

    QSqlRecord record = storeModel->record(row);
    StoreUpdateDialog updateDiag(&record);
    if (updateDiag.exec() == QDialog::Accepted) {
        storeModel->setRecord(row, record);
        storeModel->submitAll();
    }
}

void StoreManager::on_delButton_clicked()
{
    int row = ui->tableView->currentIndex().row();

    if (row < 0) {
        return;
    }

    int ret = QMessageBox::question(this, "Confirmación de borrado",
            "¿Seguro desea eliminar la tienda selecionada?",
            QMessageBox::Ok | QMessageBox::Cancel);

    if (ret == QMessageBox::Ok) {
        storeModel->removeRow(row);
        storeModel->submitAll();
    }
}

void StoreManager::on_searchEdit_textChanged(const QString &text)
{
    storeModel->setFilter(QString("tienda.nombre LIKE '%%1%'").arg(text));

    if (text.isEmpty()) {
        ui->searchButton->setEnabled(false);
        ui->searchButton->setIcon(QIcon(":/icons/search_48.png"));
    } else {
        ui->searchButton->setEnabled(true);
        ui->searchButton->setIcon(QIcon(":/icons/cross_48.png"));
    }
}

void StoreManager::on_searchButton_clicked()
{
    storeModel->setFilter("");
    ui->searchEdit->clear();
    ui->searchButton->setEnabled(false);
}
