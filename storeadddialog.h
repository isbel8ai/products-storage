#ifndef STOREADDDIALOG_H
#define STOREADDDIALOG_H

#include <QDialog>

namespace Ui {
class StoreAddDialog;
}

class QSqlRecord;

class StoreAddDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StoreAddDialog(QSqlRecord *row, QWidget *parent = 0);
    ~StoreAddDialog();
    
private slots:
    void on_acceptButton_clicked();

private:
    Ui::StoreAddDialog *ui;
    QSqlRecord *record;
};

#endif // STOREADDDIALOG_H
