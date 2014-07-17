/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "cameraselectornode.h"
#include "rendercamera.h"
#include <Qt3DRenderer/qcameraselector.h>
#include <Qt3DRenderer/renderer.h>
#include <Qt3DRenderer/rendereraspect.h>
#include <Qt3DCore/qaspectmanager.h>
#include <Qt3DCore/qchangearbiter.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qscenepropertychange.h>
#include "renderlogging.h"

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

CameraSelector::CameraSelector(FrameGraphNode *parent)
    : FrameGraphNode(FrameGraphNode::CameraSelector, parent)
    , m_renderer(Q_NULLPTR)
    , m_peer(Q_NULLPTR)
{
}

void CameraSelector::setRenderer(Renderer *renderer)
{
    m_renderer = renderer;
}

void CameraSelector::setPeer(Qt3D::QCameraSelector *peer)
{
    if (m_peer != peer) {
        if (m_peer)
            m_renderer->rendererAspect()->aspectManager()->changeArbiter()->unregisterObserver(this, m_peer);
        m_peer = peer;
        m_cameraUuid = QUuid();
        if (m_peer) {
            m_renderer->rendererAspect()->aspectManager()->changeArbiter()->registerObserver(this, m_peer, ComponentUpdated);
            if (m_peer->camera())
                m_cameraUuid = m_peer->camera()->uuid();
        }
    }
}

void CameraSelector::sceneChangeEvent(const QSceneChangePtr &e)
{
    qCDebug(Render::Framegraph) << Q_FUNC_INFO;
    if (e->type() == ComponentUpdated) {
        QScenePropertyChangePtr propertyChange = qSharedPointerCast<QScenePropertyChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("camera")) {
            m_cameraUuid = propertyChange->value().toUuid();
        }
    }
}

QUuid CameraSelector::cameraUuid() const
{
    return m_cameraUuid;
}

} // Render

} // Qt3D

QT_END_NAMESPACE
