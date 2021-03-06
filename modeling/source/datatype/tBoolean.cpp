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
#include "webo/modeling/datatype/tBoolean.h"
#include "webo/modeling/Object.h"

using namespace webo::modeling;


namespace webo {

	namespace modeling {

		namespace datatype {

			tBoolean & tBoolean::instance() {
				static tBoolean instance_;
				return instance_;
			}

			tBoolean::tBoolean()
				: DataType("tBoolean") {
			}

			std::shared_ptr<Object> tBoolean::value(bool value) {
				std::shared_ptr<Object> object = std::make_shared<Object>(instance());
				object->asBoolean(value);
				return object;
			}

		}

	}

}
