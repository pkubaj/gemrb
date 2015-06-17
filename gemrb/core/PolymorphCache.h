/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2010 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef POLYMORPHCACHE_H
#define POLYMORPHCACHE_H

#include "ie_types.h"

namespace GemRB {

struct GEM_EXPORT PolymorphCache {
	ieResRef Resource;
	ieDword *stats;

	PolymorphCache() : stats(NULL) { Resource[0] = 0; }
	~PolymorphCache() {
		delete[] stats;
	}
};

}

#endif
