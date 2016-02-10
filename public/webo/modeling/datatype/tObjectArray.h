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

		class Class;
		class Object;

		namespace datatype {

			class MODELING_API tObjectArray : public DataType {
			public:
                static tObjectArray & instance(Class & baseType);

				static std::shared_ptr<Object> value(Class & baseType); // empty array
                static std::shared_ptr<Object> value(Class & baseType, size_t length);
				static std::shared_ptr<Object> value(Class & baseType, std::shared_ptr<Object> arr[], size_t length);
				
				virtual bool isObjectArray();
				Class & getBaseType() const;
                
                tObjectArray(Class & baseType);

            private:
                Class & mBaseType;
			};

		}

	}

}
