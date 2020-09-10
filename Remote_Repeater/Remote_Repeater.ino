//pins
#define IRpin_PIN      PIND
#define startButton 13
#define sensorPower 12
#define IREmitter 8
#define IRSensor 2
#define Buzzer 9

//debug
#define debug 0


//mode
//0 is not continuous: need to press button before for everytime you want signal to repeat
//1 is continous: button is not used
#define continuous 1

unsigned long startms;
unsigned long endms;

int triggered_count = 0;

//conditionals
bool pressed = false;
bool on = false;
bool receivingSignal = false;
bool start = false;

//structs
struct utime_pair
{
  uint16_t high;
  uint16_t low;
};

//signal values
#define signalLength 100
utime_pair IRSignal[signalLength];
int IRSignalCount = 0;
#define MAXPULSE 65000
//int multiplier = 1;
//float readWriteSpeed = multiplier * 0.025974025974026; //in milliseconds
#define RESOLUTION 20

//functions
//void(* resetFunc) (void) = 0;
void copySignal();
void repeatSignal();
void turnOnSensorPower();
void turnOffSensorPower();
void printSignal();
void turnOnEmitter();
void turnOffEmitter();
void clearIRSignal();
//check if Serial is connected
bool receivingUpdate(); // error in name, supposed to be receiving serial signal to check if connection available
//see if Serial wants Arduino On or Off
int checkDesiredStatus(); //0 is not receiving any serial input, 1 is on, 2 is off

//sources
//https://www.instructables.com/id/How-to-control-your-TV-with-an-Arduino/
//http://www.arrl.org/files/file/ETP/TV%20remote%20decoder%20kit%20ver%202_2.pdf
//https://www.instructables.com/id/Control-LED-Using-Serial-Monitor/

