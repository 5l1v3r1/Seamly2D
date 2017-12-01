/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                             *
 *                                                                         *
 ***************************************************************************
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 **************************************************************************

 ************************************************************************
 **
 **  @file   moveabstractlabel.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   13 5, 2016
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2016 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "moveabstractlabel.h"

#include <QDomElement>

#include "../vmisc/logging.h"
#include "../vmisc/vabstractapplication.h"
#include "../vwidgets/vmaingraphicsview.h"
#include "../vundocommand.h"

//---------------------------------------------------------------------------------------------------------------------
MoveAbstractLabel::MoveAbstractLabel(VAbstractPattern *doc, quint32 pointId, double x, double y,
                                     QUndoCommand *parent)
    : VUndoCommand(QDomElement(), doc, parent),
      m_oldMx(0.0),
      m_oldMy(0.0),
      m_newMx(x),
      m_newMy(y),
      m_isRedo(false),
      m_scene(qApp->getCurrentScene())
{
    nodeId = pointId;
    qCDebug(vUndo, "Point id %u", nodeId);

    qCDebug(vUndo, "Label new Mx %f", m_newMx);
    qCDebug(vUndo, "Label new My %f", m_newMy);
}

//---------------------------------------------------------------------------------------------------------------------
MoveAbstractLabel::~MoveAbstractLabel()
{
}

//---------------------------------------------------------------------------------------------------------------------
void MoveAbstractLabel::undo()
{
    qCDebug(vUndo, "Undo.");

    Do(m_oldMx, m_oldMy);
    VMainGraphicsView::NewSceneRect(m_scene, qApp->getSceneView());
    m_isRedo = true;
    emit ChangePosition(nodeId, m_oldMx, m_oldMy);
}

//---------------------------------------------------------------------------------------------------------------------
void MoveAbstractLabel::redo()
{
    qCDebug(vUndo, "Redo.");

    Do(m_newMx, m_newMy);
    VMainGraphicsView::NewSceneRect(m_scene, qApp->getSceneView());
    if (m_isRedo)
    {
        emit ChangePosition(nodeId, m_newMx, m_newMy);
    }
}
