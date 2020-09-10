

int IRSensor = 12;    
bool code[1500];
int clen = 0;    
bool first = false;

void printIntArray(bool* toPrint, int len)
{
  int i;
  for (i = 0; i < len; ++i)
  {
    Serial.print(toPrint[i]);
  }
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  pinMode(IRSensor, INPUT);
  Serial.println("start");
}
 
void loop() 
{
  if (!digitalRead(IRSensor) || first)
  {
    code[clen++] = !digitalRead(IRSensor);
    first = true;
  }
  if (clen == 1499)
  {
    printIntArray(code, clen);
    exit(0);
  }
  delay(1);
}
