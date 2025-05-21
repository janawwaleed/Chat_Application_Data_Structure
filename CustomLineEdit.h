#pragma once
#pragma once

#include <QLineEdit>
#include <QFocusEvent>
#include <iostream>

class CustomLineEdit : public QLineEdit {
    Q_OBJECT

public:
    CustomLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) {}

    void focusInEvent(QFocusEvent* e) override {
        QLineEdit::focusInEvent(e);
        setPlaceholderText("");
    }

    void focusOutEvent(QFocusEvent* e) override {
        QLineEdit::focusOutEvent(e);
        if (text().isEmpty()) {
            setPlaceholderText("Enter your Number");
        }
    }
};
