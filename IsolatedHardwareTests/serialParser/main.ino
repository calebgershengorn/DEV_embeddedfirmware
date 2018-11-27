int count;

void setup() {
  Serial.begin(115200);
  count = 0;

  Serial.println("Beginning");
}

void loop() {
  
  Serial.print(millis());
  Serial.print('\t');
  Serial.print(count);
  Serial.println();

  count++;
  if (count>100){
    Serial.println("done");
    count = 0;
  }
  delay(100);

} // Loop