#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

// Connect RX/TX pins to the module (adjust as needed)
SoftwareSerial myVR(2, 3); // RX, TX

// Create VoiceRecognitionV3 object
VR myVR(myVR);

void setup()
{
    Serial.begin(115200); // Serial monitor for user interaction
    myVR.begin(9600);     // Serial communication with the module

    // Print a welcome message
    Serial.println("Elechouse Voice Recognition V3 Module");
    Serial.println("Enter your command:");
}

void loop()
{
    if (Serial.available())
    {                                              // Check for user input from serial monitor
        String cmd = Serial.readStringUntil('\n'); // Read entire line of input
        myVR.sendCmd(cmd.c_str());                 // Send command to the module

        delay(20); // Brief delay for processing

        // Handle module's response
        while (myVR.available())
        {
            Serial.write(myVR.read()); // Print module's response to serial monitor
        }
    }
}
