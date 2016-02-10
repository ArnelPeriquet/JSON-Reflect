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
#include "webo/modeling/datatype/tArray.h"
#include "webo/modeling/datatype/DataTypes.h"
#include "webo/modeling/Object.h"

using namespace webo::modeling;


namespace webo {

	namespace modeling {

		namespace datatype {

			// various supported instantiations
			template class tArray<tCharacter>;
			template class tArray<tInteger>;
            template class tArray<tFloat>;
			template class tArray<tString>;
			template class tArray<tBoolean>;
			template class tArray<tNull>;
            template class tArray<tArray<tCharacter>>;
            template class tArray<tArray<tInteger>>;
            template class tArray<tArray<tFloat>>;
            template class tArray<tArray<tString>>;
            template class tArray<tArray<tBoolean>>;
            template class tArray<tArray<tNull>>;


			template <typename T>
			tArray<T> & tArray<T>::instance() {
                static tArray<T> instance_( T::instance() );
				return instance_;
			}

			template <typename T>
			tArray<T>::tArray(Type & baseType)
				: DataType(std::string("tArray") + "<" + baseType.name + ">"), mBaseType(baseType) {
			}

			template <typename T>
			bool tArray<T>::isArray() {
				return true;
			}

			template <typename T>
			std::shared_ptr<Object> tArray<T>::value() {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance()); //empty array
                return object;
			}

            template <typename T>
            std::shared_ptr<Object> tArray<T>::value(size_t length) {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance());
                object->asArray<T>(length);

                for (size_t i=0; i<length; i++)
                    object->asArray<T>()[i] = std::make_shared<Object>(T::instance());

                return object;
            }
            
			template <typename T>
			std::shared_ptr<Object> tArray<T>::value(char arr[], size_t length) {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance());
                object->asArray<T>(length);

				for (size_t i=0; i<length; i++)
					object->asArray<T>()[i] = tCharacter::value(arr[i]);

				return object;
			}

			template <typename T>
			std::shared_ptr<Object> tArray<T>::value(int arr[], size_t length) {
				std::shared_ptr<Object> object = std::make_shared<Object>(instance());
                object->asArray<T>(length);

				for (size_t i=0; i<length; i++)
					object->asArray<T>()[i] = tInteger::value(arr[i]);

				return object;
			}

            template <typename T>
            std::shared_ptr<Object> tArray<T>::value(double arr[], size_t length) {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance());
                object->asArray<T>(length);

                for (size_t i = 0; i<length; i++)
                    object->asArray<T>()[i] = tFloat::value(arr[i]);

                return object;
            }

			template <typename T>
			std::shared_ptr<Object> tArray<T>::value(std::string arr[], size_t length) {
				std::shared_ptr<Object> object = std::make_shared<Object>(instance());
                object->asArray<T>(length);

				for (size_t i=0; i<length; i++)
					object->asArray<T>()[i] = tString::value(arr[i]);

				return object;
			}

			template <typename T>
			std::shared_ptr<Object> tArray<T>::value(bool arr[], size_t length) {
				std::shared_ptr<Object> object = std::make_shared<Object>(instance());
                object->asArray<T>(length);

				for (size_t i=0; i<length; i++)
					object->asArray<T>()[i] = tBoolean::value(arr[i]);

				return object;
			}

		}

	}

}
