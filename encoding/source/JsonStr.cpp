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
#include <ctype.h>
#include "webo/encoding/JsonStr.h"


namespace webo {

	namespace encoding {

		JsonStr::JsonStr(std::string inputStr) {
			std::ostringstream oss;
			char lastChar = ' ';

			for (std::size_t i = 0; i < inputStr.length(); i++) {
				while (isspace(inputStr[i])) {
					i++;

					if (i >= inputStr.length())
						goto outer;
				}

				if (inputStr[i] == ':')
					oss << '"';

				if ((lastChar != '}' && lastChar != ']' && lastChar != ':') && (inputStr[i] == '}' || inputStr[i] == ']' || inputStr[i] == ','))
					oss << '"';

				if ((lastChar == ':' || lastChar == ',') && inputStr[i] != '{' && inputStr[i] != '[')
					oss << '"';

				oss << inputStr[i];

				if (inputStr[i] == '{')
					oss << '"';

				lastChar = inputStr[i];
			}
		outer:

			mJsonStr = oss.str();
		}

		std::string JsonStr::operator()() {
			return mJsonStr;
		}

	}

}
