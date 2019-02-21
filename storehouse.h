#ifndef STOREHOUSE_H
#define STOREHOUSE_H

#include <QWidget>

namespace Ui {
class StoreHouse;
}

class QSqlTableModel;
class QSqlQueryModel;

class StoreHouse : public QWidget
{
    Q_OBJECT
    
public:
    explicit StoreHouse(QWidget *parent = 0);
    ~StoreHouse();
    
private slots:
    void on_storeBox_currentIndexChanged(int index);

    void on_searchEdit_textChanged(const QString &filter);

private:
    Ui::StoreHouse *ui;
    QSqlTableModel *storeModel;
    QSqlQueryModel *sthoseModel;
};

#endif // STOREHOUSE_H
