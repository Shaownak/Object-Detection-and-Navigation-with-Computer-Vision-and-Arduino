const int red = 3;
const int yellow = 2;

void setup() {
  Serial.begin(9600);
//  Serial.setTimeout(1);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
}

void loop() {
  if (Serial.available()>0){
    int x, y;
    if(Serial.read() == 'X'){
      x = Serial.parseInt();
    }
    if(Serial.read() == 'Y'){
      y = Serial.parseInt();
    }
    Serial.read();
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print("\n");
    if(x>330){
      digitalWrite(red, HIGH);
      digitalWrite(yellow, LOW);
    }
    else if(x<330){
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);
    }
    else{
      digitalWrite(red, HIGH);
      digitalWrite(yellow, HIGH);
    }
  }
}
