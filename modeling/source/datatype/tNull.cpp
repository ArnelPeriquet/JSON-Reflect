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
#include "webo/modeling/datatype/tNull.h"
#include "webo/modeling/Object.h"

using namespace webo::modeling;


namespace webo {

	namespace modeling {

		namespace datatype {

			tNull & tNull::instance() {
				static tNull instance_;
				return instance_;
			}

			tNull::tNull()
				: DataType("tNull") {
			}

			std::shared_ptr<Object> tNull::value() {
				return std::make_shared<Object>(instance());
			}

		}

	}

}
