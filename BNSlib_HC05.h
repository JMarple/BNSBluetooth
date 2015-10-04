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

#ifndef __BNSLIB_HC05_H__
#define __BNSLIB_HC05_H__

/**
 * Sends a string to a specified UART port.
 * Optionally, the size parameter (if provided) specifies how much data
 * to read from the data buffer. If not provided or -1, then data is read
 * until a null byte
 *
 * Returns the amount of data read from the "data" buffer
 */
int bnsSerialSend(const TUARTs uart, const char* data, int size = (-1));

/**
 * Reads data from the UART port into the buffer "data"
 * Reads at most `stringSize` bytes, and will stop reading after
 * `timeoutMilli` milliseconds without any new data.
 *
 * Returns the amount of bytes read into the buffer.
 */
int bnsSerialRead(const TUARTs uart, char* data, int stringSize, int timeoutMilli);

/**
 * This function will send the "AT\r\n" command, looking for an "OK" back from the
 * HC05 device.
 */
bool bnsATTestConnection(const TUARTs uart);

/**
 * Asks and prints the version number to the HC05 device to the debug stream.
 */
bool bnsATGetVersion(const TUARTs uart);

/**
 * Asks and prints the name of the HC05 device to the debug stream.
 */
bool bnsATGetName(const TUARTs uart);

/**
 * Sets the name of the HC05 device.
 */
bool bnsATSetName(const TUARTs uart, const string name);

/**
 * Asks and prints the uart baudrate of the HC05 device to the debug stream.
 */
bool bnsATGetBaudrate(const TUARTs uart);

/**
 * Sets the baudrate of the HC05 device.
 * Note: When parity = 0, no parity will be set.
 *       When parity = 1, odd partiy will be set.
 *       When parity = 2, even parity will be set.
 */
bool bnsATSetBaudrate(const TUARTs uart, int baudrate, int stopbits, int parity);

/**
 * Sets the PIN of the HC05
 */
bool bnsATSetPIN(const TUARTs uart, int pin);

/**
 * Sets the Password for the HC05
 */
bool bnsATSetPassword(const TUARTs uart, int pass);

#include "BNSlib_HC05.c"

#endif
