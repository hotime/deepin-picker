/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2017 Deepin, Inc.
 *               2011 ~ 2017 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QString>
#include <QDir>
#include <QApplication>
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <QWidget>
#include "utils.h"

QString Utils::getQrcPath(QString imageName)
{
    return QString(":/image/%1").arg(imageName);
}

QString Utils::getQssPath(QString qssName)
{
    return QString(":/qss/%1").arg(qssName);
}

QSize Utils::getRenderSize(int fontSize, QString string)
{
    QFont font;
    font.setPointSize(fontSize);
    QFontMetrics fm(font);

    int width = 0;
    int height = 0;
    foreach (auto line, string.split("\n")) {
        int lineWidth = fm.width(line);
        int lineHeight = fm.height();

        if (lineWidth > width) {
            width = lineWidth;
        }
        height += lineHeight;
    }

    return QSize(width, height);
}

void Utils::setFontSize(QPainter &painter, int textSize)
{
    QFont font = painter.font() ;
    font.setPointSize(textSize);
    painter.setFont(font);
}

void Utils::applyQss(QWidget *widget, QString qssName)
{
    QFile file(Utils::getQssPath(qssName));
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    widget->setStyleSheet(stylesheet);
    file.close();
}

QString Utils::colorToHex(QColor color)
{
    return QString("#%1%2%3").arg(color.red(), 2, 16, QLatin1Char('0')).arg(color.green(), 2, 16, QLatin1Char('0')).arg(color.blue(), 2, 16, QLatin1Char('0')).toUpper();
}

QString Utils::colorToRGB(QColor color)
{
    return QString("(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
}

QString Utils::colorToRGBA(QColor color)
{
    return QString("(%1, %2, %3, 1.0)").arg(color.red()).arg(color.green()).arg(color.blue());
}

QString Utils::colorToFloatRGB(QColor color)
{
    return QString("(%1, %2, %3)").arg(color.red() / 255.0).arg(color.green() / 255.0).arg(color.blue() / 255.0);
}

QString Utils::colorToFloatRGBA(QColor color)
{
    return QString("(%1, %2, %3, 1.0)").arg(color.red() / 255.0).arg(color.green() / 255.0).arg(color.blue() / 255.0);
}

bool Utils::fileExists(QString path) 
{
    QFileInfo check_file(path);
    
    // check if file exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
}

