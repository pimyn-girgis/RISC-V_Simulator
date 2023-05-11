/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "highlighter.h"

//! [0]
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    QColor instructionColor("#FF8811");
    keywordFormat.setForeground(instructionColor);
    keywordFormat.setFontWeight(QFont::Bold);
    /// AW: instruction highlighting
    const QString keywordPatterns[] = {
        QStringLiteral("\\badd\\b"), QStringLiteral("\\bbgeu\\b"), QStringLiteral("\\bslti\\b"),
        QStringLiteral("\\blui\\b"), QStringLiteral("\\blb\\b"), QStringLiteral("\\bsltiu\\b"),
        QStringLiteral("\\bauipc\\b"), QStringLiteral("\\blh\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\bjal\\b"), QStringLiteral("\\blw\\b"), QStringLiteral("\\bxori\\b"),
        QStringLiteral("\\bjalr\\b"), QStringLiteral("\\blbu\\b"), QStringLiteral("\\bori\\b"),
        QStringLiteral("\\bbeq\\b"), QStringLiteral("\\blhu\\b"), QStringLiteral("\\bslli\\b"),
        QStringLiteral("\\bbne\\b"), QStringLiteral("\\bsb\\b"), QStringLiteral("\\bsrli\\b"),
        QStringLiteral("\\bblt\\b"), QStringLiteral("\\bsh\\b"), QStringLiteral("\\bsrai\\b"),
        QStringLiteral("\\bbge\\b"), QStringLiteral("\\bsw\\b"), QStringLiteral("\\bsub\\b"),
        QStringLiteral("\\bbltu\\b"), QStringLiteral("\\baddi\\b"), QStringLiteral("\\bsll\\b"),
        QStringLiteral("\\bslt\\b"), QStringLiteral("\\bsltu\\b"), QStringLiteral("\\bxor\\b"),
        QStringLiteral("\\bsrl\\b"), QStringLiteral("\\bsra\\b"), QStringLiteral("\\bor\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bfence\\b"), QStringLiteral("\\becall\\b"),
        QStringLiteral("\\bebreak\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
//! [0] //! [1]
    }

    QColor registerColor("#F4D06F");
    registerFormat.setForeground(registerColor);
    /// AW: register highlighting
    const QString regKeywordPatterns[] = {
        QStringLiteral("\\bx1\\b"), QStringLiteral("\\bx2\\b"), QStringLiteral("\\bx3\\b"),
        QStringLiteral("\\bx4\\b"), QStringLiteral("\\bx5\\b"), QStringLiteral("\\bx6\\b"),
        QStringLiteral("\\bx9\\b"), QStringLiteral("\\bx8\\b"), QStringLiteral("\\bx7\\b"),
        QStringLiteral("\\bx10\\b"), QStringLiteral("\\bx11\\b"), QStringLiteral("\\bx12\\b"),
        QStringLiteral("\\bx15\\b"), QStringLiteral("\\bx14\\b"), QStringLiteral("\\bx13\\b"),
        QStringLiteral("\\bx16\\b"), QStringLiteral("\\bx17\\b"), QStringLiteral("\\bx18\\b"),
        QStringLiteral("\\bx21\\b"), QStringLiteral("\\bx20\\b"), QStringLiteral("\\bx19\\b"),
        QStringLiteral("\\bx22\\b"), QStringLiteral("\\bx23\\b"), QStringLiteral("\\bx24\\b"),
        QStringLiteral("\\bx27\\b"), QStringLiteral("\\bx26\\b"), QStringLiteral("\\bx25\\b"),
        QStringLiteral("\\bx28\\b"), QStringLiteral("\\bx29\\b"), QStringLiteral("\\bx30\\b"),
        QStringLiteral("\\bpc\\b"), QStringLiteral("\\bx32\\b"), QStringLiteral("\\bx31\\b"),
        QStringLiteral("\\bzero\\b"), QStringLiteral("\\btp\\b"), QStringLiteral("\\bgp\\b"),
        QStringLiteral("\\bsp\\b"), QStringLiteral("\\bra\\b"), QStringLiteral("\\bt0\\b"),
        QStringLiteral("\\bs0\\b"), QStringLiteral("\\bx0\\b"), QStringLiteral("\\bt1\\b"),
        QStringLiteral("\\bs1\\b"), QStringLiteral("\\ba0\\b"), QStringLiteral("\\bt2\\b"),
        QStringLiteral("\\bs2\\b"), QStringLiteral("\\ba1\\b"), QStringLiteral("\\bt3\\b"),
        QStringLiteral("\\bs3\\b"), QStringLiteral("\\ba2\\b"), QStringLiteral("\\bt4\\b"),
        QStringLiteral("\\bs4\\b"), QStringLiteral("\\ba3\\b"), QStringLiteral("\\bt5\\b"),
        QStringLiteral("\\bs5\\b"), QStringLiteral("\\ba4\\b"), QStringLiteral("\\bt6\\b"),
        QStringLiteral("\\bs6\\b"), QStringLiteral("\\ba5\\b"), QStringLiteral("\\ba6\\b"),
        QStringLiteral("\\bs7\\b"), QStringLiteral("\\ba7\\b"), QStringLiteral("\\ba8\\b"),
        QStringLiteral("\\bs8\\b"), QStringLiteral("\\bs9\\b"), QStringLiteral("\\bs10\\b"),
        QStringLiteral("\\bs11\\b")
    };

    for (const QString &pattern : regKeywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = registerFormat;
        highlightingRules.append(rule);
//! [0] //! [1]
    }
//! [1]

//! [2] AW: label highlighing

    functionFormat.setFontItalic(true);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\:)"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

//! [2]

//! [3] AW: comments
    QColor commentColor("#676461");
    singleLineCommentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression(QStringLiteral("#[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(commentColor);
//! [3]

//! [4] AW: string highlighting
    QColor stringColor("#BD5698");
    quotationFormat.setForeground(stringColor);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);
//! [4]

//! [5] AW: section highlighting

    QColor sectionColor("#A745C4");
    classFormat.setForeground(sectionColor);
    rule.pattern = QRegularExpression(QStringLiteral("\\.[A-Za-z0-9_]+"));
    rule.format = classFormat;
    highlightingRules.append(rule);
//! [5]

//! [6] AW: block comment highlighting, if you remove it crashes idk why man
    commentStartExpression = QRegularExpression(QStringLiteral("#\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*#"));
}
//! [6]

//! [7]
void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
//! [7] //! [8]
    setCurrentBlockState(0);
//! [8]

//! [9]
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

//! [9] //! [10]
    while (startIndex >= 0) {
//! [10] //! [11]
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
//! [11]
