#include "productupdatedialog.h"
#include "ui_productupdatedialog.h"

#include <QSqlRecord>

ProductUpdateDialog::ProductUpdateDialog(QSqlRecord *prod, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductUpdateDialog)
{
    ui->setupUi(this);
    record = prod;
    ui->nameEdit->setText(record->value(1).toString());
    ui->codeEdit->setText(record->value(2).toString());
    ui->descEdit->setPlainText(record->value(3).toString());
}

ProductUpdateDialog::~ProductUpdateDialog()
{
    delete ui;
}

void ProductUpdateDialog::on_acceptButton_clicked()
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
