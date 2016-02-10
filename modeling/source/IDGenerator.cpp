/*
 * (C) Copyright 2015  Arnel I Periquet.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 */

#include <stdafx.h>
#include "IDGenerator.h"

namespace webo {

	namespace Modeling {

		int IDGenerator::gNextObjectID = 1;


		std::string IDGenerator::generateObjectID() {
			std::ostringstream oss;
			oss << gNextObjectID++;
			return "_object__" + oss.str();
		}

	}

}
