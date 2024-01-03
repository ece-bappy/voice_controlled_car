#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

// Pin assignments (adjust as needed)
const int VR_RX = 2;
const int VR_TX = 3;
const int motor1Pin1 = 4; // Motor 1 control pins
const int motor1Pin2 = 5;
const int motor2Pin1 = 6; // Motor 2 control pins
const int motor2Pin2 = 7;

// Create VoiceRecognitionV3 object
SoftwareSerial myVR(VR_RX, VR_TX);
VR myVR(myVR);

void setup()
{
    Serial.begin(115200); // Serial monitor for debugging
    myVR.begin(9600);     // Serial communication with the module

    // Set motor control pins as outputs
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);

    // Load trained commands (adjust indices if needed)
    myVR.load(0); // "Forward"
    myVR.load(1); // "Backwards"
    myVR.load(2); // "Left"
    myVR.load(3); // "Right"
}

void loop()
{
    if (myVR.recognize())
    {                                   // Check if a command is recognized
        int command = myVR.getResult(); // Get the recognized command index

        switch (command)
        {
        case 0: // "Forward"
            forward();
            break;
        case 1: // "Backwards"
            backwards();
            break;
        case 2: // "Left"
            left();
            break;
        case 3: // "Right"
            right();
            break;
        default:
            Serial.println("Unknown command");
        }
    }
}

// Motor control functions (adjust logic based on your H-Bridge driver)
void forward()
{
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void backwards()
{
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void left()
{
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW); // Stop motor 2
}

void right()
{
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); // Stop motor 1
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}
