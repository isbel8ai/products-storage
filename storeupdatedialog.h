#ifndef STOREUPDATEDIALOG_H
#define STOREUPDATEDIALOG_H

#include <QDialog>

namespace Ui {
class StoreUpdateDialog;
}

class QSqlRecord;

class StoreUpdateDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StoreUpdateDialog(QSqlRecord *row, QWidget *parent = 0);
    ~StoreUpdateDialog();
    
private slots:
    void on_acceptButton_clicked();

private:
    Ui::StoreUpdateDialog *ui;
    QSqlRecord *record;
};

#endif // STOREUPDATEDIALOG_H
