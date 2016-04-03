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
#include "XmlStringifier.h"
#include "webo/modeling/Object.h"
#include "webo/modeling/Type.h"
#include "webo/modeling/Class.h"
#include "webo/modeling/ClassModel.h"
#include "webo/modeling/datatype/DataTypes.h"


using namespace webo::modeling;
using namespace webo::modeling::datatype;


// unit tests
//
// - object attribute starting with '#' results in an XML Attribute with the name following '#'
// - object attribute starting with '@' results in a directly nested XML Element with the name following '@'
// - object attributes that are primitive types result in sub-nodes of free text; the object attribute name is ignored
// - object attributes that are user class instances result in nested XML Elements; the object attribute name is ignored

namespace {
    static const char XML_ATTRIB_INDICATOR = '#';
    static const char XML_DIRECT_NODE_INDICATOR = '@';
}


namespace webo {

	namespace encoding_xml {

		XmlStringifier::XmlStringifier(ClassModel & classModel)
			: mClassModel(classModel), mIndentation(0) {
		}

		void XmlStringifier::indent(std::stringstream & ss) const {
			for (int i = 0; i < mIndentation * 3; i++)
				ss << " ";
		}

		bool XmlStringifier::isAttribute(std::string & attribName) {
			return attribName.length() > 0 && attribName.at(0) == XML_ATTRIB_INDICATOR;
		}

		bool XmlStringifier::isDirectNode(std::string & attribName) {
			return attribName.length() > 0 && attribName.at(0) == XML_DIRECT_NODE_INDICATOR;
		}

		std::string XmlStringifier::stringify(Object & object, Class & clazz, bool allowMissingAttributes) {
			std::stringstream ss;
			stringifyObject(ss, object, clazz, allowMissingAttributes);
			return ss.str();
		}

		void XmlStringifier::stringifyObject(std::stringstream & ss, Object & object, Class & clazz, bool allowMissingAttributes) {
			ss << "<" << clazz.name;
			stringifyAttributes(ss, object, clazz, allowMissingAttributes);
			ss << ">";

			ss << "\n";
			mIndentation++;
			indent(ss);

			stringifyNodes(ss, object, clazz, allowMissingAttributes);

			ss << "\n";
			mIndentation--;
			indent(ss);

			ss << "</" << clazz.name << ">";
		}

		void XmlStringifier::stringifyAttributes(std::stringstream & ss, Object & object, Class & clazz, bool allowMissingAttributes) {
			std::vector<std::string> & attribNames = clazz.getAttributeNames();

			for (auto attribName: attribNames) {
				if (!allowMissingAttributes && !object.hasValue(attribName))
					throw std::runtime_error("object is missing value, name=" + attribName);

				if (isAttribute(attribName) && object.hasValue(attribName)) {
					std::shared_ptr<Object> attribValue = object.get(attribName);
					Type &  vAttribType = attribValue->type;
					ss << " " << attribName.substr(1) << "=\"";
					stringifyText(ss, *attribValue, vAttribType);
                    ss << "\"";
				}
			}
		}

		void XmlStringifier::stringifyNodes(std::stringstream & ss, Object & object, Class & clazz, bool allowMissingAttributes) {
			std::vector<std::string> nodeNames;
			extractNodes(nodeNames, object, clazz, allowMissingAttributes);

            size_t length = nodeNames.size();
            size_t count = 0;

			for (auto nodeName: nodeNames) {
				std::shared_ptr<Object> nodeValue = object.get(nodeName);

                Type & type = nodeValue->type;

                if (type.isSimpleArray()) {
                    ; // ignored cause it doesn't make sense to have an array of unnamed nodes in XML
                } else if (type.isObjectArray()) {
                    std::shared_ptr<Object> * arr = nodeValue->asObjectArray();

                    for (size_t i = 0; i < nodeValue->getObjectArrayLength(); i++) {
                        stringifyNestedNode(ss, *arr[i], allowMissingAttributes);
                    }
                }  else if (type.isBuiltIn()) {
                    stringifyDirectNodeOrFreeText(ss, nodeName, *nodeValue);
                } else {
                    stringifyNestedNode(ss, *nodeValue, allowMissingAttributes);
                }

				if (count++ < length-1) {
					ss << "\n";
					indent(ss);
				}
			}
		}

		void XmlStringifier::extractNodes(std::vector<std::string> & oNodeNames, Object & object, Class & clazz, bool allowMissingAttributes) {
			std::vector<std::string> & attribNames = clazz.getAttributeNames();

			for (auto attribName: attribNames) {
				if (!allowMissingAttributes && !object.hasValue(attribName))
					throw std::runtime_error("object is missing value, name=" + attribName);

				if (!isAttribute(attribName) && object.hasValue(attribName))
					oNodeNames.push_back(attribName);
			}
		}

		void XmlStringifier::stringifyDirectNodeOrFreeText(std::stringstream & ss, std::string & name, Object & iValue) {
			if (isDirectNode(name)) {
				ss << "<" << name.substr(1) << ">";
				stringifyText(ss, iValue, iValue.type);
				ss << "</" << name.substr(1) << ">";
			}
			else {
				stringifyText(ss, iValue, iValue.type);
			}
		}

		void XmlStringifier::stringifyNestedNode(std::stringstream & ss, Object & iValue, bool allowMissingAttributes) {
			Class * clazz = dynamic_cast<Class *>(&(iValue.type));

			if (clazz)
				stringifyObject(ss, iValue, *clazz, allowMissingAttributes);
			else
				throw std::runtime_error("attempt to convert a non-class to a class, type=" + iValue.type.name);
		}

		void XmlStringifier::stringifyText(std::stringstream & ss, Object & object, Type & type) {
			if (type == tCharacter::instance())
				ss << object.asCharacter();
			else if (type == tInteger::instance())
				ss << object.asInteger();
            else if (type == tFloat::instance())
                ss << object.asFloat();
			else if (type == tString::instance())
				ss << object.asString();
			else if (type == tBoolean::instance())
				ss << (object.asBoolean() ? "true" : "false");
			else if (type == tNull::instance())
				ss << "null";
			else
				throw UnsupportedPrimitiveType("unsupported primitive type=" + type.name);
		}

	}

}
