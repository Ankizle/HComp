#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <iostream>
#include <unistd.h>

#include "SearchBar.h"
#include "tab1.h"

int main(int argc, char** argv) {
	QApplication a(argc, argv);
    QWidget mainwindow;
    mainwindow.resize(700, 300);

    QLayout* layout = new QGridLayout(&mainwindow);
    mainwindow.show();

    SearchBar search;
    search.parentw = &mainwindow;
    search.parentl = layout;
    layout->addWidget(&search);

    return a.exec();
}