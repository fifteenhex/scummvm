/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "common/scummsys.h"

#if defined(OPENPANDORA)

#include "backends/graphics/openpandora/op-graphics.h"
#include "backends/events/openpandora/op-events.h"
#include "graphics/scaler/aspect.h"
#include "common/mutex.h"
#include "common/textconsole.h"

static SDL_Cursor *hiddenCursor;

OPGraphicsManager::OPGraphicsManager(SdlEventSource *sdlEventSource, SdlWindow *window)
	: SurfaceSdlGraphicsManager(sdlEventSource, window) {
}

bool OPGraphicsManager::loadGFXMode() {

	uint8_t hiddenCursorData = 0;
	hiddenCursor = SDL_CreateCursor(&hiddenCursorData, &hiddenCursorData, 8, 1, 0, 0);

	/* On the OpenPandora we need to work around an SDL assumption that
	   returns relative mouse coordinates when you get to the screen
	   edges using the touchscreen. The workaround is to set a blank
	   SDL cursor and not disable it (Hackish I know).

	   The root issues likes in the Windows Manager GRAB code in SDL.
	   That is why the issue is not seen on framebuffer devices like the
	   GP2X (there is no X window manager ;)).
	*/
	SDL_ShowCursor(SDL_ENABLE);
	SDL_SetCursor(hiddenCursor);

	return SurfaceSdlGraphicsManager::loadGFXMode();
}

void OPGraphicsManager::unloadGFXMode() {

	uint8_t hiddenCursorData = 0;
	hiddenCursor = SDL_CreateCursor(&hiddenCursorData, &hiddenCursorData, 8, 1, 0, 0);

	// Free the hidden SDL cursor created in loadGFXMode
	SDL_FreeCursor(hiddenCursor);

	SurfaceSdlGraphicsManager::unloadGFXMode();
}

#endif
