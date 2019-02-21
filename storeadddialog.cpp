#include "storeadddialog.h"
#include "ui_storeadddialog.h"

#include <QSqlRecord>

StoreAddDialog::StoreAddDialog(QSqlRecord *row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StoreAddDialog)
{
    ui->setupUi(this);
    record = row;
}

StoreAddDialog::~StoreAddDialog()
{
    delete ui;
}

void StoreAddDialog::on_acceptButton_clicked()
{
    if (ui->nameEdit->text().isEmpty()) {
        return;
    }

    record->setValue("nombre", ui->nameEdit->text());
    record->setValue("descripcion", ui->descEdit->toPlainText());

    accept();
}
