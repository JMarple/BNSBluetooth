# BNS Bluetooth Library for RobotC

Includes:
  * Functions and examples for sending and recieving commands over UART
  * AT Commands for reprogramming HC05 bluetooth modules.  
  
Connecting a HC05 to a Vex Cortex is not difficult at all.  
The HC05 module commonly found online can be powered from a 5V source, and the TX/RX pins run at 3.3V, so no conversion is necessary from the Cortex to the module.
For reprogramming it, connect the "key" pin to 5V (Disclaimer: this could potentionally damage your device as it's not made to run at 5V.  Use a voltage divider  down to 3.3V if you want to be safe). 

Functions Cheatsheet: 
 * bnsSerialSend(UART1, "Hello Vex!"); // Sends a string over UART1
 * bnsSerialRead(UART1, someString, 100, 1000); // Reads a string over UART1 without a 1second timeout
 * bnsATTestConnection(UART1); // Returns true if there is a connection between the cortex and HC05 over UART1
 * bnsATGetName(UART1); // Prints the name of the HC05 module to the debug stream
 * bnsATSetName(UART1, "Team BNS"); // Sets the name of the HC05 module which.
 * ... and more AT commmands. 
