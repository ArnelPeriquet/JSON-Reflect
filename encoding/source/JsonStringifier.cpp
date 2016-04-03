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
#include "JsonStringifier.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/Type.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;


namespace webo {

	namespace encoding {

		JsonStringifier::JsonStringifier(ClassModel & classModel)
			: mClassModel(classModel), mIndentation(0) {
		}

		void JsonStringifier::indent(std::stringstream & ss) const {
			for (int i = 0; i < mIndentation * 3; i++)
				ss << " ";
		}

		std::string JsonStringifier::stringify(Object & object, Type & type, bool allowMissingAttributes) {
			std::stringstream ss;

            if (type.isBuiltIn()) {
                if (type.isSimpleArray())
                    stringifyArray(ss, object, type);
                else if (type.isObjectArray())
                    stringifyObjectArray(ss, object, type, allowMissingAttributes);
                else
                    stringifyPrimitive(ss, object, type);
            } else {
                Class & theClass = dynamic_cast<Class &>(type);
                stringifyObject(ss, object, theClass, allowMissingAttributes);
            }

            return ss.str();
        }

		void JsonStringifier::stringifyObject(std::stringstream & ss, Object & object, Class & clazz, bool allowMissingAttributes) {
			std::vector<std::string> & attribNames = clazz.getAttributeNames();

			ss << "{\n";
			mIndentation++;
			mIndentation++;

			for (std::vector<std::string>::iterator attribName = attribNames.begin(); attribName != attribNames.end(); ++attribName) {
				if (!allowMissingAttributes && !object.hasValue(*attribName))
					throw std::runtime_error("object is missing value, name=" + *attribName);

				if (object.hasValue(*attribName)) {
					std::shared_ptr<Object> attribValue = object.get(*attribName);
					Type & attribType = clazz.getAttributeType(*attribName);

					mIndentation--;
					indent(ss);

					ss << "\"" << *attribName << "\"" << " :\n";

					mIndentation++;
					indent(ss);

					if (attribType.isBuiltIn()) {
						if (attribType.isSimpleArray())
							stringifyArray(ss, *attribValue, attribType);
						else if (attribType.isObjectArray())
							stringifyObjectArray(ss, *attribValue, attribType, allowMissingAttributes);
						else
							stringifyPrimitive(ss, *attribValue, attribType);
					}
					else {
						Class * attribClass = dynamic_cast<Class *>(&attribType);

						if (attribClass)
							stringifyObject(ss, *attribValue, *attribClass, allowMissingAttributes);
						else
							throw std::runtime_error("attempt to convert a non-class to a class, type=" + attribType.name);
					}

					if (attribName + 1 != attribNames.end())
						ss << ",\n";
				}
			}

			ss << "\n";

			mIndentation--;
			mIndentation--;
			indent(ss);
			ss << "}";
		}

		void JsonStringifier::stringifyArray(std::stringstream & ss, Object & object, Type & type) {
			int length = object.getArrayLength();

			ss << "[\n";
			mIndentation++;
			indent(ss);

			if (type == tArray<tCharacter>::instance()) {
				std::shared_ptr<Object> * arr = object.asArray();

				for (int i = 0; i < length; i++) {
					ss << "\"" << arr[i]->asCharacter() << "\"";

					if (i != length - 1) {
						ss << ",\n";
						indent(ss);
					}
				}
			}

			if (type == tArray<tInteger>::instance()) {
				std::shared_ptr<Object> * arr = object.asArray();

				for (int i = 0; i < length; i++) {
					ss << arr[i]->asInteger();

					if (i != length - 1) {
						ss << ",\n";
						indent(ss);
					}
				}
			}

            if (type == tArray<tFloat>::instance()) {
                std::shared_ptr<Object> * arr = object.asArray();

                for (int i = 0; i < length; i++) {
                    ss << arr[i]->asFloat();

                    if (i != length - 1) {
                        ss << ",\n";
                        indent(ss);
                    }
                }
            }

			if (type == tArray<tString>::instance()) {
				std::shared_ptr<Object> * arr = object.asArray();

				for (int i = 0; i < length; i++) {
					ss << "\"" << arr[i]->asString() << "\"";

					if (i != length - 1) {
						ss << ",\n";
						indent(ss);
					}
				}
			}

			if (type == tArray<tBoolean>::instance()) {
				std::shared_ptr<Object> * arr = object.asArray();

				for (int i = 0; i < length; i++) {
					ss << (arr[i]->asBoolean() ? "true" : "false");

					if (i != length - 1) {
						ss << ",\n";
						indent(ss);
					}
				}
			}

            if (type == tArray<tNull>::instance()) {
                std::shared_ptr<Object> * arr = object.asArray();

                for (int i = 0; i < length; i++) {
                    ss << "null";

                    if (i != length - 1) {
                        ss << ",\n";
                        indent(ss);
                    }
                }
            }

            if (type == tArray<tArray<tBoolean>>::instance()) {
                std::shared_ptr<Object> * arr = object.asArray();

                for (int i = 0; i < length; i++) {
                    stringifyArray(ss, *arr[i], tArray<tBoolean>::instance());

                    if (i != length - 1) {
                        ss << ",\n";
                        indent(ss);
                    }
                }
            }

			ss << "\n";
			mIndentation--;
			indent(ss);
			ss << "]";
		}

		void JsonStringifier::stringifyObjectArray(std::stringstream & ss, Object & object, Type & type, bool allowMissingAttributes) {
			ss << "[\n";
			mIndentation++;
			indent(ss);

			if (type.isObjectArray()) {
				tObjectArray & objArrType = dynamic_cast<tObjectArray &>(type);
				std::shared_ptr<Object> * arr = object.asObjectArray();
				int length = object.getObjectArrayLength();

				for (int i = 0; i < length; i++) {
                    Class & clazz = dynamic_cast<Class &>(arr[i]->type);
					stringifyObject(ss, *arr[i], clazz, allowMissingAttributes);

					if (i != length - 1) {
						ss << ",\n";
						indent(ss);
					}
				}
			}
			else {
				throw std::runtime_error("internal error: expecting tObjectArray, type=" + type.name);
			}

			ss << "\n";
			mIndentation--;
			indent(ss);
			ss << "]";
		}


		void JsonStringifier::stringifyPrimitive(std::stringstream & ss, Object & object, Type & type) {
			if (type == tCharacter::instance())
				ss << "\"" << object.asCharacter() << "\"";
			else if (type == tInteger::instance())
				ss << object.asInteger();
            else if (type == tFloat::instance())
                ss << object.asFloat();
			else if (type == tString::instance())
				ss << "\"" << object.asString() << "\"";
			else if (type == tBoolean::instance())
				ss << (object.asBoolean() ? "true" : "false");
			else if (type == tNull::instance())
				ss << "null";
			else
				throw UnsupportedPrimitiveType("unsupported primitive type=" + type.name);
		}

	}

}
