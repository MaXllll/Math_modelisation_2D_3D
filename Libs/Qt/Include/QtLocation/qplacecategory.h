/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLACECATEGORY_H
#define QPLACECATEGORY_H

#include <QtLocation/qlocationglobal.h>

#include <QtCore/QSharedDataPointer>
#include <QtCore/QString>
#include <QtCore/QMetaType>
#include <QtLocation/QLocation>

QT_BEGIN_NAMESPACE

class QPlaceIcon;

class QPlaceCategoryPrivate;
class Q_LOCATION_EXPORT QPlaceCategory
{
public:
    QPlaceCategory();
    QPlaceCategory(const QPlaceCategory &other);

    virtual ~QPlaceCategory();

    QPlaceCategory &operator=(const QPlaceCategory &other);

    bool operator==(const QPlaceCategory &other) const;
    bool operator!=(const QPlaceCategory &other) const {
        return !(other == *this);
    }

    QString categoryId() const;
    void setCategoryId(const QString &identifier);

    QString name() const;
    void setName(const QString &name);

    QLocation::Visibility visibility() const;
    void setVisibility(QLocation::Visibility visibility);

    QPlaceIcon icon() const;
    void setIcon(const QPlaceIcon &icon);

    bool isEmpty() const;

private:
    QSharedDataPointer<QPlaceCategoryPrivate> d;
};

Q_DECLARE_TYPEINFO(QPlaceCategory, Q_MOVABLE_TYPE);

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QPlaceCategory)

#endif // QPLACECATEGORY_H
