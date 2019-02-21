#include "storeupdatedialog.h"
#include "ui_storeupdatedialog.h"

#include <QSqlRecord>

StoreUpdateDialog::StoreUpdateDialog(QSqlRecord *row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StoreUpdateDialog)
{
    ui->setupUi(this);
    record = row;
    ui->nameEdit->setText(record->value(1).toString());
    ui->descEdit->setPlainText(record->value(2).toString());
}

StoreUpdateDialog::~StoreUpdateDialog()
{
    delete ui;
}

void StoreUpdateDialog::on_acceptButton_clicked()
{
    if (ui->nameEdit->text().isEmpty()) {
        return;
    }

    record->setValue("nombre", ui->nameEdit->text());
    record->setValue("descripcion", ui->descEdit->toPlainText());

    accept();
}
