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
#include "webo/modeling/Object.h"
#include "webo/modeling/Type.h"
#include "webo/modeling/Class.h"
#include "IDGenerator.h"
#include "webo/modeling/datatype/DataTypes.h"

using namespace webo::modeling::datatype;


namespace webo {

    namespace modeling {


        char                                            mCharacterValue;
        int                                             mIntegerValue;
        bool                                            mBooleanValue;

        Object::Object(Type & type) : type(type) {
            if (type == tVoid::instance())
                throw std::invalid_argument("unable to create Object of type tVoid");

            mID = Modeling::IDGenerator::generateObjectID();
            initialize();
        }

        Object::Object(Type & type, std::string & objectID) : type(type), mID(objectID) {
            if (type == tVoid::instance())
                throw std::invalid_argument("unable to create Object of type tVoid");

            initialize();
        }

        Object::~Object() {
            deleteArrayValue();
            deleteObjectArrayValue();
        }

        void Object::initialize() {
            mCharacterValue = 0;
            mIntegerValue = 0;
            mFloatValue = 0.0;
            mBooleanValue = false;
            mArrayValue = nullptr;
            mArrayLength = 0;
            mObjectArrayValue = nullptr;
            mObjectArrayLength = 0;
        }

        void Object::deleteObjectArrayValue() {
            if (mObjectArrayValue) {
                delete[] mObjectArrayValue;
                mObjectArrayValue = nullptr;
                mObjectArrayLength = 0;
            }
        }

        void Object::deleteArrayValue() {
            if (mArrayValue) {
                delete[] mArrayValue;
                mArrayValue = nullptr;
                mArrayLength = 0;
            }
        }

        std::string Object::getID() {
            return mID;
        }

        bool Object::operator==(std::shared_ptr<Object> & object) {
            return equals(object);
        }

        bool Object::operator==(Object & object) {
            return equals(object);
        }

        bool Object::operator!=(std::shared_ptr<Object> & object) {
            return !equals(object);
        }

        bool Object::operator!=(Object & object) {
            return !equals(object);
        }

        bool Object::equals(std::shared_ptr<Object> & object) {
            return equals(*object);
        }

        bool Object::equals(Object & object) {
            if (!object.type.equals(tNull::instance()) &&  // type tNull is compatible with all other types
                !type.equals(object.type))
                throw TypeMismatchException("mismatched type while trying to set attribute value, type=" + type.name);

            if (type.isBuiltIn()) {
                if (type.equals(tString::instance()))
                    return mStringValue == object.asString();
                if (type.equals(tCharacter::instance()))
                    return mCharacterValue == object.asCharacter();
                if (type.equals(tInteger::instance()))
                    return mIntegerValue == object.asInteger();
                if (type.equals(tFloat::instance()))
                    return mFloatValue == object.asFloat();
                if (type.equals(tBoolean::instance()))
                    return mBooleanValue == object.asBoolean();
                if (type.equals(tNull::instance()))
                    return object.type.equals(tNull::instance());

                throw std::exception(std::string("unknown type encountered, type=" + type.name).c_str());
            } else {
                return getID() == object.getID();
            }
        }

        // convenience methods
        std::shared_ptr<Object> Object::set(std::string name, char * value) { return set(name, tString::value(value)); }
        std::shared_ptr<Object> Object::set(std::string name, std::string value) { return set(name, tString::value(value)); }
        std::shared_ptr<Object> Object::set(std::string name, char value) { return set(name, tCharacter::value(value)); }
        std::shared_ptr<Object> Object::set(std::string name, int value) { return set(name, tInteger::value(value)); }
        std::shared_ptr<Object> Object::set(std::string name, double value) { return set(name, tFloat::value(value)); }
        std::shared_ptr<Object> Object::set(std::string name, float value) { return set(name, tFloat::value(value)); }
        std::shared_ptr<Object> Object::set(std::string name, bool value) { return set(name, tBoolean::value(value)); }
        std::shared_ptr<Object> Object::set(std::string name, std::vector<std::string> value) {
            return set(name, tArray<tString>::value(&value[0], value.size()));
        }
        std::shared_ptr<Object> Object::set(std::string name, std::vector<char> value) {
            return set(name, tArray<tCharacter>::value(&value[0], value.size()));
        }
        std::shared_ptr<Object> Object::set(std::string name, std::vector<int> value) {
            return set(name, tArray<tInteger>::value(&value[0], value.size()));
        }
        std::shared_ptr<Object> Object::set(std::string name, std::vector<double> value) {
            return set(name, tArray<tFloat>::value(&value[0], value.size()));
        }
        std::shared_ptr<Object> Object::set(std::string name, std::vector<float> value) {
            return set(name, tArray<tFloat>::value(&value[0], value.size()));
        }
        std::shared_ptr<Object> Object::set(std::string name, std::vector<bool> value) {
            bool * arr = nullptr;
            std::shared_ptr<Object> object;

            try {
                arr = new bool[value.size()];
                size_t idx = 0;

                for (bool val : value)
                    arr[idx++] = val;

                object = set(name, tArray<tBoolean>::value(arr, value.size()));
            }
            catch (std::exception &) {
                if (arr)
                    delete[] arr;
                throw;
            }

            if (arr)
                delete[] arr;

            return object;
        }

        std::shared_ptr<Object> Object::set(std::string name, std::shared_ptr<Object> value) {
            if (type.isBuiltIn())
                throw ObjectIsNotAClassException("attempt to set attribute value on type that is not a class, type=" + type.name);

            Class & c = dynamic_cast<Class &>(type);

            if (!c.hasAttribute(name))
                throw UnknownAttributeException("unknown attribute name=" + name);

            if (!value->type.equals(tNull::instance()) &&  // type tNull is compatible with all other types
                !c.getAttributeType(name).equals(value->type))
                throw TypeMismatchException("mismatched type while trying to set value for attribute \"" + name + "\", expecting type=" 
                    + c.getAttributeType(name).name + " but got type=" + value->type.name);

            mAttributeValues[name] = value;

            return mAttributeValues[name];
        }

