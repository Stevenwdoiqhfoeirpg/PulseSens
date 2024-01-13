#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>
#include <Wire.h>
#include "rgb_lcd.h"
//#include <SPI.h>
//#include <WiFiNINA.h>
//#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

//char ssid[] = "VM0372824";    //  your network SSID (name) 
//char pass[] = "vsQkspmyvbDfxr3y";   // your network password
//int keyIndex = 0;            // your network key Index number (needed only for WEP)
//WiFiClient  client;

//unsigned long myChannelNumber = 2399796;
//const char * myWriteAPIKey = "YBZ1PLLXHF58WQEP";

//const int updateThingSpeakInterval = 20 * 1000; // 20 second interval at which to update ThingSpeak

const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PULSE_INPUT = A0;
const int PULSE_BLINK = LED_BUILTIN;
const int PULSE_FADE = 5;
const int THRESHOLD = 550;   
byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

PulseSensorPlayground pulseSensor;
rgb_lcd lcd;

void setup() {
  Serial.begin(115200);
 //while (!Serial) {
   // ; // wait for serial port to connect. Needed for Leonardo native USB port only
  // check for the WiFi module:
 // if (WiFi.status() == WL_NO_MODULE) {
  //  Serial.println("Communication with WiFi module failed!");
    // don't continue
    //while (true);
  //}
//   String fv = WiFi.firmwareVersion();
  //if (fv != "1.0.0") {
    //Serial.println("Please upgrade the firmware");
  //}
  //ThingSpeak.begin(client);  //Initialize ThingSpeak
  
  // Configure the PulseSensor manager.
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);
  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);
  // Skip the first SAMPLES_PER_SERIAL_SAMPLE in the loop().
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
  // reading for the PulseSensor signal.
  if (!pulseSensor.begin()) {
    for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(PULSE_BLINK, LOW);
      delay(50); Serial.println('!');
      digitalWrite(PULSE_BLINK, HIGH);
      delay(50);
    }
  }
  lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("BPM: ");
}
void loop() {
  // Connect or reconnect to WiFi
//  if(WiFi.status() != WL_CONNECTED){
  //  Serial.print("Attempting to connect to SSID: ");
    //Serial.println("VM0372824");
    //while(WiFi.status() != WL_CONNECTED){
      //WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      //Serial.print(".");   
    //} 
    //Serial.println("\nConnected.");
  if(pulseSensor.sawNewSample()) {
    if (--samplesUntilReport == (byte) 0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

      pulseSensor.outputSample();

      if (pulseSensor.sawStartOfBeat()) {
        pulseSensor.outputBeat();
      }
      // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of bpm:
    lcd.print(analogRead(0)/10);

    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  //int x = ThingSpeak.writeField(myChannelNumber, 0, "BPM", myWriteAPIKey);
  //if(x == 200){
    //Serial.println("Channel update successful.");
 // }
  //else{
   // Serial.println("Problem updating channel. HTTP error code " + String(x));
 // }
    delay(50);
    }
  }
}