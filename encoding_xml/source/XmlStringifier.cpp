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

		XmlStringifier::XmlStringifier(ClassModel & iClassModel)
			: mClassModel(iClassModel), mIndentation(0) {
		}

		void XmlStringifier::indent(std::stringstream & ss) const {
			for (int i = 0; i < mIndentation * 3; i++)
				ss << " ";
		}

		bool XmlStringifier::isAttribute(std::string & iAttribName) {
			return iAttribName.length() > 0 && iAttribName.at(0) == XML_ATTRIB_INDICATOR;
		}

		bool XmlStringifier::isDirectNode(std::string & iAttribName) {
			return iAttribName.length() > 0 && iAttribName.at(0) == XML_DIRECT_NODE_INDICATOR;
		}

		std::string XmlStringifier::stringify(Object & iObject, Class & iClass, bool iAllowMissingAttributes) {
			std::stringstream ss;
			stringifyObject(ss, iObject, iClass, iAllowMissingAttributes);
			return ss.str();
		}

		void XmlStringifier::stringifyObject(std::stringstream & ss, Object & iObject, Class & iClass, bool iAllowMissingAttributes) {
			ss << "<" << iClass.name;
			stringifyAttributes(ss, iObject, iClass, iAllowMissingAttributes);
			ss << ">";

			ss << "\n";
			mIndentation++;
			indent(ss);

			stringifyNodes(ss, iObject, iClass, iAllowMissingAttributes);

			ss << "\n";
			mIndentation--;
			indent(ss);

			ss << "</" << iClass.name << ">";
		}

		void XmlStringifier::stringifyAttributes(std::stringstream & ss, Object & iObject, Class & iClass, bool iAllowMissingAttributes) {
			std::vector<std::string> & vAttribNames = iClass.getAttributeNames();

			for (std::vector<std::string>::iterator vAttribName = vAttribNames.begin(); vAttribName != vAttribNames.end(); ++vAttribName) {
				if (!iAllowMissingAttributes && !iObject.hasValue(*vAttribName))
					throw std::runtime_error("object is missing value, name=" + *vAttribName);

				if (isAttribute(*vAttribName) && iObject.hasValue(*vAttribName)) {
					std::shared_ptr<Object> vAttribValue = iObject.get(*vAttribName);
					Type &  vAttribType = vAttribValue->type;
					ss << " " << vAttribName->substr(1) << "=\"";
					stringifyText(ss, *vAttribValue, vAttribType);
                    ss << "\"";
				}
			}
		}

		void XmlStringifier::stringifyNodes(std::stringstream & ss, Object & iObject, Class & iClass, bool iAllowMissingAttributes) {
			std::vector<std::string> vNodeNames;
			extractNodes(vNodeNames, iObject, iClass, iAllowMissingAttributes);

			for (std::vector<std::string>::iterator vNodeName = vNodeNames.begin(); vNodeName != vNodeNames.end(); ++vNodeName) {
				std::shared_ptr<Object> vNodeValue = iObject.get(*vNodeName);

				if (vNodeValue->type.isBuiltIn())
					stringifyDirectNodeOrFreeText(ss, *vNodeName, *vNodeValue);
				else
					stringifyNestedNode(ss, *vNodeValue, iAllowMissingAttributes);

				if (vNodeName + 1 != vNodeNames.end()) {
					ss << "\n";
					indent(ss);
				}
			}
		}

		void XmlStringifier::extractNodes(std::vector<std::string> & oNodeNames, Object & iObject, Class & iClass, bool iAllowMissingAttributes) {
			std::vector<std::string> & vAttribNames = iClass.getAttributeNames();

			for (std::vector<std::string>::iterator vAttribName = vAttribNames.begin(); vAttribName != vAttribNames.end(); ++vAttribName) {
				if (!iAllowMissingAttributes && !iObject.hasValue(*vAttribName))
					throw std::runtime_error("object is missing value, name=" + *vAttribName);

				if (!isAttribute(*vAttribName) && iObject.hasValue(*vAttribName))
					oNodeNames.push_back(*vAttribName);
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

		void XmlStringifier::stringifyNestedNode(std::stringstream & ss, Object & iValue, bool iAllowMissingAttributes) {
			Class * vClass = dynamic_cast<Class *>(&(iValue.type));

			if (vClass)
				stringifyObject(ss, iValue, *vClass, iAllowMissingAttributes);
			else
				throw std::runtime_error("attempt to convert a non-class to a class, type=" + iValue.type.name);
		}

		void XmlStringifier::stringifyText(std::stringstream & ss, Object & iObject, Type & type) {
			if (type == tCharacter::instance())
				ss << iObject.asCharacter();
			else if (type == tInteger::instance())
				ss << iObject.asInteger();
            else if (type == tFloat::instance())
                ss << iObject.asFloat();
			else if (type == tString::instance())
				ss << iObject.asString();
			else if (type == tBoolean::instance())
				ss << (iObject.asBoolean() ? "true" : "false");
			else if (type == tNull::instance())
				ss << "null";
			else
				throw UnsupportedPrimitiveType("unsupported primitive type=" + type.name);
		}

	}

}
