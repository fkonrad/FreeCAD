/***************************************************************************
 *   Copyright (c) 2015 Balázs Bámer                                       *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef SURFACE_GUI_SURFACE_H
#define SURFACE_GUI_SURFACE_H

#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <Base/BoundBox.h>
#include <Mod/Surface/App/FillType.h>
#include <Mod/Part/Gui/ViewProvider.h>
#include <Mod/Surface/App/FeatureSurface.h>

namespace SurfaceGui
{
  
    class Ui_SurfaceFilling;

    class ViewProviderSurfaceFeature : public PartGui::ViewProviderPart
    {
        PROPERTY_HEADER(SurfaceGui::ViewProviderSurfaceFeature);
    public:
        virtual bool setEdit(int ModNum);
        virtual void unsetEdit(int ModNum);
        QIcon getIcon(void) const;
    };

    class SurfaceFilling : public QWidget
    {
        Q_OBJECT

    protected:
        FillType_t fillType, oldFillType;
        Surface::SurfaceFeature* editedObject;

    private:
        Ui_SurfaceFilling* ui;
        Base::BoundBox3d bbox;
        ViewProviderSurfaceFeature* vp;

    public:
        SurfaceFilling(ViewProviderSurfaceFeature* vp, Surface::SurfaceFeature* obj);
        ~SurfaceFilling();
        void accept();
        void reject();
        void apply();
        void setEditedObject(Surface::SurfaceFeature* obj);

    protected:
        void changeEvent(QEvent *e);

    private Q_SLOTS:
        void on_fillType_stretch_clicked();
        void on_fillType_coons_clicked();
        void on_fillType_curved_clicked();
        FillType_t getFillType() const;
    };

    class TaskSurfaceFilling : public Gui::TaskView::TaskDialog
    {
        Q_OBJECT

    public:
        TaskSurfaceFilling(ViewProviderSurfaceFeature* vp, Surface::SurfaceFeature* obj);
        ~TaskSurfaceFilling();
        void setEditedObject(Surface::SurfaceFeature* obj);

    public:
        bool accept();
        bool reject();
        void clicked(int id);

        virtual QDialogButtonBox::StandardButtons getStandardButtons() const
        { return QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel; }

    private:
        SurfaceFilling* widget;
        Gui::TaskView::TaskBox* taskbox;
        ViewProviderSurfaceFeature* view;
    };

} //namespace Surface

#endif // SURFACE_GUI_SURFACE_H