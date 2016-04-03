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
#include "JsonParser.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/Type.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/tObject.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling;
using namespace webo::modeling::datatype;

namespace {
    template <typename T>
    std::vector<T> as_vector(ptree & pt, ptree::key_type const & key)
    {
        std::vector<T> r;

        BOOST_FOREACH(ptree::value_type & child, pt.get_child(key)) {
            r.push_back(child.second.get_value<T>());
        }

        return r;
    }

    std::vector<ptree *> as_vector(ptree & pt, ptree::key_type const & key)
    {
        std::vector<ptree *> r;

        BOOST_FOREACH(ptree::value_type & child, pt.get_child(key)) {
            r.push_back(&child.second);
        }

        return r;
    }
}

namespace webo {

	namespace encoding {

		JsonParser::JsonParser(ClassModel & classModel)
			: mClassModel(classModel) {
		}

		std::shared_ptr<Object> JsonParser::parse(std::string & jsonString, Class & clazz, bool allowMissingAttributes) {
			try {
				std::stringstream jsonStream(jsonString);
                return parse(jsonStream, clazz, allowMissingAttributes);
			}
			catch (std::exception & ex) {
				throw std::runtime_error(std::string(ex.what()) + ", json=" + jsonString);
			}
		}

        std::shared_ptr<Object> JsonParser::parse(std::stringstream & jsonStream, Class & clazz, bool allowMissingAttributes) {
            try {
                ptree propTree;
                read_json(jsonStream, propTree);
                return createObject(clazz, propTree, allowMissingAttributes);
            }
            catch (std::exception & ex) {
                throw std::runtime_error(std::string(ex.what()));
            }
        }

		std::shared_ptr<Object> JsonParser::createObject(Class & clazz, ptree & propTree, bool allowMissingAttributes) {
			std::shared_ptr<Object> object = std::make_shared<Object>(clazz);
			createAttributes(clazz, object, propTree, allowMissingAttributes);
			return object;
		}

		void JsonParser::createAttributes(Class & clazz, std::shared_ptr<Object> iObject, boost::property_tree::ptree & propTree, bool allowMissingAttributes) {
			std::vector<std::string> & attribNames = clazz.getAttributeNames();

			for (std::vector<std::string>::iterator attribName = attribNames.begin(); attribName != attribNames.end(); ++attribName) {
				boost::optional<boost::property_tree::ptree&> child = propTree.get_child_optional(*attribName);

				if (!allowMissingAttributes && !child)
					throw std::runtime_error("missing attribute, name=" + *attribName);

				if (child) {
					std::shared_ptr<Object> vAttribValue;
					Type & attribType = clazz.getAttributeType(*attribName);

					if (attribType.isBuiltIn()) {
						if (attribType.isSimpleArray())
							vAttribValue = createArray(*attribName, attribType, propTree);
						else if (attribType.isObjectArray())
							vAttribValue = createObjectArray(*attribName, attribType, propTree, allowMissingAttributes);
						else
							vAttribValue = createPrimitive(*attribName, attribType, propTree);
					}
					else {
						Class * vAttribClass = dynamic_cast<Class *>(&attribType);

						if (vAttribClass)
							vAttribValue = createObject(*vAttribClass, propTree.get_child(*attribName), allowMissingAttributes);
						else
							throw std::runtime_error("attempt to convert a non-class to a class, type=" + attribType.name);
					}

					iObject->set(*attribName, vAttribValue);
				}
			}
		}

		std::shared_ptr<Object> JsonParser::createArray(std::string name, Type & type, boost::property_tree::ptree & propTree) {
			if (type == tArray<tCharacter>::instance()) {
				std::vector<char> vect = as_vector<char>(propTree, name);

				if (vect.size() == 0)
					return tArray<tCharacter>::value(); // empty array
				else
					return tArray<tCharacter>::value(&(vect[0]), vect.size());
			}

			if (type == tArray<tInteger>::instance()) {
				std::vector<int> vect = as_vector<int>(propTree, name);

				if (vect.size() == 0)
					return tArray<tInteger>::value(); // empty array
				else
					return tArray<tInteger>::value(&(vect[0]), vect.size());
			}

            if (type == tArray<tFloat>::instance()) {
                std::vector<double> vect = as_vector<double>(propTree, name);

                if (vect.size() == 0)
                    return tArray<tFloat>::value(); // empty array
                else
                    return tArray<tFloat>::value(&(vect[0]), vect.size());
            }

			if (type == tArray<tString>::instance()) {
				std::vector<std::string> vect = as_vector<std::string>(propTree, name);

				if (vect.size() == 0)
					return tArray<tString>::value(); // empty array
				else
					return tArray<tString>::value(&(vect[0]), vect.size());
			}

			if (type == tArray<tBoolean>::instance()) {
				std::shared_ptr<Object> returnVal;

				std::vector<bool> vect = as_vector<bool>(propTree, name);

				if (vect.size() == 0) {
					return tArray<tBoolean>::value(); // empty array
				}
				else {
					bool * bools = new bool[vect.size()];

					try {
						for (size_t i = 0; i < vect.size(); i++)
							bools[i] = vect[i];

						returnVal = tArray<tBoolean>::value(bools, vect.size());
					}
					catch (std::exception & ex) {
						delete[] bools;
						throw ex;
					}

					delete[] bools;

					return returnVal;
				}
			}

			throw std::runtime_error("unsupported tArray, name=" + name + ", type=" + type.name);
		}

		std::shared_ptr<Object> JsonParser::createObjectArray(std::string name, Type & type, boost::property_tree::ptree & propTree, bool allowMissingAttributes) {
			if (type.name.find("tObjectArray") != std::string::npos) {
				std::shared_ptr<Object> returnVal;

				int endIndex = type.name.find(">");
				std::string baseClassName = type.name.substr(13, endIndex - 13);
				Class & baseClass = mClassModel.getClass(baseClassName);

				std::vector<ptree *> vect = as_vector(propTree, name);

				if (vect.size() == 0) {
					return tObjectArray::value(baseClass); // empty array
				}
				else {
					std::shared_ptr<Object> * objects = new std::shared_ptr<Object>[vect.size()];

					try {
						for (size_t i = 0; i < vect.size(); i++)
							objects[i] = createObject(baseClass, *vect[i], allowMissingAttributes);

						returnVal = tObjectArray::value(baseClass, objects, vect.size());
					}
					catch (std::exception & ex) {
						delete[] objects;
						throw ex;
					}

					delete[] objects;

					return returnVal;
				}
			}

			throw std::runtime_error("internal error: expecting tObjectArray, name=" + name + ", type=" + type.name);
		}

		std::shared_ptr<Object> JsonParser::createPrimitive(std::string name, Type & type, boost::property_tree::ptree & propTree) {
			if (type == tCharacter::instance())
				return tCharacter::value(propTree.get<char>(name));

			if (type == tInteger::instance())
				return tInteger::value(propTree.get<int>(name));

            if (type == tFloat::instance())
                return tFloat::value(propTree.get<double>(name));

			if (type == tString::instance())
				return tString::value(propTree.get<std::string>(name));

			if (type == tBoolean::instance())
				return tBoolean::value(propTree.get<bool>(name));

			if (type == tNull::instance())
				return tNull::value();

			throw std::runtime_error("unsupported primitive type, name=" + name + ", type=" + type.name);
		}

	}

}
