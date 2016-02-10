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

#include "webo/modeling/datatype/DataType.h"


namespace webo {

	namespace modeling {

		class Object;
		
		namespace datatype {

			class MODELING_API tCharacter : public DataType {
			public:
				static tCharacter & instance();
				static std::shared_ptr<Object> value(char value);

			private:
				tCharacter();
			};

		}

	}

}
