#include "productadddialog.h"
#include "ui_productadddialog.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>

ProductAddDialog::ProductAddDialog(QSqlRecord *row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductAddDialog)
{
    ui->setupUi(this);
    record = row;
}

ProductAddDialog::~ProductAddDialog()
{
    delete ui;
}

void ProductAddDialog::on_acceptButton_clicked()
{
    if (ui->nameEdit->text().isEmpty()) {
        return;
    }

    if (ui->codeEdit->text().isEmpty()) {
        return;
    }

    record->setValue("nombre", ui->nameEdit->text());
    record->setValue("codigo", ui->codeEdit->text());
    record->setValue("descripcion", ui->descEdit->toPlainText());

    accept();
}
