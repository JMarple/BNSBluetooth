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

/**
 * Sends a string to a specified UART port.
 */
void bnsSerialSend(const TUARTs uart, const char* data);

/**
 * Reads data from the UART port.  After the last character, this function will wait
 * the amount of milliseconds specified by timeoutMilli to ensure no data is missed.
 */
void bnsSerialRead(const TUARTs uart, char* data, int stringSize, int timeoutMilli);

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

#include "BNSlib_HC05.c"
