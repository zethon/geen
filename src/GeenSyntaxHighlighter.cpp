#include <QTextDocument>

#include "GeenSyntaxHighlighter.h"

namespace geen
{

GeenSyntaxHighlighter::GeenSyntaxHighlighter(QTextDocument* document)
    : QSyntaxHighlighter(document)
{
}

void GeenSyntaxHighlighter::highlightBlock(const QString& text)
{
    static std::vector<QChar> redSymbols = { '+', '-', '/' , '*' };

    enum { NormalState = -1, CStyleComment };

    int state = previousBlockState();
    int start = 0;

    for (int i = 0; i < text.length(); ++i)
    {

        if (state == CStyleComment)
        {
            if (text.mid(i, 2) == "*/")
            {
                state = NormalState;
                setFormat(start, i - start + 2, Qt::blue);
            }
        }
        else
        {
            if (text.mid(i, 2) == "//")
            {
                setFormat(i, text.length() - i, Qt::darkGreen);
                break;
            }
            else if (text.mid(i, 2) == "/*")
            {
                start = i;
                state = CStyleComment;
            }
            else if (text.mid(i, 1) == "("
                || text.mid(i, 1) == ")")
            {
                QTextCharFormat format;
                format.setFontWeight(QFont::Bold);
                format.setForeground(Qt::darkGreen);
                setFormat(i, 1, format);
            }
            else if (std::find(redSymbols.begin(), redSymbols.end(), text.mid(i,1)) != redSymbols.end())
            {
                QTextCharFormat format;
                format.setFontWeight(QFont::Bold);
                format.setForeground(Qt::darkRed);
                setFormat(i, 1, format);
            }


        }
    }
}

}
