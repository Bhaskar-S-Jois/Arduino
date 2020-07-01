#include <LiquidCrystal.h>
#include <Keypad.h>
#include<setjmp.h>
#include<EEPROM.h>

#define  AS4 466
#define  D5  587
#define  C5  523
#define  G5  784
#define  F5  698
#define  A4  440
#define  F4  349
#define  G4  392
#define  A5  880
#define  AS5 932

jmp_buf buf;
const byte ROWS = 4;
const byte COLS = 4; 
int count=0;
int sfx=1,lgt=5;
int sensorPin = A0;
int led=10;
int alarmset=0,alarmtime=0;
int sensorValue=0;
int ModeAval=0;
int M=0;
int hc=0;
int Ahours = 12;
int Aminutes = 0;
int Aseconds = 0;
int m=0;
int alrm=0;
int sound=0;
int cur=0;
int hours=12;
int minutes=0;
int seconds=0;
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 4, 5, 6, 7 };
byte colPins[COLS] = { 0, 11, 2, 3 }; 
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS ); 
LiquidCrystal lcd(8, 15, 19, 18, 17, 16);
long int Num1,Num2,Number;
long long int i=0,k=0,arr[4];
char key,action;
unsigned long long start,Tstart;
unsigned long long limit=999;//limit=1000 , limit=998 based on trial and error
long long int num;
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
void DetectButtons()
{ 
    if(Num1==35)
    {
      i--;
      if(i>=4)
      {
        lcd.setCursor(i+2, 1);
        lcd.print(" ");
        lcd.setCursor(i+2, 1);
      }
      else if(i>=2)
      {
        lcd.setCursor(i+1, 1);
        lcd.print(" ");
        lcd.setCursor(i+1, 1);
      }
      else
      {
        lcd.setCursor(i, 1);
        lcd.print(" ");
        lcd.setCursor(i, 1);
      }
      i--;
    }
    else
    {
      if(i>=4)
      {
        lcd.setCursor(i+2, 1);
        lcd.print(Num1-48);
      }
      else if(i>=2)
      {
        lcd.setCursor(i+1, 1);
        lcd.print(Num1-48);
      }
      else
      {
        lcd.setCursor(i, 1);
        lcd.print(Num1-48);
      }
      arr[i]=Num1-48;
    }
}
void ModeA()
{
    while(1)
    {
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Set timer");
        lcd.setCursor(2,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print(":");
        lcd.setCursor(0,1);
        i=0;
        while(i<5)
        {
          key = kpd.getKey();
          Num1=key; 
          if (Num1!=NO_KEY)
          {
            if(Num1==48)
            {
              if(i>=4)
               {
                  lcd.setCursor(i+2, 1);
                  lcd.print("0");
               }
               else if(i>=2)
               {
                  lcd.setCursor(i+1, 1);
                  lcd.print("0");
                }
                else
                {
                  lcd.setCursor(i, 1);
                  lcd.print("0");
                }
                arr[i]=0;
                i++;
            }
            else 
            {
              DetectButtons();
              i++;
            }
          }
        }
        i=0;
        lcd.setCursor(0,0);
        EEPROM.write(0,arr[0]);
        EEPROM.write(1,arr[1]);
        EEPROM.write(2,arr[2]);
        EEPROM.write(3,arr[3]);
        EEPROM.write(4,arr[4]);
        EEPROM.write(5,arr[5]);
        int misec=(int)arr[4]*1;
        int sec = (int)arr[2]*10+(int)arr[3];
        int minutes = (int)arr[0]*10+(int)arr[1];
        int Minutes,Sec,Misec;
        delay(500);
        if(misec>99 || sec >59 || minutes>59)
        {
          lcd.setCursor(0,0);
          lcd.print("                ");
          lcd.setCursor(0,0);
          lcd.print("Invalid time");
          delay(1000);
          lcd.setCursor(0,0);
          lcd.print("                ");
          lcd.setCursor(0,1);
          return;
        }
        else
        {
          long long int total = minutes*60*10+sec*10+misec;
          lcd.setCursor(0,0);
          lcd.print("                ");
          lcd.setCursor(0,0);
          lcd.print("Timer set");
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("Press * to start");
          while(1)
          {
            key = kpd.getKey();
            Num1=key;
            if(Num1!=NO_KEY)
            {
              if(Num1=='*')
              { lcd.setCursor(0,0);
                lcd.print("                ");
                lcd.setCursor(0,0);
                lcd.print("Timer Running:");
                lcd.setCursor(0,1);
                lcd.print("                ");
                lcd.setCursor(0,1);
                for(i=total; i>=0;  i--)
                {
                  Minutes=i/600;
                  Sec=(i/10)%60;
                  Misec=i%10;
                  lcd.setCursor(0,1);
                  lcd.print("                ");
                  lcd.setCursor(0,1);
                  lcd.print(Minutes);
                  lcd.print(":");
                  lcd.print(Sec);
                  lcd.print(":");
                  lcd.print(Misec);
                  delay(93);
                }
                goto out;
              }
            }
          }
          out:
          tone(13,500);
          delay(500);
          noTone(13);
          delay(500);
          lcd.setCursor(0,0);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,0);
          lcd.print("Press * to goto ");
          lcd.setCursor(0,1);
          lcd.print("main menu");
          while(1)
          {
            key = kpd.getKey();
            Num1=key;
           if(Num1!=NO_KEY)
            {
              if(Num1=='*')
              {
                lcd.setCursor(0,0);
                lcd.print("                ");
                lcd.setCursor(0,1);
                lcd.print("                ");
                return;
              }
            }
          }
        }
    }
}
void ModeB()
{
  i=0;
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Stopwatch");
  lcd.setCursor(0,1);
  lcd.print("                ");
  
  while(1)
  {
     i++;
     lcd.setCursor(0,1);
     lcd.print("                ");
     int minutes=i/600;
     int sec=(i/10)%60;
     int misec=i%10;
     lcd.setCursor(0,1);
     lcd.print(minutes);
     lcd.print(":");
     lcd.print(sec);
     lcd.print(":");
     lcd.print(misec);
     delay(93);
     key = kpd.getKey();
     Num1=key;
     if(Num1!=NO_KEY)
     {
        if(Num1=='*')
        {
          tone(13,400);
          delay(1000);
          noTone(13);
          delay(4000);
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,0);
          lcd.print("                ");
          lcd.setCursor(0,0);
          lcd.print("Press * to exit");
          while(1)
          {
            key = kpd.getKey();
            Num1=key;
            if(Num1!=NO_KEY)
            {
              if(Num1=='*')
              {
                return;
              }
            }
          }
        }
     }
  }
}
void brand(int sec)
{
  sec=(sec%30)+1;
  lcd.setCursor(11,1);
  switch(sec)
  {
    case 1:lcd.print("Speed");break;
    case 2:lcd.print("peedB");break;
    case 3:lcd.print("eedBi");break;
    case 4:lcd.print("edBir");break;
    case 5:lcd.print("dBird");break;
    case 6:lcd.print("Bird_");break;
    case 7:lcd.print("ird_E");break;
    case 8:lcd.print("rd_El");break;
    case 9:lcd.print("d_Ele");break;
    case 10:lcd.print("_Elec");break;
    case 11:lcd.print("Elect");break;
    case 12:lcd.print("lectr");break;
    case 13:lcd.print("ectro");break;
    case 14:lcd.print("ctron");break;
    case 15:lcd.print("troni");break;
    case 16:lcd.print("ronic");break;
    case 17:lcd.print("onics");break;
    case 18:lcd.print("nics-");break;
    case 19:lcd.print("ics-D");break;
    case 20:lcd.print("cs-Di");break;
    case 21:lcd.print("s-Dig");break;
    case 22:lcd.print("-Digi");break;
    case 23:lcd.print("Digit");break;
    case 24:lcd.print("igita");break;
    case 25:lcd.print("gital");break;
    case 26:lcd.print("italC");break;
    case 27:lcd.print("talCl");break;
    case 28:lcd.print("alClo");break;
    case 29:lcd.print("lCloc");break;
    case 30:lcd.print("Clock");break;
  }
}
void updateTime()
{
           lcd.setCursor(0,1);
           lcd.print("        ");
           lcd.setCursor(0,1);
           lcd.print(hours);
           lcd.print(":");
           if(minutes<10)
              lcd.print("0");
           lcd.print(minutes);
           lcd.print(":");
           if(seconds<10)
              lcd.print("0");
           lcd.print(seconds);
           brand(seconds);
           if(M==0)
           {
              lcd.setCursor(8,1);
              lcd.print("AM");
           }
           else if(M==1)
           {
              lcd.setCursor(8,1);
              lcd.print("PM");
           }
           seconds++;
           if(seconds>59)
           {
            minutes++;
            seconds=0;
           }
           if(minutes>59)
           {
            hours++;
            if(hours==12)
            {
              if(M==0)
              {
                M=1;
                lcd.setCursor(8,1);
                lcd.print("PM");
              }
              else if(M==1)
              {
                M=0;
                lcd.setCursor(8,1);
                lcd.print("AM");
              }
            }
            if(hours==6 && M==1)
            {
              analogWrite(led,80);
              lgt=2;
            }
            if(hours==7 && M==1)
            {
              analogWrite(led,160);
              lgt=4;
            }
            if(hours==8 && M==1)
            {
              analogWrite(led,250);
              lgt=5;
            }

            if(hours==5 && M==0)
            {
              analogWrite(led,160);
              lgt=4;
            }
            if(hours==6 && M==0)
            {
              analogWrite(led,80);
              lgt=2;
              if(sfx==-1)
              {
                sfx=1;
                lcd.setCursor(13,0);
                lcd.print("ON ");
                
              }
            }
            if(hours==7 && M==0)
            {
              analogWrite(led,0);
              lgt=0;
            }
            if(hours==11 && M==1)
            {
              analogWrite(led,160);
              lgt=4;
            }
            if(hours==12 && M==0)
            {
              sfx=-1;
              lcd.setCursor(13,0);
              lcd.print("DND");
              analogWrite(led,80);
              lgt=2;
            }
            minutes=0;
            hc=0;
           }
           if(hours>12)
           {
            hours=1;
           }
           if(minutes==0)
           {
              if(hc<(hours)&&sfx==1)
              {
                tone(13,500);
                delay(200);
                noTone(13);
                hc++;
              }
              else if(hc<(hours))
              {
                noTone(13);
              }
              else
              {
                noTone(13);
              }
           }
           if(minutes==30)
           {
            if(seconds==1&&sfx==1)
            {
              tone(13,700);
              delay(500);
              noTone(13);
            }
            else
            {
              noTone(13);
            }
           }
}
void music(int ton,unsigned long long dly)
{
  Tstart=millis();
  if(ton==0)
    noTone(13);
  else
    tone(13,ton);
  int light=ton/4;
  analogWrite(led,light);
  while(millis()-Tstart<dly)
  {
    if(millis()-start>limit || start>millis())
    {
      //delay(12);
      start=millis();
      updateTime();
    }
    key = kpd.getKey();
    Num1=key;  
    if (Num1!=NO_KEY)
    {
      if(Num1==67)
      {
        sound=0;
        alrm=0;
        noTone(13);
        lcd.setCursor(10,1);
        lcd.print(" ");
        longjmp(buf,0);
      }
    }
  }
}
void ModeD(int mode)
{
   analogWrite(led,lgt*40);
   lcd.setCursor(0,0);
   lcd.print("                ");
   lcd.setCursor(0,1);
   lcd.print("                ");
   lcd.setCursor(0,0);
   if(mode==0)
   {
      mode=2;
      lcd.setCursor(0,0);
      lcd.print("               ");
      lcd.setCursor(0,0);
      lcd.print("Set H ");
      if(hours<10)
      {
        lcd.print("0");
        lcd.print(hours);
      }
      else
      {
        lcd.print(hours);
      }
      lcd.print(":");
      if(minutes<10)
      {
        lcd.print("0");
        lcd.print(minutes);
      }
      else
      {
         lcd.print(minutes);
      }
      lcd.print(":");
      if(seconds<10)
      {  
        lcd.print("0");
        lcd.print(seconds);
      }
      else
      {
        lcd.print(seconds);
      }
      if(M==0)
      {
        lcd.print("AM");
      }
      else
      {
        lcd.print("PM");
      }
      while(1)
      {
         key = kpd.getKey();
         Num1=key;
        if (Num1!=NO_KEY)
        {
             if(Num1=='#')
             {
               if(cur==0)
               {
                 hours=(hours%12)+1;
                 if(hours<10)
                 {
                    lcd.setCursor(6,0);
                    lcd.print("0");
                    lcd.print(hours);
                 }
                 else
                 {
                    lcd.setCursor(6,0);
                    lcd.print(hours);
                 }
               }
               else if(cur==1)
               {
                    minutes=(minutes+1)%60;
                    if(minutes<10)
                    {
                      lcd.setCursor(9,0);
                      lcd.print("0");
                      lcd.print(minutes);
                    }
                    else
                    {
                      lcd.setCursor(9,0);
                      lcd.print(minutes);
                    }
               }
               else if(cur==2)
               {
                    seconds=(seconds+1)%60;
                    if(seconds<10)
                    {
                      lcd.setCursor(12,0);
                      lcd.print("0");
                      lcd.print(seconds);
                    }
                    else
                    {
                      lcd.setCursor(12,0);
                      lcd.print(seconds);
                    }
                }
                else if(cur==3)
                {
                    if(M==0)
                    {
                      M=1;
                      lcd.setCursor(14,0);
                      lcd.print("PM");
                    }
                    else if(M==1)
                    {
                      M=0;
                      lcd.setCursor(14,0);
                      lcd.print("AM");
                    }
                }
             }
             if((Num1=='*'||Num1==68))
             {
                  cur=(cur+1)%4;
                  if(cur==0)
                  {
                    lcd.setCursor(4,0);
                    lcd.print("H");
                  }
                  else if(cur==1)
                  {
                    lcd.setCursor(4,0);
                    lcd.print("M");
                  }
                  else if(cur==2)
                  {
                    lcd.setCursor(4,0);
                    lcd.print("S");
                  }
                  else if(cur==3)
                  {
                    lcd.setCursor(4,0);
                    lcd.print("m");
                  }
              }
              if(Num1=='0')
              {
                  break;
              }
        }
      }
   }
   else if(mode==1)
   {
        mode=2;
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Set time");
        lcd.setCursor(2,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print(":");
        lcd.setCursor(0,1);
        i=-1;
        while(i<6)
        {
          key = kpd.getKey();
          Num1=key; 
          if (Num1!=NO_KEY)
          {
            if(Num1==48)
            {
              if(i>=4)
               {
                  lcd.setCursor(i+2, 1);
                  lcd.print("0");
               }
               else if(i>=2)
               {
                  lcd.setCursor(i+1, 1);
                  lcd.print("0");
                }
                else
                {
                  lcd.setCursor(i, 1);
                  lcd.print("0");
                }
                arr[i]=0;
                i++;
              }
             else if(Num1==67 && i==-1)
            {
                  lcd.setCursor(8, 1);
                  lcd.print("AM");
                  M=0;
                  i++;
            }
            else if(Num1==68 && i==-1)
            {
                  lcd.setCursor(8, 1);
                  lcd.print("PM");
                  M=1;
                  i++;
            }
            else 
            {
              DetectButtons();
              i++;
            }
          }
        }
        hours = (int)arr[0]*10+(int)arr[1];
        minutes = (int)arr[2]*10+(int)arr[3];
        seconds = (int)arr[4]*10+(int)arr[5];
        seconds=seconds-60;
        if(seconds<0)
          seconds=-seconds;
   }
   i=0;
   lcd.setCursor(0,0);
   lcd.print("                ");
   lcd.setCursor(0,0);
   lcd.print("LGT:");
   lcd.setCursor(9,0);
   lcd.print("SFX:ON ");
   lcd.setCursor(11,1);
   lcd.print("[SBE]");
   start=millis();
   while(1)
   {  
           Serial.println("Start:");
           Serial.println(millis());
           updateTime();
           lcd.setCursor(4,0);
           lcd.print("    ");
           lcd.setCursor(4,0);
           lcd.print(lgt*20);
           lcd.print("%");
           analogWrite(led,lgt*40);
           while(1)
           {
              key = kpd.getKey();
              Num1=key; 
              if (Num1!=NO_KEY)
              {
                  if(Num1=='0')
                  {
                   lcd.setCursor(0,0);
                   lcd.print("                ");
                   lcd.setCursor(0,1);
                    lcd.print("                ");
                    lcd.setCursor(0,0);
                   Serial.println("Intruder");
                    return ;
                  }
                  
                 if((Num1=='*'||Num1==68)&&alarmset==0&&sound==0)
                 {
                    lcd.setCursor(13,0);
                    if(sfx==1)
                    {
                     sfx=0;
                      lcd.print("OFF");
                    }
                    else if(sfx==0)
                    {
                      sfx=1;
                      lcd.print("ON ");
                    }
                 }
                 if((Num1=='*'||Num1==68)&&sound==1)
                     {
                      sound=0;
                      alrm=0;
                      noTone(13);
                      lcd.setCursor(10,1);
                      lcd.print(" ");
                     }
                 if(Num1=='#'&&alarmset==0)
                 {
                    lgt=(lgt+1)%6;
                    lcd.setCursor(4,0);
                    lcd.print("    ");
                    lcd.setCursor(4,0);
                    lcd.print(lgt*20);
                    lcd.print("%");
                    if(lgt*20==100)
                       analogWrite(led,250);                      
                    else
                      analogWrite(led,lgt*40);
                 }
                 if(Num1==67&&alarmset==0)
                 { 
                  alarmset=1;
                  lcd.setCursor(0,0);
                  lcd.print("               ");
                  lcd.setCursor(0,0);
                  lcd.print("Set ");
                  if(cur==0)
                  {
                    lcd.print("H");
                  }
                  else if(cur==1)
                  {
                    lcd.print("M");
                  }
                  else if(cur==2)
                  {
                    lcd.print("S");
                  }
                  else if(cur==3)
                  {
                    lcd.print("m");
                  }
                  lcd.print(" ");
                  if(Ahours<10)
                  {
                    lcd.print("0");
                    lcd.print(Ahours);
                  }
                  else
                  {
                    lcd.print(Ahours);
                  }
                  lcd.print(":");
                  if(Aminutes<10)
                  {
                    lcd.print("0");
                    lcd.print(Aminutes);
                  }
                  else
                  {
                    lcd.print(Aminutes);
                  }
                  lcd.print(":");
                  if(Aseconds<10)
                  {  
                    lcd.print("0");
                    lcd.print(Aseconds);
                  }
                  else
                  {
                    lcd.print(Aseconds);
                  }
                  if(m==0)
                  {
                    lcd.print("AM");
                  }
                  else
                  {
                    lcd.print("PM");
                  }
                 }
                 while(alarmset==1)
                 {
                    key = kpd.getKey();
                    Num1=key; 
                    if (Num1!=NO_KEY)
                    {
                      if(Num1=='#'&&alarmset==1)
                      {
                      if(cur==0)
                      {
                        Ahours=(Ahours%12)+1;
                        if(Ahours<10)
                        {
                          lcd.setCursor(6,0);
                          lcd.print("0");
                          lcd.print(Ahours);
                        }
                        else
                        {
                          lcd.setCursor(6,0);
                          lcd.print(Ahours);
                        }
                      }
                      else if(cur==1)
                      {
                        Aminutes=(Aminutes+1)%60;
                        if(Aminutes<10)
                        {
                          lcd.setCursor(9,0);
                          lcd.print("0");
                          lcd.print(Aminutes);
                        }
                        else
                        {
                          lcd.setCursor(9,0);
                          lcd.print(Aminutes);
                        }
                      }
                      else if(cur==2)
                      {
                        Aseconds=(Aseconds+1)%60;
                        if(Aseconds<10)
                        {
                          lcd.setCursor(12,0);
                          lcd.print("0");
                          lcd.print(Aseconds);
                        }
                        else
                        {
                          lcd.setCursor(12,0);
                          lcd.print(Aseconds);
                        }
                      }
                      else if(cur==3)
                      {
                        if(m==0)
                        {
                          m=1;
                          lcd.setCursor(14,0);
                          lcd.print("PM");
                        }
                        else if(m==1)
                        {
                          m=0;
                          lcd.setCursor(14,0);
                          lcd.print("AM");
                        }
                      }
                     }
                     if((Num1=='*'||Num1==68)&&alarmset==1&&sound==0)
                     {
                      cur=(cur+1)%4;
                      if(cur==0)
                      {
                        lcd.setCursor(4,0);
                        lcd.print("H");
                      }
                      else if(cur==1)
                      {
                        lcd.setCursor(4,0);
                        lcd.print("M");
                      }
                      else if(cur==2)
                      {
                        lcd.setCursor(4,0);
                        lcd.print("S");
                      }
                     else if(cur==3)
                      {
                        lcd.setCursor(4,0);
                        lcd.print("m");
                      }
                     }
                     if((Num1==67||Num1==66)&&alarmset==1)
                     {
                      alarmset=0;
                      if(Num1==67)
                      {
                        lcd.setCursor(10,1);
                        lcd.print("*");
                        alrm=1;
                     }
                      else if(Num1==66)
                      {
                        lcd.setCursor(10,1);
                        lcd.print(" ");
                        alrm=0;
                      }
                      lcd.setCursor(0,0);
                     lcd.print("                ");
                      lcd.setCursor(0,0);
                      lcd.print("LGT:");
                      lcd.print(lgt*20);
                      lcd.print("%");
                      lcd.setCursor(9,0);
                      lcd.print("SFX:");
                        if(sfx==0)
                        {
                          lcd.print("OFF");
                        }
                        else if(sfx==1)
                        {
                         lcd.print("ON ");
                        }
                        else if(sfx==-1){
                          lcd.print("DND");
                        }
                      break;
                     }
                    }
                    if(millis()-start>limit || start>millis())
                    { 
                        //delay(12);
                        start=millis();
                        updateTime();
                    }  
                }
              }
               if(alrm==1)
                  {
                    if(Ahours==hours&&Aminutes==minutes&&Aseconds==seconds&&M==m)
                    {
                      tone(13,500);
                      sound=1;
                      hc=13;
                      Serial.println("Alarm");
                    }
                  }
                  while(sound==1)
                  {
                    for(int loop=0; loop<4; loop++)
                    {
                      music(AS4,200);
                      music(0,50);
                    }
                    for(int loop=0; loop<4; loop++)
                    {
                      music(D5,200);
                      music(0,50);
                    }
                    for(int loop=0; loop<4; loop++)
                    {
                      music(C5,200);
                      music(0,50);
                    }
                    for(int loop=0; loop<4; loop++)
                    {
                      music(F5,200);
                      music(0,50);
                    }

                    for(int loop=0; loop<12; loop++)
                    {
                      music(G5,200);
                      music(0,50);
                    }
                    music(C5,200);  music(0,50);
                    music(AS4,200); music(0,50);
                    music(A4,200);  music(0,50);
                    music(F4,200);  music(0,50);

                    for(int loop=0; loop<2; loop++)
                    {
                      music(G4,200);  music(0,50);
                      music(0,200); music(0,50);
                      music(G4,200);  music(0,50);
                      music(D5,200);  music(0,50);
                    
                      music(C5,200);  music(0,50);
                      music(0,200); music(0,50);
                      music(AS4,200); music(0,50);
                      music(0,200); music(0,50);
                    
                      music(A4,200);  music(0,50);
                      music(0,200); music(0,50);
                      music(A4,200);  music(0,50);
                      music(A4,200);  music(0,50);
                    
                      music(C5,200);  music(0,50);
                      music(0,200); music(0,50);
                      music(AS4,200); music(0,50);
                      music(A4,200);  music(0,50);

                      for(int innerloop=0;  innerloop<2;  innerloop++)
                      {
                        music(G4,200);  music(0,50);
                        music(0,200);  music(0,50);
                        music(G4,200);  music(0,50);
                        music(AS5,200); music(0,50);
                    
                        music(A5,200); music(0,50);
                        music(AS5,200); music(0,50);
                        music(A5,200); music(0,50);
                        music(AS5,200); music(0,50);
                      }
                    }

                  }
                  setjmp(buf);

                  if(millis()-start>limit || start>millis())
                  {
                    //adjustments based on trial and error of millis() versus real time millisecond
                    //delay(12);
                    //Serial.println("loop:");
                    //delayMicroseconds(475);
                    //if(seconds%20==0)
                   // {
                    //  delay(1);
                    //}
                    //if(seconds==0)
                    //{
                      //delay(10);
                    //}
                    start=millis();
                    break;
                  }
                  Serial.println("Stop:");
                  Serial.println(millis());
          }
      }
}
void selectMode()
{
  if (Num1==67)
  {
     lcd.setCursor(0, 1);
     lcd.print("Timer Mode");
     delay(500);   
     ModeA();
  }
  else if(Num1==66)
  {
    lcd.setCursor(0, 0);
    lcd.print("Stop watch mode");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Starts in : ");
    lcd.setCursor(12,1);
    lcd.print("3");
    tone(13,300);
    delay(500);
    noTone(13);
    delay(500);
    lcd.setCursor(12,1);
    lcd.print("2");
    tone(13,300);
    delay(500);
    noTone(13);
    delay(500);
    lcd.setCursor(12,1);
    lcd.print("1");
    tone(13,300);
    delay(500);
    noTone(13);
    delay(500);
    lcd.setCursor(12,1);
    lcd.print("0");
    tone(13,700);
    delay(500);
    noTone(13);
    delay(500);
    ModeB();
  }
  else if(Num1==68)
  {
    lcd.setCursor(0, 1);
     lcd.print("Set Time");
     delay(500);  
        int mode;
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("D:keypad mode");
        lcd.setCursor(0,1);
        lcd.print("#:watch mode");
        while(1)
        {
          
          key = kpd.getKey();
          Num1=key; 
          if (Num1!=NO_KEY)
          {
            if(Num1==68)
            {
              mode=1;
              break;
            }
            else if(Num1=='#')
            {
              mode=0;
              break;
            }
          }
        }
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,0); 
        ModeD(mode);
  }
}

void setup() {
     lcd.begin(16, 2);
     lcd.setCursor(0,0);
     pinMode(8,OUTPUT);
     pinMode(9,OUTPUT);
     pinMode(12,OUTPUT);
     pinMode(10,OUTPUT);
     Serial.begin(9600);
}

void loop() {
  if(count==0)
    {
      lcd.setCursor(0,0);
      lcd.print("SpeedBird");
      lcd.setCursor(0,1);
      lcd.print("Electronics");
      delay(2000);
      count++;
    }
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Soft RTOS model");
    lcd.setCursor(0,1);
    lcd.print("Select Mode");
    key = kpd.getKey();
    Num1=key; 
    if(Num1!=NO_KEY)
    {
      selectMode();
    }
   delay(200);    
}
