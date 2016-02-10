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
#include "webo/modeling/tObject.h"


namespace webo {

	namespace modeling {

		tObject & tObject::instance() {
			static tObject _instance;
			return _instance;
		}

		tObject::tObject()
			: Class("tObject") {
		}

		bool tObject::isBuiltIn() {
			return true;
		}

		void tObject::addSuperClass(Class & superClass) {
			throw std::runtime_error("attempt to add superclass to tObject, name=" + superClass.name);
		}

	}

}
