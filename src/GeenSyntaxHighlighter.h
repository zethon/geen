#pragma once

#include <iostream>

#include <QSyntaxHighlighter>

namespace geen
{

class GeenSyntaxHighlighter : public QSyntaxHighlighter 
{

public:
    GeenSyntaxHighlighter(QTextDocument* document);
    ~GeenSyntaxHighlighter() = default;

    void highlightBlock(const QString& text) override;
};

} // namespace
