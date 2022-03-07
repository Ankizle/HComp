#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QProcess>
#include <iostream>
#include <unistd.h>
#include "SearchBar.h"
#include "openapp.h"

int main(int argc, char** argv) {
	QApplication a(argc, argv);
    QWidget mainwindow;
    mainwindow.resize(700, 300);

    QLayout* layout = new QVBoxLayout(&mainwindow);
    mainwindow.show();

    SearchBar search;
    search.parentw = &mainwindow;
    search.parentl = layout;
    search.wid = mainwindow.effectiveWinId();
    layout->addWidget(&search);

    // QProcess* p = new QProcess(layout);
    // QStringList args;
    // p->start(QString("./test/test4/a.out"), args);


    return a.exec();
}