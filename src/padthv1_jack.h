// padthv1_jack.h
//
/****************************************************************************
   Copyright (C) 2012-2018, rncbc aka Rui Nuno Capela. All rights reserved.

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

#ifndef __padthv1_jack_h
#define __padthv1_jack_h

#include "padthv1.h"

#include <jack/jack.h>


#ifdef CONFIG_ALSA_MIDI
#include <jack/ringbuffer.h>
#include <alsa/asoundlib.h>
// forward decls.
class padthv1_alsa_thread;
#endif


//-------------------------------------------------------------------------
// padthv1_jack - decl.
//

class padthv1_jack : public padthv1
{
public:

	padthv1_jack();

	~padthv1_jack();

	jack_client_t *client() const;

	void open(const char *client_id);
	void close();

	void activate();
	void deactivate();

	int process(jack_nframes_t nframes);

#ifdef CONFIG_ALSA_MIDI
	snd_seq_t *alsa_seq() const;
	void alsa_capture(snd_seq_event_t *ev);
#endif

#ifdef CONFIG_JACK_SESSION
	// JACK session event handler.
	void sessionEvent(void *pvSessionArg);
#endif

protected:

	void updatePreset(bool bDirty);

private:

	jack_client_t *m_client;

	volatile bool m_activated;

	jack_port_t **m_audio_ins;
	jack_port_t **m_audio_outs;

	float **m_ins;
	float **m_outs;

	float m_params[padthv1::NUM_PARAMS];

#ifdef CONFIG_JACK_MIDI
	jack_port_t *m_midi_in;
#endif
#ifdef CONFIG_ALSA_MIDI
	snd_seq_t *m_alsa_seq;
//	int m_alsa_client;
	int m_alsa_port;
	snd_midi_event_t *m_alsa_decoder;
	jack_ringbuffer_t *m_alsa_buffer;
	padthv1_alsa_thread *m_alsa_thread;
#endif
};


//-------------------------------------------------------------------------
// padthv1_jack_application -- Singleton application instance.
//

#include <QObject>
#include <QStringList>


// forward decls.
class QCoreApplication;
class padthv1widget_jack;

#ifdef CONFIG_NSM
class padthv1_nsm;
#endif

#ifdef HAVE_SIGNAL_H
class QSocketNotifier;
#endif

class padthv1_jack_application : public QObject
{
	Q_OBJECT

public:

	// Constructor.
	padthv1_jack_application(int& argc, char **argv);

	// Destructor.
	~padthv1_jack_application();

	// Facade method.
	int exec();

#ifdef CONFIG_NSM

protected slots:

	// NSM callback slots.
	void openSession();
	void saveSession();

	void hideSession();
	void showSession();

#endif	// CONFIG_NSM

#ifdef HAVE_SIGNAL_H
	// SIGTERM signal handler.
	void sigterm_handler();
#endif

protected:

	// Argument parser method.
	bool parse_args();

	// Startup method.
	bool setup();

private:

	// Instance variables.
	QCoreApplication *m_pApp;
	bool m_bGui;
	QStringList m_presets;

	padthv1_jack *m_pSynth;
	padthv1widget_jack *m_pWidget;

#ifdef CONFIG_NSM
	padthv1_nsm *m_pNsmClient;
#endif

#ifdef HAVE_SIGNAL_H
	QSocketNotifier *m_pSigtermNotifier;
#endif
};


#endif// __padthv1_jack_h

// end of padthv1_jack.h

