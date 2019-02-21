#ifndef OUTPUTDIALOG_H
#define OUTPUTDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class OutputDialog;
}

class QSqlQueryModel;
class QSqlTableModel;

class OutputDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OutputDialog(QWidget *parent = 0);
    ~OutputDialog();
    
private slots:
    void on_searchEdit_textChanged(const QString &text);

    void on_searchButton_clicked();

    void on_priceBox_editingFinished();

    void on_tableView_clicked(const QModelIndex &index);

    void on_acceptButton_clicked();

private:
    Ui::OutputDialog *ui;
    QSqlQueryModel *wareModel;    
    QSqlTableModel *storeModel;
    bool edited;
};

#endif // OUTPUTDIALOG_H
