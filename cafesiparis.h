#ifndef CAFESIPARIS_H
#define CAFESIPARIS_H

#include <QMainWindow>
#include <database.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CafeSiparis; }
QT_END_NAMESPACE

class CafeSiparis : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;

public:
    CafeSiparis(QWidget *parent = nullptr);
    ~CafeSiparis();
private:
    void databaseConnection();
    void add_listWidget1();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CafeSiparis *ui;
};
#endif // CAFESIPARIS_H
