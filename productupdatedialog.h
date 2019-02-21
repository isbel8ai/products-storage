#ifndef PRODUCTUPDATEDIALOG_H
#define PRODUCTUPDATEDIALOG_H

#include <QDialog>

namespace Ui {
class ProductUpdateDialog;
}

class QSqlRecord;

class ProductUpdateDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProductUpdateDialog(QSqlRecord *prod, QWidget *parent = 0);
    ~ProductUpdateDialog();
    
private slots:
    void on_acceptButton_clicked();

private:
    Ui::ProductUpdateDialog *ui;
    QSqlRecord *record;
};

#endif // PRODUCTUPDATEDIALOG_H
