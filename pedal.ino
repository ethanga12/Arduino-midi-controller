//https://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/

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
