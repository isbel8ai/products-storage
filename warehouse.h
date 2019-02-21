#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QWidget>

namespace Ui {
class Warehouse;
}

class QSqlQueryModel;

class Warehouse : public QWidget
{
    Q_OBJECT
    
public:
    explicit Warehouse(QWidget *parent = 0);
    ~Warehouse();
    
private slots:
    void on_searchEdit_textChanged(const QString &text);

    void on_searchButton_clicked();

    void on_inputButton_clicked();

    void on_outputButton_clicked();

private:
    Ui::Warehouse *ui;
    QSqlQueryModel *wareModel;
};

#endif // WAREHOUSE_H
