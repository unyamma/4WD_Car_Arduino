/*
* 2021y 05m 01d 11:40 am
* Project: First 4WD remote car
* Schematic: Mixed
* Program part: Spafuji
* Device: Arduino //! \/ Important parts \/!
* ----All in Readme.md
* If smthing didn't work before contact me please try to change version of IRemote library
*/

#define DECODE_NEC 1 // I forget what is it but pls don't delete this string

#include <IRremote.h> // !library for IR remote control!

int IR_RECEIVE_PIN = 11; // Output pin (Arduino Uno r3 Sensor Shield) for IR receiver
#define In1 2// Wire from Sensor Shield (2nd signal) to "In1" L298N Stepper Motor Driver
#define In2 3// Wire from Sensor Shield (3nd signal) to "In2" L298N Stepper Motor Driver
#define In3 4// Wire from Sensor Shield (4nd signal) to "In3" L298N Stepper Motor Driver
#define In4 5// Wire from Sensor Shield (5nd signal) to "In4" L298N Stepper Motor Driver

unsigned long irr = 0x00;//variable for saving the IR device output //!If you change variable for stopping below you must change here!

void setup() { // Setup func (Running once)
    Serial.begin(115200);//begining of serial monitor (Tool in arduino like debug console)
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);// Init IRemote library

    Serial.print(F("Ready to receive IR signals at pin ")); // Alert to serial monitor of initing of IRemote
    Serial.println(IR_RECEIVE_PIN); // Print to SM*
    //pinMode(EnA, OUTPUT);
    //pinMode(EnB, OUTPUT);
    digitalWrite(In1, LOW);//-------------------
    digitalWrite(In2, LOW);//Setting all motors
    digitalWrite(In3, LOW);//to low (off motors)
    digitalWrite(In4, LOW);//-------------------
    //analogWrite(EnB, 128);
    //analogWrite(EnA, 128);
}

void loop() { // Running allways but after start function
  if (IrReceiver.decode()) { // If we get signal from IR remote
  
      // Print a short summary of received data
      IrReceiver.printIRResultShort(&Serial);
      if (IrReceiver.decodedIRData.protocol == UNKNOWN) { //uknown protocols in some reasons can didn't work or work rarely
          // We have an unknown protocol here, print more info
          IrReceiver.printIRResultRawFormatted(&Serial, true); // print result (where?serial is?true) 
      }
      Serial.println(); // print to SM* empty line
  
      /*
       * //!!!Important!!! Enable receiving of the next value,
       * since receiving has stopped after the end of the current received data packet.
       */
      IrReceiver.resume(); // Enable receiving of the next value
  
      /*
       * Finally, check the received data and perform actions according to the received command
       */
      irr = IrReceiver.decodedIRData.command; // saving result of catching IR signal
      
  }
  if (irr == 0x18) { // !Important 0x18 code I saw on MY IR device any other device can show other code for "up arrow"!
    digitalWrite(In1, LOW); //A+ 0
    digitalWrite(In2, HIGH);//A- 1
    digitalWrite(In3, HIGH);//B+ 1
    digitalWrite(In4, LOW); //B- 0 ---- Wheels A backwards, Wheels B forward ---- Turn left
    irr = 0x00; // Set code for stop button  !If You change stop code below you must change here!
    }
  if (irr = 0x4E) { // !Important 0x4E code didn't checked, and in real life you device have other code for "" button!
    digitalWrite(In1, HIGH);//A+ 1
    digitalWrite(In2, LOW); //B- 0
    digitalWrite(In3, LOW); //B+ 0
    digitalWrite(In4, HIGH);//B- 1 ---- Wheels A FWD, B BCK ---- Turn left
    irr = 0x00; // Set code for stop button  !If You change stop code below you must change here!
  }
  if (irr = 0x27) { // !Important 0x27 code didn't checked, and in real life you device have other code for "" button!
    digitalWrite(In1, HIGH);//A+ 1
    digitalWrite(In2, LOW); //A- 0
    digitalWrite(In3, HIGH);//B+ 1
    digitalWrite(In4, LOW); //B- 0 ---- A FWD, B FWD ---- Go forward
    irr = 0x00; // Set code for stop button  !If You change stop code below you must change here!
  }
  if (irr = 0x00) { // !Important 0x00 code I saw on MY IR device any other device can show other code for "OK" button!
    digitalWrite(In1, LOW); //A+ 0
    digitalWrite(In2, HIGH);//A- 1
    digitalWrite(In3, LOW); //B+ 0
    digitalWrite(In4, HIGH);//B- 1 ---- A&B BCK ---- GO backwards
  }
  /*
  digitalWrite(In1, LOW);// ---------
  digitalWrite(In2, LOW);//Stopping motors
  digitalWrite(In3, LOW);//cuz no signal received
  digitalWrite(In4, LOW);// ---------*/

}

//*1 - SM - Serial Monitor
//*2 - bcuz - bcause - because
