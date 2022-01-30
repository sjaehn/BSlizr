/* B.Slizr
 * Step Sequencer Effect Plugin
 *
 * Copyright (C) 2018, 2019 by Sven Jähnichen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef BSLIZR_H_
#define BSLIZR_H_

#define MODFL(x) (x - floorf (x))

#include <cmath>
#include <array>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include "main.h"
#include "Message.hpp"

typedef struct
{
	int count;
	bool ready;
	double inputMin;
	double inputMax;
	double outputMin;
	double outputMax;
} BSlizrMonitor_t;

const BSlizrMonitor_t defaultMonitorData = {0, false, 0.0, 0.0, 0.0, 0.0};

class BSlizr
{
public:
	BSlizr (double samplerate, const LV2_Feature* const* features);
	~BSlizr();

	void connect_port (uint32_t port, void *data);
	void run (uint32_t n_samples);

	LV2_URID_Map* map;

private:
	double rate;
	float bpm;
	float speed;
	float position;
	float beatsPerBar;
	uint32_t beatUnit;
	uint32_t refFrame;
	float* prevStep;
	float* actStep;
	float* nextStep;
	float pos;

	// Audio buffers
	float* audioInput1;
	float* audioInput2;
	float* audioOutput1;
	float* audioOutput2;

	// Controllers
	float* controllers[NrControllers];
	float sequencesperbar;
	float nrSteps;
	float attack;
	float release;
	float step[MAXSTEPS];

	// Atom port
	BSlizrURIs uris;

	LV2_Atom_Sequence* controlPort1;
	LV2_Atom_Sequence* controlPort2;
	LV2_Atom_Sequence* notifyPort;

	LV2_Atom_Forge forge;
	LV2_Atom_Forge_Frame notify_frame;

	bool record_on;
	int monitorpos;
	Message message;
	std::array<BSlizrNotifications, NOTIFYBUFFERSIZE> notifications;
	std::array<BSlizrMonitor_t, MONITORBUFFERSIZE> monitor;

	void play(uint32_t start, uint32_t end);
	void notifyGUI();
	void notifyMessageToGui ();

};

#endif /* BSLIZR_H_ */
