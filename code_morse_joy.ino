#include<LiquidCrystal.h>
#include <string.h> 
#include <ezButton.h>

#define joyX A0
#define joyY A1
#define btn 2
LiquidCrystal lcd(12,11,10,9,8,7);
ezButton button(btn);

String lettercheck="";
String fullword="";
String result="";
int size=0;
int size_word;
int input_mode;
String encryptword;
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  Serial.println("Choose The Input Mode :\n");
  Serial.println("1. Input Code morse through joystick.\n");
  Serial.println("2. Input word through serial monitor.\n");

  while(!Serial.available()){
      Serial.print('.');
      delay(500);
   }
   // chose the mode .
   int a = Serial.parseInt();
   switch(a){
      case 1:
          input_mode=1;
          Serial.println(input_mode);
         break;
      case 2: 
         input_mode=2;
   

         break;
      default:
         Serial.println("Value outside 1,2");
         break;
   }

}
void loop() {
  int btnValue = 0;
  button.loop();
  btnValue=button.getState();
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
// launch mode depending on the input_mode given by the user.
  switch(input_mode){
      case 1:
ModeJoyStick(btnValue,xValue,yValue);

         break;

      case 2:

        Serial.print("Enter Your Word\n");
        while(Serial.available()==0){

        }
        encryptword=Serial.readString();
         Serial.println(encryptword);
         ModeInput(encryptword);
         delay(2000);
         break;

      default:
         Serial.println("Value outside 1,2");
         break;
   }

}







// function that check the word with the matching morse code signification

char check_letter(String checkWord) {
  if (checkWord == ".") {
    return 'E';
  } else if (checkWord == "..") {
    return 'I';
  } else if (checkWord == "-") {
    return 'T';
  } else if (checkWord == "...") {
    return 'S';
  } else if (checkWord == ".-") {
    return 'A';
  } else if (checkWord == "-.") {
    return 'N';
  } else if (checkWord == "....") {
    return 'H';
  } else if (checkWord == "..-") {
    return 'U';
  } else if (checkWord == ".-.") {
    return 'R';
  } else if (checkWord == "-..") {
    return 'D';
  } else if (checkWord == "--") {
    return 'M';
  } else if (checkWord == ".--") {
    return 'W';
  } else if (checkWord == "--.") {
    return 'G';
  } else if (checkWord == "...-") {
    return 'V';
  } else if (checkWord == ".-..") {
    return 'L';
  } else if (checkWord == "..-.") {
    return 'F';
  } else if (checkWord == "-...") {
    return 'B';
  } else if (checkWord == "-.-") {
    return 'K';
  } else if (checkWord == "---") {
    return 'O';
  } else if (checkWord == ".--.") {
    return 'P';
  } else if (checkWord == "-..-") {
    return 'X';
  } else if (checkWord == "-.-.") {
    return 'C';
  } else if (checkWord == "--..") {
    return 'Z';
  } else if (checkWord == ".---") {
    return 'J';
  } else if (checkWord == "-.--") {
    return 'Y';
  } else if (checkWord == "--.-") {
    return 'Q';
  } else {
    return '_';
  }
}

void ModeJoyStick(bool btnValue,int xValue,int yValue){
  if (!btnValue==HIGH) {
    lcd.clear();
    lcd.print("Result:");
    result=check_letter(lettercheck);
    if(result!='_'){
      fullword+=result;
      //Serial.print(fullword);
     lcd.setCursor(0,1);
     lcd.print(fullword);
     delay(200);
     
    }else{
      lcd.print("error try again.");
      delay(200);
      lcd.clear();
      lettercheck="";
      fullword="";
    }
     
     lettercheck="";
    delay(200);
    lcd.clear();
    
    // TODO do something here
  }else{
if(xValue <512 && yValue >512){
    lcd.print(".");
     lettercheck += ".";
    //size++;  
    delay(200);
  
  } if (xValue>512 && yValue>512 ){
    lcd.print("-");
    lettercheck += "-";
     //size++;
    delay(200);
    //lcd.clear();
  }
if(xValue <512 && yValue <512){
    lcd.print("reset");
    //empty_array(inputed_letter);
    lettercheck="";
    fullword="";
    delay(200);
    lcd.clear();
  } if (xValue>512 && yValue<512 ){
    lcd.print(" ");
     lettercheck="";
    //size=0;
    delay(200);
  }
  }


}



