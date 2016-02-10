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

		class Type;
		class Object;

		namespace datatype {

			template <typename T>
			class MODELING_API tArray : public DataType {
			public:
				static tArray<T> & instance();

				virtual bool isArray();

				static std::shared_ptr<Object> value(); // empty array
                static std::shared_ptr<Object> value(size_t length);
				static std::shared_ptr<Object> value(char arr[], size_t length);
				static std::shared_ptr<Object> value(int arr[], size_t length);
                static std::shared_ptr<Object> value(double arr[], size_t length);
				static std::shared_ptr<Object> value(std::string arr[], size_t length);
				static std::shared_ptr<Object> value(bool arr[], size_t length);

			private:
				tArray(Type & iBaseType);

				Type & mBaseType;
			};

		}

	}

}

