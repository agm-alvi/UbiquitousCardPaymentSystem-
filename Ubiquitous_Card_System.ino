#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include<stdlib.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 33, 35, 37}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define SS_PIN 53
#define RST_PIN 49
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
String lcdprnt = "Paid ";
int a_amount = 5000, b_amount = 5000, c_amount = 5000;
int sum = 0;
char A_card = "3F AD 4D 29";
char B_card = "BO 77 BB 25";
char C_card = "71 F3 3D 08";
MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class
void setup() {
  
  lcd.begin(16,2);
   Serial.begin(9600);
   SPI.begin();       // Init SPI bus
   mfrc522.PCD_Init(); // Init MFRC522
   lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("Enter Amount");
  Serial.begin(9600);
  delay(2000);
 
   //lcd.clear();
pinMode(8,OUTPUT);//5 volt
Start:
  lcd.clear();
 //please_pay();
lcd.print("Key Input");
  delay(2000);
  Serial.print("Key Input");
  char key = 'x';
  while(key!='D'){
     key = keypad.getKey();
  if (key != NO_KEY){
   // Serial.println(key);
    Serial.print(key);
    int am;
       switch(key){
      case '0' : am = 0; break;
      case '1' : am = 1; break;
      case '2' : am = 2; break;
      case '3' : am = 3; break;
      case '4' : am = 4; break;
      case '5' : am = 5; break;
      case '6' : am = 6; break;
      case '7' : am = 7; break;
      case '8' : am = 8; break;
      case '9' : am = 9; break;
      
      case 'A' : goto Start; break;
     // case 'B' : sum = (sum-am)/100; am =0; break;
      
      case 'C' : sum = 0; am = 0; break;
      case 'D' : goto ending; break;
      
      default :   break;
    }
 
    
    lcd.print(am);
    sum = (sum*10)+ am;
    }
  }
ending:
Serial.println();
Serial.print("Sum =  ");
Serial.print(sum);

lcd.clear();
lcd.print("Pay:");
lcd.print(sum);
lcd.print(" Taka");

lcd.setCursor(0,1);

lcd.println("Swipe Card");
delay(2000);   
}
void loop() {
  

/*if ( mfrc522.PICC_IsNewCardPresent())
    {
        if ( mfrc522.PICC_ReadCardSerial())
        {
           Serial.print("Tag UID:");
           for (byte i = 0; i < mfrc522.uid.size; i++) {
                  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                  Serial.print(mfrc522.uid.uidByte[i], HEX);
            }
          
            Serial.println();
            mfrc522.PICC_HaltA();
        }
}*/ 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    digitalWrite(8,HIGH);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  lcd.clear();
  digitalWrite(8,LOW);
  Serial.print("UID tag :");
  lcd.print("UID tag :");
  delay(2000);
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "3F AD 4D 29") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    a_amount -=sum;
    Serial.println(a_amount);
  lcd.clear();
  lcd.print(content);
  lcd.setCursor(0,1);
  lcdprnt = lcdprnt+sum;
  lcd.print(lcdprnt);
    delay(2000);
setup(); 
  }
  else if (content.substring(1) == "B0 77 BB 25" ) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    b_amount -=sum;
    Serial.println(b_amount);
  lcd.clear();
  lcd.print(content);
  lcd.setCursor(0,1);
  lcdprnt = lcdprnt+sum;
  lcd.print(lcdprnt);
    delay(2000);
setup();
}
 else if (content.substring(1) == "71 F3 3D 08") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    c_amount -=sum;
    Serial.println(c_amount);
  lcd.clear();
  lcd.print(content);
  lcd.setCursor(0,1);
  lcdprnt = lcdprnt+sum;
  lcd.print(lcdprnt);
    delay(2000);
setup();
  }
 else   {
    Serial.println(" Access denied");
    }

}
 