void setup() {

  Serial.begin(115200);
  

  //intializing pins
  pinMode(startButton, INPUT);
  pinMode(IRSensor, INPUT);
  pinMode(sensorPower, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  
  pinMode(IREmitter,OUTPUT);
  digitalWrite(IREmitter, LOW);

  //setting up IRSensor signal reading
  if (continuous)
  {
    //when running with serial inputs from computer
    if (receivingUpdate()) //if statement only for testing Serial with debugging on----------------------
    {
    turnOffSensorPower();
    receivingSignal = false;
    on = false;
    start = true;
    }
    
    //when testing without serial connection
    if (debug && false) //false only for testing Serial with debugging on------------------------------
    {
      turnOnSensorPower();
      receivingSignal = true;
      on = true;
      delay(3);
    }

    
    
  }
  else
  {
    turnOffSensorPower();
  }
  
  if (debug)
  {
    Serial.println("start");
  }
}


void loop() {

  if (!continuous)
  {
    //Turn On
    //start pressed
    if (!digitalRead(startButton) && !pressed)
    {
      pressed = true;
      if (debug)
      {
        Serial.println("Pressed");
      }
    }
    //start depressed
    if (pressed && digitalRead(startButton))
    {
      pressed = false;
      if (debug)
      {
        Serial.println("Depressed");
      }
      on = true;
      if (debug)
      {
        Serial.println("On: " + String(on));
      }
      turnOnSensorPower();
      receivingSignal = true;
    }
  }
  
  if (receivingUpdate())
  {
    int check = checkDesiredStatus();
    if (check == 1)
    {
      if (debug)
      {
        Serial.println("Turning on.");
      }
      
      turnOnSensorPower();
      receivingSignal = true;
      on = true;
      start = true;
      
      delay(3);
    }
    if (check == 2)
    {
      if (debug)
      {
        Serial.println("Turning off.");
      }
      
      turnOffSensorPower();
      receivingSignal = false;
      on = false;
      start = false;
      
      delay(3);
    }
    if (check == 3)
    {
      triggered_count = -100;
      tone(Buzzer,0, 100000);
    }
    
  }
  if (start && !(IRpin_PIN & _BV(IRSensor)))
  {
    start = false;
  }

  
  if (on && receivingSignal && !start)
  {
    if (IRSignalCount < signalLength)
    {
      if (IRSignalCount == 0)
      {
        if (debug)
        {
          Serial.println("Copying Signal");
        }
        startms = millis();
      }


      
      copySignal();
      


      if (on && (IRSignalCount == signalLength || receivingSignal == false))
      {
        //if signal has not yet ended, keep waiting
        bool cycle = true;
        while (cycle)
        {
          cycle = false;
          if (debug)
          {
            Serial.println("Not yet finished.");
          }
          int k;
          for (k = 0; k < MAXPULSE/10; ++k)
          {
            if (!(IRpin_PIN & _BV(IRSensor)))
            {
              cycle = true;
            }
            delayMicroseconds(RESOLUTION);
          }
        }

        
        if (debug)
        {
          Serial.println("Values Check: " + String(IRSignalCount));
          endms = millis();
          Serial.println("Copied signal in " + String(endms - startms) + "ms");
        }
        if (debug)
        {
          printSignal();
        }
        receivingSignal = false;
        turnOffSensorPower();

        Serial.println("Triggered");
        triggered_count++;
        if (triggered_count > 2)
        {
          tone(Buzzer,440,100000);
          ++triggered_count;
        }
        
      }
    }  
    
  }

  if (on && !receivingSignal)
  {
    if (debug)
    {
      Serial.println("Repeating Signal");
    }
    delay(4000);
    repeatSignal();

    if (debug)
    {
      Serial.println("Finished Repeating");
    }
    
    //reset
    on = false;
    clearIRSignal();
    IRSignalCount = 0;

    if (continuous)
    {
      turnOnSensorPower();
      receivingSignal = true;
      on = true;
    }
    
    //if want to repeat receiving and sending signals
//    on = true;
//    receivingSignal = true;
    
    
  }

//  // if device turned on, and IRsensor is triggered or continuously reading signal
//  if (on && !digitalRead(IRSensor))
//  {
//    if (debug && !receivingSignal)
//    {
//      startms = millis();
//    }
//    
//    copySignal();
//
//    //repeat signal then turn off signal processing
//    if (debug)
//    {
//      endms = millis();
//      printSignal();
//      Serial.println("copying time in ms: " + String(endms-startms));
//    }
//    
//    //turnOffSensorPower();
//    
//    delay(6000);
//    if (debug)
//    {
//      startms = millis();
//    }
//    repeatSignal();
//    if (debug)
//    {
//      endms = millis();
//      Serial.println("emitting time in ms: " + String(endms-startms));
//      Serial.println(entered);
//    }
//    delay(1000);
//
//    //turn off signal processing until button pressed or reset
//    turnOnSensorPower();
//    receivingSignal = false;
//    on = false;
//    pressed = false;
//    IRSignalCount = 0;
//    if (debug)
//    {
//      Serial.println("Off");
//    }
//  
//    
//  }

  
  
}



void copySignal()
{
  cli();
  uint16_t tempHigh = 0;
  uint16_t tempLow = 0;
  while (IRpin_PIN & (1 << IRSensor))
  {
    tempHigh++;
    delayMicroseconds(RESOLUTION);
    if ((tempHigh >= MAXPULSE) && (IRSignalCount != 0))
    {
      receivingSignal = false;
      return;
    }

    //check if client's commands didn't change
    if (IRSignalCount == 0 && receivingUpdate() && checkDesiredStatus() == 2)
    {
      if (debug)
      {
        Serial.println("receivingUpdate1: " + String(receivingUpdate()));
        Serial.println("Turning off.");
      }
      turnOffSensorPower();
      receivingSignal = false;
      on = false;
      clearIRSignal();
      IRSignalCount = 0;    
      delay(3);
      return;
    }
  }

  //HIGH and LOW are opposite from signal and no signal
  IRSignal[IRSignalCount].low = tempHigh;
  while (!(IRpin_PIN & _BV(IRSensor)))
  {
    tempLow++;
    delayMicroseconds(RESOLUTION);
    if ((tempLow >= MAXPULSE) && (IRSignalCount != 0))
    {
      receivingSignal = false;
      return;
    }

    //check if client's commands didn't change
//    if (receivingUpdate() && checkDesiredStatus() == 2)
//    {
//      if (debug)
//      {
//        Serial.println("receivingUpdate2: " + String(receivingUpdate()));
//        Serial.println("Turning off.");
//      }
//      turnOffSensorPower();
//      receivingSignal = false;
//      on = false;
//      clearIRSignal();
//      IRSignalCount = 0;
//      delay(3);
//      return;
//    }
  }
  
  //HIGH and LOW are opposite from signal and no signal
  IRSignal[IRSignalCount].high = tempLow;
  IRSignalCount++;
  sei();

}

void repeatSignal()
{

  cli();
  startms = millis();
  int i;
  for (i = 0; i < IRSignalCount; ++i)
  {
    delayMicroseconds(IRSignal[i].low * RESOLUTION);

    
    int j;
    for (j = IRSignal[i].high * RESOLUTION; j > 0; j-=26)
    {
      digitalWrite(IREmitter, HIGH);
      delayMicroseconds(10);
      digitalWrite(IREmitter, LOW);
      delayMicroseconds(10);
    }
    
  }
  endms = millis();
  if (debug)
  {
    Serial.println("Sent in " + String(endms - startms) + "ms");    
  }

  sei();

  
//  //test sensor input
//  //IRSignalCount = 0;
//  float temp = readWriteSpeed * .5 * 1000;
//  int i;
//  for (i = 0; i < signalLength; ++i)
//  {
//    digitalWrite(IREmitter, IRSignal[i]);
//    delayMicroseconds(temp);
//    digitalWrite(IREmitter, 0);
//    delayMicroseconds(temp);
//    
//  }
//  if (debug)
//  {
//    //test sensor input
//    //printSignal();
//    
//    //Serial.println();
//  }
}

void turnOnSensorPower()
{
  digitalWrite(sensorPower, HIGH);
}

void turnOffSensorPower()
{
  digitalWrite(sensorPower, LOW);
}

void printSignal()
{
  Serial.println("\nPrinting Signal");
  int i;
  for (i = 0; i < IRSignalCount; ++i)
  {
    Serial.println("high: " + String(IRSignal[i].high * RESOLUTION) + \
    " usec    low: " + String(IRSignal[i].low * RESOLUTION));
  }
  Serial.println();
}

void clearIRSignal()
{
  int i;
  for (i = 0; i < signalLength; ++i)
  {
    IRSignal[i].high = 0;
    IRSignal[i].low = 0;
  }
}


bool receivingUpdate()
{
  return int(Serial.available());
}

int checkDesiredStatus()
{
  char temp = Serial.read();
  char str[2];
  str[0] = temp;
  Serial.println(String(int(str[0])));
  return int(str[0]);  
}
