#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *mwref;

LRESULT KeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam){
    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);

    switch(wParam){
    case WM_KEYDOWN:
        switch(cKey.vkCode){
        case 'C' :
            if(GetAsyncKeyState(VK_CONTROL)){
                mwref->something();
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);

    //setup
    mwref = this;
    board = QApplication::clipboard();

    // exit shortcut
    keyCtrlQ = new QShortcut(this);
    keyCtrlQ ->setKey(Qt::CTRL + Qt::Key_Q);
    connect(keyCtrlQ, SIGNAL(activated()), this, SLOT(close()));

    // keyboardhook
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyBoardProc, NULL, 0);
    if(hHook == 0) qDebug() << "Hook failed" << endl;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mpos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() && Qt::LeftButton){
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void MainWindow::something()
{
    QString tmp = board->text();
    int n = tmp.length();
    int with_space = n;
    int without_space = 0;
    for(int i = 0; i < n ; ++i){
        if(tmp[i] != ' ' && tmp[i] != '\n' && tmp[i] != '\t'){
            without_space++;
        }
    }
    ui->label_2->setText(QString::number(with_space));
    ui->label_4->setText(QString::number(without_space));
}
