#include "MIDIUSB.h"

int POTENT = A1;
int BUTTON_PIN = 0;

void setup() {
   Serial.begin(9600);
   while (!Serial); // Wait for Serial to initialize
   Serial.println("Ready!");
   pinMode(POTENT, INPUT);
   attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),buttonTriggered, RISING);
}

//MIDI Program Change (PC) # to enable/disable plugin?
// Shall we create a CLI? ex: map PIN to function

void loop() {
  // read in potent
  int potentValue = analogRead(POTENT); //Range 1 - 1023 (2^10)
  Serial.println(potentValue);

  // Rather than putting this in a loop, probably create an interrupt that triggers on change
  // Revision: idk if there exist interrupts for analog pins
  /*
  First param is event type (0x0B for control, 0x0C for pc)
  Second param is event type | channel number (idk if this matters)
  Third param is control number (0-119), prob 0x5B (91)?
  Fourth param is control val (0-127): use potentValue
  */
  midiEventPacket_t reverbAmount = {0x0B, 0xB0 | 0, 0x5B, potentValue};

  //Midi cc 91 (0x5B): Usually controls reverb send amount
  MidiUSB.sendMIDI(reverbAmount);
  delay(500);

}

void buttonTriggered() {
  Serial.println("Button Pressed");
  delay(100);
}

/*//https://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/

const int footswitch = 1; 
bool on; 
int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
//higher velocity usually makes MIDI instruments louder

int noteON = 144;//144 = 10010000 in binary, note on command
int noteOFF = 128;//128 = 10000000 in binary, note off command


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  while (!Serial); 
  pinMode(footswitch, INPUT);
  on = false;


}

void loop() {
  // put your main code here, to run repeatedly:
  //check for button input 
  if (digitalRead(footswitch)) {
    on = !on; 
  }
  for (int note=50;note<70;note++) {//from note 50 (D3) to note 69 (A4)
    MIDImessage(noteON, note, velocity);//turn note on
    delay(300);//hold note for 300ms
    MIDImessage(noteOFF, note, velocity);//turn note off
    delay(200);//wait 200ms until triggering next note
  }

}

void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}
*/
