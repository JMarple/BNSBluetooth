// ------------------------------------------------------------------------
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// The author can be contacted by email at jmarple@umass.edu
//
// ------------------------------------------------------------------------

#pragma systemFile

// Sends data to the specified uart port.
// Returns the amount of data read from the "data" buffer
int bnsSerialSend(const TUARTs uart, const char* data, int size)
{
	int characterCounter = 0;

	// Keep sending data until the next character is set to 0 (end of string).
	while((size > -1) ? (characterCounter < size)
		              : (*data != 0))
	{
	  sendChar(uart, *data);
	  data++;
	  characterCounter++;
	}

	return characterCounter;
}

// Reads data from a specified uart port, saving it to the string "data"
// stringSize: read at most this much data
// timeoutMillis: stop trying to read data after this long
// Returns the amount of data read into the "data" buffer
int bnsSerialRead(const TUARTs uart, char* data, int stringSize, int timeoutMilli)
{
	long startTime = nPgmTime;
	int characterCounter = 0;

	for (int i = 0; i < stringSize; i++)
		data[i] = 0;

	while (nPgmTime - startTime < timeoutMilli && characterCounter < stringSize)
	{
		short d = getChar(uart);

		if (d != -1)
		{
			*data = d;
			startTime = nPgmTime;
			characterCounter++;
			data++;
		}
	}
	return characterCounter;
}

// A generic method for sending and recieving AT commands, communicating this data to the user.
bool __bnsATCmd(const TUARTs uart, const string introMsg, const string cmd, const string errorMsg, const string goodMsg)
{
	char stringBuffer[100];
	writeDebugStreamLine(introMsg);

	bnsSerialSend(uart, cmd);
	bnsSerialRead(uart, stringBuffer, 100, 1000);

	if (stringBuffer[0] == 0)
	{
		writeDebugStreamLine(errorMsg);
		return false;
	}
	else
	{
	  writeDebugStream(goodMsg);
	  writeDebugStreamLine(stringBuffer);
	  return true;
	}
}

// Prints "OK" if there is a good connection.
bool bnsATTestConnection(const TUARTs uart)
{
	return __bnsATCmd(uart,
		"Testing Device Connection ...",
		"AT\r\n",
		"No AT Connection!",
		" > AT Connection = ");
}

// Prints the version number to the debug stream.
bool bnsATGetVersion(const TUARTs uart)
{
	return __bnsATCmd(uart,
		"Asking device for version number...",
		"AT+VERSION?\r\n",
		"Error!",
		" > AT Version = ");
}

// Prints the name to the debug stream.
bool bnsATGetName(const TUARTs uart)
{
	return __bnsATCmd(uart,
		"Asking device for name...",
		"AT+NAME?\r\n",
		"Error!",
		" > AT Name = ");
}

// Sets the name of the HC05 module.
bool bnsATSetName(const TUARTs uart, const string name)
{
	string strName;
	stringFormat(strName, "AT+NAME=%s\r\n", name);

	string strIntro = "Setting Name to ";
	strcat(strIntro, name);

	return __bnsATCmd(uart,
		strIntro,
		strName,
		"Error!",
		" > AT Name Status = ");
}

// Prints the baudrate currently set on the HC05 module.
bool bnsATGetBaudrate(const TUARTs uart)
{
	return __bnsATCmd(uart,
	  "Asking device for uart baudrate...",
	  "AT+UART?\r\n",
		"Error!",
		" > AT UART Baudrate = ");
}

// Sets the baudrate for the HC05 module.
bool bnsATSetBaudrate(const TUARTs uart, int baudrate, int stopbits, int parity)
{
	string strBaud;
	stringFormat(strBaud, "AT+UART=%d,%d,%d\r\n", baudrate, stopbits, parity);

	string strBaudrate;
	stringFormat(strBaudrate, "%d...", baudrate);

	string strIntro = "Setting baud = ";
	strcat(strIntro, strBaudrate);

	return __bnsATCmd(uart,
	  strIntro,
		strBaud,
		"Error!",
		" > AT Baudrate Status = ");
}

// Sets the baudrate for the HC05 module.
bool bnsATSetPIN(const TUARTs uart, int pin)
{
	string strPin;
	stringFormat(strPin, "AT+PIN=%d\r\n", pin);

	return __bnsATCmd(uart,
	  "Setting PIN...",
		strPin,
		"Error!",
		" > AT Pin = ");
}

// Sets the baudrate for the HC05 module.
bool bnsATSetPassword(const TUARTs uart, int pass)
{
	string strPass;
	stringFormat(strPass, "AT+PSWD=%d\r\n", pass);

	return __bnsATCmd(uart,
	  "Setting PIN...",
		strPass,
		"Error!",
		" > AT Pin = ");
}

// Prints the role of this HC05 (1 = master, 0 = slave.
bool bnsATGetRole(const TUARTs uart)
{
	return __bnsATCmd(uart,
		"Asking device role...",
		"AT+ROLE?\r\n",
		"Error!",
		" > AT Role = ");
}

// Prints the role of this HC05 (1 = master, 0 = slave.
bool bnsATReset(const TUARTs uart)
{
	return __bnsATCmd(uart,
		"Reseting...",
		"AT+RESET?\r\n",
		"Error!",
		" > AT Reset = ");
}

void bnsDebugStream(char* str, float option1 = (-1), float option2 = (-1), float option3 = (-1))
{
  string sendingStr;
  stringFormat(sendingStr, str, option1, option2, option3);

  bnsSerialSend(UART1, (char*)&sendingStr);
}

void bnsDebugStreamLine(char* str, float option1 = (-1), float option2 = (-1), float option3 = (-1))
{
  string sendingStr;
  stringFormat(sendingStr, str, option1, option2, option3);

  bnsSerialSend(UART1, (char*)&sendingStr);
  bnsSerialSend(UART1, "\n");
}
