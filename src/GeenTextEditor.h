#pragma once

#include <QTextEdit>
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

class GeenTextEditor : public QTextEdit
{

public:
    explicit GeenTextEditor(QWidget* parent);

protected:
    void keyReleaseEvent(QKeyEvent* e) override;

private:
    void processLine(const QString& line);

    QJSEngine       _scriptEngine;
    QImage          _arrow;

};

} // namespace