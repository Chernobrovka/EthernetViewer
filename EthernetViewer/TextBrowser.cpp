#include "TextBrowser.h"

TextBrowser::TextBrowser(QTextBrowser *textBrowser, QObject *parent)
    : QObject(parent), m_textBrowser(textBrowser)
{
    textBrowser->setStyleSheet("QTextBrowser {"
                  "background-color: #474545;"  // Темный фон
                  "color: #48D433;"             // Яркий цвет текста
                  "}");
}

void TextBrowser::setText(const QString &text){
    if (m_textBrowser) {
        m_textBrowser->setText(text);
    }
}

void TextBrowser::appendText(const QString &text){
    if (m_textBrowser) {
        m_textBrowser->append(text);
    }
}

void TextBrowser::clear(){
    if (m_textBrowser) {
        m_textBrowser->clear();
    }
}
