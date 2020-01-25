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
        : QTextEdit(parent),
          _arrow{ ":/IconResource/icons/result_arrow.png" }
    {
        _arrow = _arrow.scaledToHeight(10);
    }

protected:
    void keyReleaseEvent(QKeyEvent* e) override;

private:
    void processLine(const QString& line);

    QScriptEngine   _scriptEngine;
    QImage          _arrow;

};

} // namespace