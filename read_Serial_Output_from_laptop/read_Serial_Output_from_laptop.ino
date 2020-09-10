
int value;

void setup() {
  Serial.begin(115200);
  pinMode(9,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    
    char data = Serial.read();
    char str[2];
    str[0] = data;
    str[1] = '\0';
    Serial.println(String(int(str[0])) + "Triggered");

  }
}
