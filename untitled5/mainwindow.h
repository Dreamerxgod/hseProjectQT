#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QToolBar>
#include <QString>
#include <QHeaderView>
#include <map>
#include "customtablewidgetitem.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addPlayer();
    void deletePlayer();
    void uploadDataset();
    void openDataAnalysis();  

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *uploadButton;
    QPushButton *dataAnalysisButton;
    QToolBar *toolBar;

    void readCSV(const QString &filename);
    void writeCSV(const QString &filename);
    void sortData(int column); 
};

struct player
{
    QString name;
    int sal;
    QString pos;
    int age;
    QString team;
    int gp;
    int gs;
    double mg;
    double fg;
    double fga;
    double threeP;
    double threePA;
    double twoP;
    double twoPA;
    double orb;
    double drb;
    double ast;
    double stl;
    double blk;
    double pf;
    double pts;
    int tm;
    double per;
};

#endif // MAINWINDOW_H
