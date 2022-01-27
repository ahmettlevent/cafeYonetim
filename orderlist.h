#ifndef ORDERLIST_H
#define ORDERLIST_H

#include <QDialog>
#include <database.h>

namespace Ui {
class OrderList;
}

class OrderList : public QDialog
{
    Q_OBJECT
    CafeDatabase database;

public:
    explicit OrderList(QWidget *parent = nullptr);
    ~OrderList();
    void initForm(int orderID);

private:
    int orderID;
    void databaseConnection();
    void initOrders();
    void clearLayout( QLayout* layout );
    void createOrderListLayout(QString yemekAdi,QString yemekFiyati);
private:
    Ui::OrderList *ui;
};

#endif // ORDERLIST_H
