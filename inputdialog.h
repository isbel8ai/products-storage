#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class InputDialog;
}

class QSqlTableModel;

class InputDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();
    
private slots:
    void on_searchEdit_textChanged(const QString &text);

    void on_searchButton_clicked();

    void on_costBox_editingFinished();

    void on_tableView_clicked(const QModelIndex &index);

    void on_acceptButton_clicked();

private:
    Ui::InputDialog *ui;
    QSqlTableModel *prodModel;
    bool edited;
};

#endif // INPUTDIALOG_H
