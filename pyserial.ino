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



//void loop() {
//  if (Serial.available() > 0)
//  {
//    int x_mid, y_mid;
//    if (Serial.read() == 'X')
//    {
//      x_mid = Serial.parseInt();  // read center x-coordinate
//      if (Serial.read() == 'Y')
//        y_mid = Serial.parseInt(); // read center y-coordinate
//    }
//    /* adjust the servo within the squared region if the coordinates
//        is outside it
//    */
////    if (x_mid > width / 2 + 30)
////      xpos += angle;
////    if (x_mid < width / 2 - 30)
////      xpos -= angle;
////    if (y_mid < height / 2 + 30)
////      ypos -= angle;
////    if (y_mid > height / 2 - 30)
////      ypos += angle;
//
//
//    // if the servo degree is outside its range
////    if (xpos >= 180)
////      xpos = 180;
////    else if (xpos <= 0)
////      xpos = 0;
////    if (ypos >= 180)
////      ypos = 180;
////    else if (ypos <= 0)
////      ypos = 0;
////
////    x.write(xpos);
////    y.write(ypos);
//
//      if(x_mid + y_mid == 0){
//        digitalWrite(red, HIGH);
//      }
//      else{
//        digitalWrite(yellow, HIGH);
//      }
//
//    // used for testing
//    //Serial.print("\t");
//    // Serial.print(x_mid);
//    // Serial.print("\t");
//    // Serial.println(y_mid);
//  }
//}
