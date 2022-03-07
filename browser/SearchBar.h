#ifndef SEARCH_BAR_H_
#define SEARCH_BAR_H_

#include <QLineEdit>
#include <QKeyEvent>
#include <QLayout>
#include <QWindow>
#include <QWidget>
#include <iostream>
#include <unistd.h>
#include <string.h>

#include "tab1.h"

class SearchBar : public QLineEdit {
    public:
        QWidget* parentw;
        QLayout* parentl;

        SearchBar() : QLineEdit() {
            this->setPlaceholderText("Search...");
        }

        void keyPressEvent(QKeyEvent* e) override {
            if (e->key() == Qt::Key_Return) {
                unsigned long long w = tab1open(parentw->winId());
            } else if (e->key() == Qt::Key_Backspace) this->backspace();
            else this->setText(this->text() + e->text());
        }
};

#endif