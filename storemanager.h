#ifndef STOREMANAGER_H
#define STOREMANAGER_H

#include <QWidget>

namespace Ui {
class StoreManager;
}

class QSqlTableModel;

class StoreManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit StoreManager(QWidget *parent = 0);
    ~StoreManager();
    
private slots:
    void on_addButton_clicked();

    void on_updateButton_clicked();

    void on_delButton_clicked();

    void on_searchEdit_textChanged(const QString &text);

    void on_searchButton_clicked();

private:
    Ui::StoreManager *ui;
    QSqlTableModel *storeModel;
};

#endif // STOREMANAGER_H
