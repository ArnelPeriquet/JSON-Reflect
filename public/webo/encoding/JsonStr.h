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

	namespace encoding {

		class ENCODING_API JsonStr {
		public:
			JsonStr(std::string inputStr);

			std::string operator()();

		private:
			std::string mJsonStr;
		};

	}

}
