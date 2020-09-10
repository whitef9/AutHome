// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin =  8  ;    // LED connected to digital pin 13
 
// The setup() method runs once, when the sketch starts
 
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);  
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);    
 
  Serial.begin(9600);
}
 
void loop()                     
{
  Serial.println("Sending IR signal");
 
  SendChannelUpCode();
 
  delay(10000);  // wait twenty seconds (20 seconds * 1000 milliseconds)
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
 
void SendChannelUpCode() {
  // This is the code for the CHANNEL + for the downstairs TV COMCAST
  
  delayMicroseconds(59620);
  pulseIR(260);
  delayMicroseconds(1900);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1940);
  pulseIR(200);
  delayMicroseconds(1920);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1940);
  pulseIR(180);
  delayMicroseconds(860);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1900);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(47560);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(260);
  delayMicroseconds(800);
  pulseIR(260);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(260);
  delayMicroseconds(1900);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(1960);
  pulseIR(200);
  delayMicroseconds(1940);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(45400);
  pulseIR(240);
  delayMicroseconds(1940);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1940);
  pulseIR(200);
  delayMicroseconds(1940);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(1940);
  pulseIR(180);
  delayMicroseconds(840);
  pulseIR(260);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(47560);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(260);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1940);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(1960);
  pulseIR(180);
  delayMicroseconds(1940);
  pulseIR(220);
  delayMicroseconds(840);
  pulseIR(240);
  delayMicroseconds(1900);
  pulseIR(240);
  delayMicroseconds(45380);
  pulseIR(240);
  delayMicroseconds(1940);
  pulseIR(200);
  delayMicroseconds(820);
  pulseIR(260);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(240);
  delayMicroseconds(1900);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1900);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(260);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(820);
  pulseIR(240);
  delayMicroseconds(1920);
  pulseIR(200);
  delayMicroseconds(840);
  pulseIR(240);

  
  


  
}
