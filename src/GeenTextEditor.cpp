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
    if (line.isEmpty()) return;

    QScriptValue value = _scriptEngine.evaluate(line);

    moveCursor(QTextCursor::EndOfLine);
    auto oldformatter = currentCharFormat();

    QTextCharFormat formatter;
    formatter.setFontWeight(QFont::Bold);
    formatter.setFontItalic(true);
    formatter.setForeground(Qt::lightGray);

    setCurrentCharFormat(formatter);

    textCursor().insertText(" ");
    textCursor().insertImage(_arrow);
    textCursor().insertText(" " + value.toString() + "\n");
    
    setCurrentCharFormat(oldformatter);
}

}
