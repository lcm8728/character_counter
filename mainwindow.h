#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QClipboard>
#include <QMainWindow>
#include <QKeyEvent>
#include <QShortcut>
#include <QDebug>

#include <Windows.h>
#pragma comment( lib, "user32.lib" )

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void something();

private:
    Ui::MainWindow *ui;
    QPoint mpos;
    QShortcut *keyCtrlQ;
    HHOOK hHook;
    QClipboard *board;
};

#endif // MAINWINDOW_H
