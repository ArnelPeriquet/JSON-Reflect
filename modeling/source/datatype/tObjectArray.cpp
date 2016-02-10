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
#include "webo/modeling/datatype/tObjectArray.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/Object.h"

using namespace webo::modeling;


namespace webo {

    namespace modeling {

        namespace datatype {

            tObjectArray & tObjectArray::instance(Class & baseType) {
                if (!baseType.mObjectArrayType)
                    baseType.mObjectArrayType = std::make_shared<tObjectArray>(baseType);

                return *baseType.mObjectArrayType;
            }

            std::shared_ptr<Object> tObjectArray::value(Class & baseType) {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance(baseType)); //empty array
                return object;
            }

            std::shared_ptr<Object> tObjectArray::value(Class & baseType, size_t length) {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance(baseType));
                object->asObjectArray(baseType, length);

                std::shared_ptr<Object> * nativeArr = object->asObjectArray(baseType);

                for (size_t i=0; i<length; i++)
                    nativeArr[i] = std::make_shared<Object>(baseType);

                return object;
            }

            std::shared_ptr<Object> tObjectArray::value(Class & baseType, std::shared_ptr<Object> arr[], size_t length) {
                std::shared_ptr<Object> object = std::make_shared<Object>(instance(baseType));
                object->asObjectArray(baseType, length);

                std::shared_ptr<Object> * nativeArr = object->asObjectArray(baseType);

                for (size_t i = 0; i < length; i++)
                    nativeArr[i] = arr[i];

                return object;
            }

            tObjectArray::tObjectArray(Class & baseType)
                : DataType("tObjectArray<" + baseType.name + ">"), mBaseType(baseType) {
            }

            bool tObjectArray::isObjectArray() {
                return true;
            }

            Class & tObjectArray::getBaseType() const {
                return mBaseType;
            }

        }

    }

}
