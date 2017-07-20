// padthv1widget_config.h
//
/****************************************************************************
   Copyright (C) 2012-2017, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __padthv1widget_config_h
#define __padthv1widget_config_h

#include "ui_padthv1widget_config.h"

#include "padthv1_programs.h"
#include "padthv1_controls.h"
#include "padthv1_config.h"


//----------------------------------------------------------------------------
// padthv1widget_config -- UI wrapper form.

class padthv1widget_config : public QDialog
{
	Q_OBJECT

public:

	// ctor.
	padthv1widget_config(QWidget *pParent = 0, Qt::WindowFlags wflags = 0);

	// dtor.
	~padthv1widget_config();

	// controllers accessors.
	void setControls(padthv1_controls *pControls);
	padthv1_controls *controls() const;

	// programs accessors.
	void setPrograms(padthv1_programs *pPrograms);
	padthv1_programs *programs() const;

protected slots:

	// command slots.
	void controlsAddItem();
	void controlsEditItem();
	void controlsDeleteItem();

	void programsAddBankItem();
	void programsAddItem();
	void programsEditItem();
	void programsDeleteItem();

	// janitorial slots.
	void controlsCurrentChanged();
	void controlsContextMenuRequested(const QPoint&);

	void programsCurrentChanged();
	void programsActivated();
	void programsContextMenuRequested(const QPoint&);

	void controlsEnabled(bool);
	void programsEnabled(bool);

	void controlsChanged();
	void programsChanged();
	void optionsChanged();

	// dialog slots.
	void accept();
	void reject();

protected:

	// stabilizer.
	void stabilize();

private:

	// UI struct.
	Ui::padthv1widget_config m_ui;

	// Controllers database.
	padthv1_controls *m_pControls;

	// Programs database.
	padthv1_programs *m_pPrograms;

	// Dialog dirty flag.
	int m_iDirtyControls;
	int m_iDirtyPrograms;
	int m_iDirtyOptions;
};


#endif	// __padthv1widget_config_h

// end of padthv1widget_config.h
