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

#include <map>
#include "webo/modeling/ModelExceptions.h"


namespace webo {

	namespace modeling {

		class Type;
		class Class;

		// This is an artificial class that is neither part of the MOF (M2) nor the user model (M1).
		// It merely exists because, by implementing meta-models, MOF Classes become C++ Classes and User Model Classes become
		// C++ objects. So, then, what do User Model objects become? You can't instantiate a C++ object, i.e. C++ does not
		// support dynamically created Class objects.
		//
		class MODELING_API Object {
		public:
			Object(Type & type);
			Object(Type & type, std::string & objectID);
			~Object();

			std::string getID();

            bool operator==(std::shared_ptr<Object> & object);
            bool operator==(Object & object);

            bool operator!=(std::shared_ptr<Object> & object);
            bool operator!=(Object & object);
            
            bool equals(std::shared_ptr<Object> & object);
			bool equals(Object & object);
            
			bool hasValue(std::string name);
			std::shared_ptr<Object> set(std::string name, std::shared_ptr<Object> iValue);
			std::shared_ptr<Object> get(std::string name);

			std::string asString(std::string value);
			char asCharacter(char value);
			int asInteger(int value);
            double asFloat(double value);
			bool asBoolean(bool value);

			std::shared_ptr<Object> * asObjectArray(Class & baseType, int length);

			template <typename T>
			std::shared_ptr<Object> * asArray(int length) {
				if (!type.equals(webo::modeling::datatype::tArray<T>::instance()))
					throw webo::modeling::TypeMismatchException("mismatched type while trying to set value as " + 
                        type.name + ", expected type=" + webo::modeling::datatype::tArray<T>::instance().name);

				if (length <= 0) {
					std::ostringstream oss;
					oss << length;
					throw std::invalid_argument(std::string("requested array length of ") + oss.str() + " is not valid");
				}

				deleteArrayValue();
				mArrayValue = new std::shared_ptr<Object>[length];
				mArrayLength = length;

				return mArrayValue;
			}

			std::string asString() const;
			char asCharacter() const;
			int asInteger() const;
            double asFloat() const;
			bool asBoolean() const;
            bool isNull() const;

			size_t getObjectArrayLength() const;
			std::shared_ptr<Object> * asObjectArray(Class & baseType) const;

			size_t getArrayLength() const;

			template <typename T>
			std::shared_ptr<Object> * asArray()  const {
				if (!type.equals(datatype::tArray<T>::instance()))
					throw TypeMismatchException("mismatched type while trying to get value as " + type.name + 
                        ", expected type=" + webo::modeling::datatype::tArray<T>::instance().name);

				if (mArrayLength <= 0)
					return nullptr;

				return mArrayValue;
			}

			Type & type;

		private:
            void initialize();
			void deleteArrayValue();
			void deleteObjectArrayValue();

			std::string mID;

			std::map<std::string, std::shared_ptr<Object>>  mAttributeValues;
			std::string                                     mStringValue;
			char                                            mCharacterValue;
			int                                             mIntegerValue;
            double                                          mFloatValue;
			bool                                            mBooleanValue;
			std::shared_ptr<Object> *                       mArrayValue;
            size_t                                          mArrayLength;
			std::shared_ptr<Object> *                       mObjectArrayValue;
			size_t                                          mObjectArrayLength;
			Class *                                         mObjectArrayBaseType;
		};

	}

}
