#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void raiseError();
     void fillTheTable(QString pathToFile, int choice);
private slots:
    void on_inputButton_clicked();

    void on_outputButton_clicked();

    void on_clearButton_clicked();

    void on_addButton_clicked();

    void on_listButton_clicked();

    void on_deleteButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
