#ifndef PRODUCTADDDIALOG_H
#define PRODUCTADDDIALOG_H

#include <QDialog>

namespace Ui {
class ProductAddDialog;
}

class QSqlRecord;

class ProductAddDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProductAddDialog(QSqlRecord *row, QWidget *parent = 0);
    ~ProductAddDialog();

private slots:
    void on_acceptButton_clicked();

private:
    Ui::ProductAddDialog *ui;
    QSqlRecord *record;
};

#endif // PRODUCTADDDIALOG_H
