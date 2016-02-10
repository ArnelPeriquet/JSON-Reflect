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

namespace webo {

	namespace modeling {

		class ObjectIsNotAClassException : public std::exception {
		public:
			ObjectIsNotAClassException(std::string msg)
				: std::exception(msg.c_str()) {}
		};

		class UnknownAttributeException : public std::exception {
		public:
			UnknownAttributeException(std::string msg)
				: std::exception(msg.c_str()) {}
		};

		class TypeMismatchException : public std::exception {
		public:
			TypeMismatchException(std::string msg)
				: std::exception(msg.c_str()) {}
		};

		class UnsupportedPrimitiveType : public std::exception {
		public:
			UnsupportedPrimitiveType(std::string msg)
				: std::exception(msg.c_str()) {}
		};

        class ClassNotFoundException : public std::exception {
        public:
            ClassNotFoundException(std::string msg)
                : std::exception(msg.c_str()) {}
        };

        class NameCollisionException : public std::exception {
        public:
            NameCollisionException(std::string msg)
                : std::exception(msg.c_str()) {}
        };
	}

}
