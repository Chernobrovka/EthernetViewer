#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QWidget>
#include <QTextBrowser>

class TextBrowser : public QObject
{
    Q_OBJECT
public:
    explicit TextBrowser(QTextBrowser *textBrowser, QObject *parent = nullptr);

    void setText(const QString &text);
    void appendText(const QString &text);
    void clear();

private:
    QTextBrowser *m_textBrowser;
};

#endif // TEXTBROWSER_H
