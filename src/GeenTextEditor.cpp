#include <QKeyEvent>
#include <QGuiApplication>
#include <QTextCursor>

#include <QDebug>

#include "GeenTextEditor.h"

namespace geen
{

void GeenTextEditor::keyReleaseEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Enter
        || e->key() == Qt::Key_Return)
    {
        auto keyboardState = QGuiApplication::keyboardModifiers();
        if (keyboardState & Qt::ControlModifier
            && keyboardState & Qt::ShiftModifier)
        {
            QTextCursor cursor{ textCursor() };
            cursor.select(QTextCursor::LineUnderCursor);
            processLine(cursor.selectedText());
        }
    }

    QTextEdit::keyReleaseEvent(e);
}

void GeenTextEditor::processLine(const QString& line)
{
    QScriptValue value = _scriptEngine.evaluate(line);
    qDebug() << "result: " << value.toString();

    this->moveCursor(QTextCursor::EndOfLine);
    this->textCursor().insertText("->" + value.toString());
}

}
