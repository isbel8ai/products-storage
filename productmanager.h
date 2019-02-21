#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <QWidget>

namespace Ui {
class ProductManager;
}

class QSqlTableModel;

class ProductManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit ProductManager(QWidget *parent = 0);
    ~ProductManager();
    
private slots:
    void on_addButton_clicked();

    void on_updateButton_clicked();

    void on_delButton_clicked();

    void on_searchEdit_textChanged(const QString &text);

    void on_searchButton_clicked();

private:
    Ui::ProductManager *ui;
    QSqlTableModel *prodModel;
};

#endif // PRODUCTMANAGER_H
