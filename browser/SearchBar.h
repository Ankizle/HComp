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
#include "openapp.h"
#include "spawntab.h"

class SearchBar : public QLineEdit {
    public:
        QWidget* parentw;
        QLayout* parentl;
        unsigned long long wid;

        SearchBar() : QLineEdit() {
            this->setPlaceholderText("Search...");
        }

        void keyPressEvent(QKeyEvent* e) override {
            if (e->key() == Qt::Key_Return) {
                char* a = (char*)calloc(1000, sizeof(char));
                printf("%d\n", wid);
                // sprintf(a, "Xephyr :1", wid);
                // system(a);
            } else if (e->key() == Qt::Key_Backspace) this->backspace();
            else this->setText(this->text() + e->text());
        }
};

#endif