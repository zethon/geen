#pragma once

#include <QTextEdit>
#include <QScriptEngine>

namespace geen
{

class GeenTextEditor : public QTextEdit
{

public:
    using QTextEdit::QTextEdit;

    explicit GeenTextEditor(QWidget* parent)
        : QTextEdit(parent)
    { 
    }

protected:
    void keyReleaseEvent(QKeyEvent* e) override;

private:
    void processLine(const QString& line);

    QScriptEngine   _scriptEngine;

};

} // namespace