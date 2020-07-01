//Interface Circuitry
#include <LiquidCrystal.h>
#include <Keypad.h>
#include<setjmp.h>
#include<EEPROM.h>
int C=261;
int d=294;
int e=329;
int f=349;
int g=392;
int a=440;
int b=493;
int c=523;
#define  B0  31
#define  C1  33
#define  CS1 35
#define  D1  37
#define  DS1 39
#define  E1  41
#define  F1  44
#define  FS1 46
#define  G1  49
#define  GS1 52
#define  A1  55
#define  AS1 58
#define  B1  62
#define  C2  65
#define  CS2 69
#define  D2  73
#define  DS2 78
#define  E2  82
#define  F2  87
#define  FS2 93
#define  G2  98
#define  GS2 104
#define  A2  110
#define  AS2 117
#define  B2  123
#define  C3  131
#define  CS3 139
#define  D3  147
#define  DS3 156
#define  E3  165
#define  F3  175
#define  FS3 185
#define  G3  196
#define  GS3 208
#define  A3  220
#define  AS3 233
#define  B3  247
#define  C4  262
#define  CS4 277
#define  D4  294
#define  DS4 311
#define  E4  330
#define  F4  349
#define  FS4 370
#define  G4  392
#define  GS4 415
#define  A4  440
#define  AS4 466
#define  B4  494
#define  C5  523
#define  CS5 554
#define  D5  587
#define  DS5 622
#define  E5  659
#define  F5  698
#define  FS5 740
#define  G5  784
#define  GS5 831
#define  A5  880
#define  AS5 932
#define  B5  988
#define  C6  1047
#define  CS6 1109
#define  D6  1175
#define  DS6 1245
#define  E6  1319
#define  F6  1397
#define  FS6 1480
#define  G6  1568
#define  GS6 1661
#define  A6  1760
#define  AS6 1865
#define  B6  1976
#define  C7  2093
#define  CS7 2217
#define  D7  2349
#define  DS7 2489
#define  E7  2637
#define  F7  2794
#define  FS7 2960
#define  G7  3136
#define  GS7 3322
#define  A7  3520
#define  AS7 3729
#define  B7  3951
#define  C8  4186
#define  CS8 4435
#define  D8  4699
#define  DS8 4978
const byte ROWS = 4;
const byte COLS = 4; 
int pass=0;
int ModeAval=0;
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 4, 5, 6, 7 };
byte colPins[COLS] = { 0, 1, 2, 3 }; 
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS ); 
LiquidCrystal lcd(14, 15, 19, 18, 17, 16);
long Num1,Num2,Number;
int i=0,k=0,arr[4];
char key,action;
int speakerPin=13;
int num;
jmp_buf buf;
void fre(int f,int d)
{
  tone(speakerPin,f);
  delay(d);
  noTone(speakerPin);
  key = kpd.getKey();
  num=key;
  if(num!=NO_KEY)
  {
    delay(500);
    longjmp(buf,1);
  }
}
void nofre(int d)
{
  noTone(speakerPin);
  delay(d);
  noTone(speakerPin);
}
void happyBday()
{
   fre(D6,125);
    fre(D6,125);
    fre(E6,250);
    fre(D6,250);
    fre(G6,250);
    fre(F6,500);
    fre(D6,125);
    fre(D6,125);
    fre(E6,250);
    fre(D6,250);
    fre(A6,250);
    fre(G6,500);
    fre(D6,125);
    fre(D6,125);
    fre(2034,250);
    fre(B7,250);
    fre(G6,250);
    fre(F6,250);
    fre(E6,500);
    fre(C6,125);
    fre(C6,125);
    fre(B7,250);
    fre(G6,250);
    fre(A6,250);
    fre(G6,500);
    nofre(500);
}
void rainsOfCastamere()
{
    fre(A4,500);
    fre(E5,250);
    fre(F5,250);
    fre(D5,1000);
    fre(F5,500);
    nofre(50);
    fre(F5,250);
    fre(E5,250);
    fre(A4,1000);
    nofre(50);
    fre(A4,500);
    fre(E5,250);
    fre(F5,250);
    fre(D5,1000);
    fre(F5,500);
    nofre(50);
    fre(F5,250);
    fre(E5,1000);
    fre(A4,500);
    fre(E5,250);
    fre(F5,250);
    fre(D5,1000);
    fre(A5,500);
    nofre(50);
    fre(A5,500);
    fre(G5,500);
    fre(D5,750);
    fre(G5,250);
    fre(F5,750);
    fre(D5,250);
    fre(A5,250);
    fre(G5,250);
    fre(E5,250);
    fre(F5,250);
    fre(D5,1000);
    nofre(500); 
}
void houseTargaryen()
{
   fre(D5,1000);
   nofre(50);
   fre(D5,500);
   nofre(50);
   fre(D5,500);
   nofre(50);
   fre(D5,250);
   fre(G5,250);
   fre(F5,2000);
   fre(C5,1000);
   nofre(50);
   fre(C5,500);
   nofre(50);
   fre(C5,500);
   nofre(50);
   fre(E5,2000);
   fre(A5,250);
   fre(C6,250);
   fre(A5,2000);
   nofre(100);
   fre(A5,250);
   fre(C6,250);
   fre(B5,2000);
   fre(A5,250);
   fre(D6,250);
   fre(CS6,2000);
   nofre(1000);
}
void houseStark()
{
    fre(C6,1000);
    fre(G6,1000);
    nofre(50);
    fre(G6,1000);
    fre(F6,500);
    fre(DS6,500);
    fre(G6,2000);
    fre(F6,1000);
    fre(G6,1000);
    fre(GS6,1000);
    fre(G6,500);
    fre(GS6,500);
    fre(G6,2000);
    fre(F6,1000);
    fre(DS6,1000);
    fre(C6,1000);
    fre(G6,1000);
    nofre(50);
    fre(G6,1000);
    fre(F6,500);
    fre(DS6,500);
    fre(G6,2000);
    fre(F6,1000);
    fre(G6,1000);
    fre(GS6,1000);
    fre(G6,500);
    fre(GS6,500);
    fre(G6,2000);
    fre(F6,1000);
    fre(DS6,1000);
    nofre(1000);
}
void kingsArrival()
{
    fre(D6,500);
    nofre(190);
    fre(D6,200);
    nofre(50);
    fre(D6,200);
    nofre(50);    
    fre(D6,200);
    nofre(50);    
    fre(D6,500);
    nofre(100);
    fre(D6,200);
    nofre(50);
    fre(E6,200);
    nofre(50);
    fre(F6,200);
    nofre(50);
    fre(D6,500);
    nofre(100);
    fre(D6,200);
    nofre(50);
    fre(D6,200);
    nofre(50);    
    fre(D6,200);
    nofre(50);    
    fre(D6,750);
    nofre(100);
    fre(D6,250);
    fre(E6,250);
    fre(F6,750);
    fre(G6,750);
    fre(E6,1000);
    fre(D6,250);
    fre(E6,250);
    fre(F6,750);
    fre(A6,750);
    fre(G6,250);
    fre(F6,250);
    nofre(50);
    fre(F6,250);
    fre(E6,250);
    fre(D6,500);
    nofre(500);
}
void setPass()
{
  if(Num1==35)
  {
      i--;
      lcd.setCursor(i, 1);
      lcd.print(" ");
      lcd.setCursor(i, 1);
      i--;
  }
  else
  {
    lcd.setCursor(i, 1);
    lcd.print(Num1-48);
    EEPROM.write(i,Num1-48);
  }
}
void ModeA()
{
    k=0;
    while(1)
    {
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,0);
      lcd.print("Enter old pass");
      i=0;
      while(i<4)
      {
        key = kpd.getKey();
        Num1=key; 
        if (Num1!=NO_KEY)
        {
          DetectButtons();
          i++; 
        }
      }
      i=0;
      delay(500);
      lcd.begin(16, 2);
      lcd.setCursor(0,0);
      if(arr[0]==EEPROM.read(0)&&arr[1]==EEPROM.read(1)&&arr[2]==EEPROM.read(2)&&arr[3]==EEPROM.read(3))
      {
        lcd.print("Enter new pass");
        pass=1;
        while(i<4)
        {
          key = kpd.getKey();
          Num1=key; 
          if (Num1!=NO_KEY)
          {
            setPass();
            i++; 
          }
        }
        delay(500);
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Password set");
        lcd.setCursor(0,1);
        lcd.print("                ");
        digitalWrite(8,HIGH);
        delay(1000);
        digitalWrite(8,LOW);
        i=0;
        pass=0;
        return ;
      }
      else
      {
        lcd.print("Access Denied");
        delay(1000);
        pass=0;
        k++;
        if(k>2)
        {
          lcd.setCursor(0,1);
          lcd.print("Try after ");
          k=0;
          for(int j=60; j>=0; j--)
          {
            lcd.setCursor(10,1);
            lcd.print(j);
            delay(1000);
            lcd.setCursor(10,1);
            lcd.print("     ");
          }
          lcd.setCursor(0,1);
          lcd.print("           ");
        }
     }
     if(pass==0)
     {
        lcd.setCursor(0,0);
        lcd.print("Enter password");
     }
   } 
}
void ModeB()
{
     lcd.setCursor(0,0);
     lcd.print("                ");
     lcd.setCursor(0,0);
     lcd.print("Music Mode");
     lcd.setCursor(0,1);
     lcd.print("                ");
     lcd.setCursor(0,1);
     key = kpd.getKey();
     num=key;
     while(num!=42)
     {
        key = kpd.getKey();
        num=key;
        if(num!=NO_KEY)
         {
            setjmp(buf);
            lcd.setCursor(0,1);
            lcd.print("                ");
            lcd.setCursor(0,1);
            if(num-48==2)
            {
              lcd.print("Rains Of Castemere");
              rainsOfCastamere();
            }
            else if(num-48==3)
            {
              lcd.setCursor(0,1);
              lcd.print("                ");
              lcd.setCursor(0,1);
              lcd.print("House Targaryen");
              houseTargaryen();
            }
            else if(num-48==5)
            {
              lcd.setCursor(0,1);
              lcd.print("                ");
              lcd.setCursor(0,1);
              lcd.print("House Stark");
              houseStark();
            }
            else if(num-48==6)
            {
              lcd.setCursor(0,1);
              lcd.print("                ");
              lcd.setCursor(0,1);
              lcd.print("King's Arrival");
              kingsArrival();
            }
            else if(num-48==8)
            {
              lcd.setCursor(0,1);
              lcd.print("                ");
              lcd.setCursor(0,1);
              lcd.print("Happy Bday");
              happyBday();
            }
            else if(num-48==9)
            {
              lcd.setCursor(0,1);
              lcd.print("                ");
              lcd.setCursor(0,1);
              lcd.print("No Song");
              noTone(speakerPin);
            }
            else if(num==68)
              return ;
       }
    }
}
void setup() 
{
     pinMode(speakerPin,OUTPUT);
     lcd.begin(16, 2);
     lcd.setCursor(0,0);
     lcd.print("Enter password");
     pinMode(8,OUTPUT);
     pinMode(9,OUTPUT);
     //EEPROM.write(0,0);
     //EEPROM.write(1,0);
     //EEPROM.write(2,0);
     //EEPROM.write(3,0);
}
void selectMode()
{
  if (Num1==65)
  {
     lcd.setCursor(0, 1);
     lcd.print("Mode A");
     delay(500);
     ModeAval=1;   
     ModeA();
  }
  else if (Num1==66)
  {
     lcd.setCursor(0, 1);
     lcd.print("Mode B");
     delay(500);
     
     ModeB();
  }
  else if(Num1==67)
  {
    lcd.setCursor(i, 1);
    lcd.print("Mode C");
  }
  if(ModeAval==0)
  {
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,0);
      lcd.print("Select Mode");
  }
}
void DetectButtons()
{ 
    if(Num1==35)
    {
      i--;
      lcd.setCursor(i, 1);
      lcd.print(" ");
      lcd.setCursor(i, 1);
      i--;
    }
    else
    {
      lcd.setCursor(i, 1);
      lcd.print(Num1-48);
      arr[i]=Num1-48;
    }
}
void loop() 
{
    key = kpd.getKey();
    Num1=key; 
    if (Num1!=NO_KEY&&pass==0)
    {
      DetectButtons();
      i++; 
    }
    if(Num1!=NO_KEY&&pass==1)
    {
      selectMode();
    }
    if(i>3)
    {
      i=0;
      delay(500);
      lcd.begin(16, 2);
      lcd.setCursor(0,0);
      if(arr[0]==EEPROM.read(0)&&arr[1]==EEPROM.read(1)&&arr[2]==EEPROM.read(2)&&arr[3]==EEPROM.read(3)&&ModeAval==0)
      {
        lcd.print("Access Granted");
        digitalWrite(8,HIGH);
        delay(1000);
        digitalWrite(8,LOW);
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Select Mode");
        pass=1;
     }
     else
     {
        lcd.print("Access Denied");
        digitalWrite(9,HIGH);
        delay(1000);
        digitalWrite(9,LOW);
        pass=0;
        k++;
        if(k>2)
        {
          digitalWrite(9,HIGH);
          lcd.setCursor(0,1);
          lcd.print("Try after ");
          k=0;
          for(int j=60; j>=0; j--)
          {
            lcd.setCursor(10,1);
            lcd.print(j);
            delay(1000);
            lcd.setCursor(10,1);
            lcd.print("     ");
          }
          lcd.setCursor(0,1);
          lcd.print("           ");
        }
        digitalWrite(9,LOW);
     }
     if(pass==0)
     {
        lcd.setCursor(0,0);
        lcd.print("Enter password");
     }
   }
   if(ModeAval==1)
   {
    
      lcd.setCursor(0,0);
      lcd.print("Enter password");
      ModeAval=0; 
   }
   delay(200);
}
