#include <QKeyEvent>
#include <QGuiApplication>
#include <QTextCursor>

#include <QDebug>

#include "GeenTextEditor.h"

namespace geen
{

Q_INVOKABLE QString BaseConverter::convert(const QString& value)
{
    return convert(value, 10);
}

Q_INVOKABLE QString BaseConverter::convert(const QString& value, unsigned int base)
{
    QString orgval = value;
    std::uint16_t orgbase = 10;

    if (auto upos = value.indexOf("_"); upos != -1)
    {
        orgval = value.left(upos);
        QString tempbase = value.right((value.size() - upos)-1);
        
        bool bok = false;
        orgbase = tempbase.toInt(&bok);
        if (!bok) return "NaN";
    }

    bool bok = false;
    auto intval = orgval.toInt(&bok, orgbase);
    if (!bok) return "NaN"; 
    
    return QString::number(intval, base);
}

GeenTextEditor::GeenTextEditor(QWidget* parent)
    : QTextEdit(parent),
    _arrow{ ":/IconResource/icons/result_arrow.png" }
{
    _arrow = _arrow.scaledToHeight(10);

    QJSValue ext = _scriptEngine.newQObject(new BaseConverter());
    _scriptEngine.globalObject().setProperty("base", ext.property("convert"));
}

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

    QJSValue value = _scriptEngine.evaluate(line);

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
