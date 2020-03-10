#include <QKeyEvent>
#include <QGuiApplication>
#include <QTextCursor>
#include <QTextBlock>
#include <QPainter>

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
    bool bok = false;

    if (auto upos = value.indexOf("_"); upos != -1)
    {
        orgval = value.left(upos);
        QString tempbase = value.right((value.size() - upos)-1);
        
        orgbase = tempbase.toInt(&bok);
        if (!bok) return "NaN";
    }

    bok = false;
    auto intval = orgval.toInt(&bok, orgbase);
    if (!bok) return "NaN"; 
    
    return QString::number(intval, base);
}

GeenTextEditor::GeenTextEditor(QWidget* parent)
    : QPlainTextEdit(parent),
    _arrow{ ":/IconResource/icons/result_arrow.png" }
{
    _arrow = _arrow.scaledToHeight(10);

    QJSValue ext = _scriptEngine.newQObject(new BaseConverter());
    _scriptEngine.globalObject().setProperty("base", ext.property("convert"));

    _lineNumberArea = new LineNumberArea(this);

    connect(this, &GeenTextEditor::blockCountChanged, this, &GeenTextEditor::updateLineNumberAreaWidth);
    connect(this, &GeenTextEditor::updateRequest, this, &GeenTextEditor::updateLineNumberArea);
    connect(this, &GeenTextEditor::cursorPositionChanged, this, &GeenTextEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void GeenTextEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(_lineNumberArea);
    painter.fillRect(event->rect(), QColor(250,250,250));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) 
    {
        if (block.isVisible() && bottom >= event->rect().top()) 
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::darkCyan);
            painter.drawText(0, top, _lineNumberArea->width() - 15, fontMetrics().height(),
                Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int GeenTextEditor::lineNumberAreaWidth()
{
    return fontMetrics().horizontalAdvance(QLatin1Char('W')) * 7;
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

    QPlainTextEdit::keyReleaseEvent(e);
}

void GeenTextEditor::resizeEvent(QResizeEvent* event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    _lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void GeenTextEditor::updateLineNumberAreaWidth(int)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void GeenTextEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) 
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(175);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void GeenTextEditor::updateLineNumberArea(const QRect& rect, int dy)
{
    if (dy)
    {
        _lineNumberArea->scroll(0, dy);
    }
    else
    {
        _lineNumberArea->update(0, rect.y(), _lineNumberArea->width(), rect.height());
    }

    if (rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth(0);
    }
}

void GeenTextEditor::processLine(const QString& line)
{
    if (line.isEmpty()) return;

    if (line.toLower() == "/quit"
        || line.toLower() == "/q")
    {
        QGuiApplication::exit();
        return;
    }

    QJSValue value = _scriptEngine.evaluate(line);

    moveCursor(QTextCursor::EndOfLine);
    auto oldformatter = currentCharFormat();

    QTextCharFormat formatter;
    formatter.setFontWeight(QFont::Normal);
    formatter.setFontItalic(true);
    formatter.setForeground(Qt::darkGray);

    //document()->firstBlock().
    //textCursor().insertBlock();
    //textCursor().block()
    //auto currentBlock = document()->findBlock(textCursor().position());

    setCurrentCharFormat(formatter);
    textCursor().insertText(" -> " + value.toString());
    textCursor().insertBlock();
    setCurrentCharFormat(oldformatter);
}

}
