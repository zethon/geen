#pragma once

#include <QTextEdit>

namespace geen
{

class GeenTextEditor : public QTextEdit
{
    Q_OBJECT

public:
    using QTextEdit::QTextEdit;

    explicit GeenTextEditor(QWidget* parent)
        : QTextEdit(parent)
    { 
    }
};

} // namespace