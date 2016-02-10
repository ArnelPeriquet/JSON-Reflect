/*
 * (C) Copyright 2015  Arnel I Periquet.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 */

#pragma once

#include "Class.h"


namespace webo {

	namespace modeling {

		class Object;


		class MODELING_API tObject : public Class {
		public:
			static tObject & instance();

			virtual bool isBuiltIn();

			virtual void addSuperClass(Class & superClass);

		private:
			tObject();
		};

	}

}