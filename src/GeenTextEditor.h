#pragma once

#include <QPlainTextEdit>
#include <QJSEngine>

namespace geen
{

class BaseConverter : public QObject
{
    Q_OBJECT

public:
    BaseConverter(QObject* parent = nullptr) : QObject(parent) {};

    Q_INVOKABLE QString convert(const QString& value);
    Q_INVOKABLE QString convert(const QString& value, unsigned int base);
};

class GeenTextEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit GeenTextEditor(QWidget* parent);

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

protected:
    void keyReleaseEvent(QKeyEvent* e) override;
    void resizeEvent(QResizeEvent* event) override;

private Q_SLOTS:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);

private:
    void processLine(const QString& line);

    QJSEngine       _scriptEngine;
    QImage          _arrow;
    QWidget*        _lineNumberArea;
    QFont           _lineNumberFont;

};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(GeenTextEditor* editor) : QWidget(editor), codeEditor(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    GeenTextEditor* codeEditor;
};

} // namespace