void ModeInput(String ch){

 int len = ch.length();
  String result="";
  
  for(int i=0;i<len;i++){
    String temp=ModeSerial(ch[i]);
    result += temp;
  }

    lcd.print(result);
}


 String ModeSerial(char ch) {
 String temp="";

  if (ch == 'A' || ch == 'a') {
    temp=".-";
   return temp;
   
    //(" ");
  }
  else if (ch == 'B' || ch == 'b')
  {
    temp="-...";
   return temp;
    //(" ");
  }
  else if (ch == 'C' || ch == 'c')
  {
  temp="-.-.";
   return temp;
    //(" ");
  }
  else if (ch == 'D' || ch == 'd')
  {
 temp ="	-..";
   return temp;
    //(" ");
  }
  else if (ch == 'E' || ch == 'e')
  {
temp=".";
   return temp;
    //(" ");
  }
  else if (ch == 'f' || ch == 'f')
  {temp="..-.";
   return temp;
 
    //(" ");
  }
  else if (ch == 'G' || ch == 'g')
  {
   temp="--.";
   return temp;
    //(" ");
  }
  else if (ch == 'H' || ch == 'h')
  {
 temp="....";
   return temp;
    //(" ");
  }
  else if (ch == 'I' || ch == 'i')
  {
temp="..";
   return temp;
    //(" ");
  }
  else if (ch == 'J' || ch == 'j')
  {temp=".---";
   return temp;
 
    //(" ");
  }
  else if (ch == 'K' || ch == 'k')
  {
  temp="-.-";
   return temp;
    //(" ");
  }
  else if (ch == 'L' || ch == 'l')
  {
temp=".-..";
   return temp;
    //(" ");
  }
  else if (ch == 'M' || ch == 'm')
  {
temp="--";
   return temp;
    //(" ");
  }
  else if (ch == 'N' || ch == 'n')
  {
 temp="-.";
   return temp;
    //(" ");
  }
  else if (ch == 'O' || ch == 'o')
  {
temp="---";
   return temp;
    //(" ");
  }
  else if (ch == 'P' || ch == 'p')
  {
temp=".--.";
   return temp;
    //(" ");
  }
  else if (ch == 'Q' || ch == 'q')
  {
    temp="--.-";
   return temp;
    //(" ");
  }
  else if (ch == 'R' || ch == 'r')
  {
 temp=".-.";
   return temp;
    //(" ");
  }
  else if (ch == 'S' || ch == 's')
  {
   temp="...";
   return temp;
    //(" ");
  }
  else if (ch == 'T' || ch == 't')
  {
   temp="-";
   return temp;
    //(" ");
  }
  else if (ch == 'U' || ch == 'u')
  {
  temp="..-";
   return temp;
    //(" ");
  }
  else if (ch == 'V' || ch == 'v')
  {
 temp="...-";
   return temp;
    //(" ");
  }
  else if (ch == 'W' || ch == 'w')
  {
   temp=".--";
   return temp;
    //(" ");
  }
  else if (ch == 'X' || ch == 'x')
  {
   temp="-..-";
   return temp;
    //(" ");
  }
  else if (ch == 'Y' || ch == 'y')
  {
  temp="-.--";
   return temp;
    //(" ");
  }
  else if (ch == 'Z' || ch == 'z')
  {
 temp="--..";
   return temp;
    //(" ");
  }
  else if (ch == ' ') {
    Serial.print("/ ");
  }
  else if (ch == '\n') {
    Serial.println("");
  }
  else {
    Serial.println("Unknown Character!");
  }

}