        bool Object::hasValue(std::string name) {
            return mAttributeValues.find(name) != mAttributeValues.end() && mAttributeValues[name];
        }

        std::shared_ptr<Object> Object::get(std::string name) {
            if (type.isBuiltIn())
                throw ObjectIsNotAClassException("attempt to get attribute value from type that is not a class, type=" + type.name);

            Class & c = dynamic_cast<Class &>(type);

            if (!c.hasAttribute(name))
                throw UnknownAttributeException("unknown attribute name=" + name);

            // lazy add default values if they don't exist
            if (!hasValue(name)) {
                Type & attribType = c.getAttributeType(name);

                if (attribType.isBuiltIn()) {
                    if (attribType.equals(tString::instance()))
                        mAttributeValues[name] = tString::value("");
                    else if (attribType.equals(tCharacter::instance()))
                        mAttributeValues[name] = tCharacter::value(0);
                    else if (attribType.equals(tInteger::instance()))
                        mAttributeValues[name] = tInteger::value(0);
                    else if (attribType.equals(tFloat::instance()))
                        mAttributeValues[name] = tFloat::value(0.0);
                    else if (attribType.equals(tBoolean::instance()))
                        mAttributeValues[name] = tBoolean::value(false);
                    else if (attribType.equals(tNull::instance()))
                        mAttributeValues[name] = tNull::value();
                    else if (attribType.isSimpleArray())
                        throw std::exception(std::string("object must be allocated and set() before you cat get(). default array not allocated due to unknown size, type=" + attribType.name).c_str());
                    else if (attribType.isObjectArray())
                        throw std::exception(std::string("object must be allocated and set() before you cat get(). default array not allocated due to unknown size, type=" + attribType.name).c_str());
                    else
                        throw std::exception(std::string("unknown type encountered, type=" + attribType.name).c_str());
                } else {
                    mAttributeValues[name] = std::make_shared<Object>(attribType);
                }
            }

            return mAttributeValues[name];
        }

        std::string Object::asString(std::string value) {
            if (!type.equals(tString::instance()))
                throw TypeMismatchException("mismatched type while trying to set value as tString, type=" + type.name);

            mStringValue = value;

            return mStringValue;
        }

        char Object::asCharacter(char value) {
            if (!type.equals(tCharacter::instance()))
                throw TypeMismatchException("mismatched type while trying to set value as tCharacter, type=" + type.name);

            mCharacterValue = value;

            return mCharacterValue;
        }

        int Object::asInteger(int value) {
            if (!type.equals(tInteger::instance()))
                throw TypeMismatchException("mismatched type while trying to set value as tInteger, type=" + type.name);

            mIntegerValue = value;

            return mIntegerValue;
        }

        double Object::asFloat(double value) {
            if (!type.equals(tFloat::instance()))
                throw TypeMismatchException("mismatched type while trying to set value as tFloat, type=" + type.name);

            mFloatValue = value;

            return mFloatValue;
        }

        bool Object::asBoolean(bool value) {
            if (!type.equals(tBoolean::instance()))
                throw TypeMismatchException("mismatched type while trying to set value as tBoolean, type=" + type.name);

            mBooleanValue = value;

            return mBooleanValue;
        }

        std::string Object::asString() const {
            if (!type.equals(tString::instance()))
                throw TypeMismatchException("mismatched type while trying to get value as tString, type=" + type.name);

            return mStringValue;
        }

        char Object::asCharacter() const {
            if (!type.equals(tCharacter::instance()))
                throw TypeMismatchException("mismatched type while trying to get value as tCharacter, type=" + type.name);

            return mCharacterValue;
        }

        int Object::asInteger() const {
            if (!type.equals(tInteger::instance()))
                throw TypeMismatchException("mismatched type while trying to get value as tInteger, type=" + type.name);

            return mIntegerValue;
        }

        double Object::asFloat() const {
            if (!type.equals(tFloat::instance()))
                throw TypeMismatchException("mismatched type while trying to get value as tFloat, type=" + type.name);

            return mFloatValue;
        }

        bool Object::asBoolean() const {
            if (!type.equals(tBoolean::instance()))
                throw TypeMismatchException("mismatched type while trying to get value as tBoolean, type=" + type.name);

            return mBooleanValue;
        }

        bool Object::isNull() const {
            return type.equals(tNull::instance());
        }

        std::shared_ptr<Object> * Object::asArray(int length) {
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

        size_t Object::getArrayLength() const {
            return mArrayLength;
        }
        
        std::shared_ptr<Object> * Object::asArray()  const {
            if (mArrayLength <= 0)
                return nullptr;

            return mArrayValue;
        }        

        std::shared_ptr<Object> * Object::asObjectArray(int iLength) {
            if (iLength <= 0) {
                std::ostringstream oss;
                oss << iLength;
                throw std::invalid_argument(std::string("requested array length of ") + oss.str() + " is not valid");
            }

            deleteObjectArrayValue();
            mObjectArrayValue = new std::shared_ptr<Object>[iLength];
            mObjectArrayLength = iLength;

            return mObjectArrayValue;
        }

        size_t Object::getObjectArrayLength() const {
            return mObjectArrayLength;
        }

        std::shared_ptr<Object> * Object::asObjectArray() const {
            if (mObjectArrayLength <= 0)
                return nullptr;

            return mObjectArrayValue;
        }

    }

}
