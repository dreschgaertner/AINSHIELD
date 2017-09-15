//more info AINSHIELD and EXPANSION-KIT
//https://www.tindie.com/products/AislerHQ/the-ultimate-arduino-uno-expansion-kit/
//  =================================================
//  A I N S H I E L D    A N A L O G U E - I N
//  =================================================
//  Additional analogue Input PIN's for
//  Arduino Uno, Mega, Due...
//  AINSHIELD : MULTIPLEX using 74HC4051
//  Library   : SPI
//  SCADA     : SerialComInstruments  Version 4.1.0.0
//              © Software from U.Maassen
//  http://www.serialcominstruments.com/download.php
//  =================================================
//  G L O B A L   S E T T I N G S
//  AINSHIELD
    #include <SPI.h>
    String thisDevice = "UNO1-AINSHIELD1";
    unsigned int t0 = 0;//---------------------------Cicle Time Start
    unsigned int t1 = 0;//---------------------------Cicle Time
    int synClock = digitalRead(13);//----------------SCK, Clock SPI
    int bit0 =0;//-----------------------------------Bit for Steering Bus MUX (S0)
    int bit1 =0;//-----------------------------------Bit for Steering Bus MUX (S1)
    int bit2 =0;//-----------------------------------Bit for Steering Bus MUX (S2)    
    int sigNo = 0;//---------------------------------Signal Number (0...7)
    int inAn0[8];//----------------------------------input Analogue No. 0, Signal 0 bis 7
    int inAn1[8];//----------------------------------input Analogue No. 1, Signal 0 bis 7
    int inAn2[8];//----------------------------------input Analogue No. 2, Signal 0 bis 7
    int inAn3[8];//----------------------------------input Analogue No. 3, Signal 0 bis 7
//  =================================================
//  S E T U P   
    void setup()
    {
    AINsetup();  
    Serial.begin(57600);//---------------------------Scada seriell
    }
//  =================================================    
//  M A I N    P R O G R A M
//  =================================================     
    void loop()
    {
    AIN();//-----------------------------------------Function
    SCADA_SER();//-----------------------------------Function
    }
//  ================================================= 
//  F U N C T I O N   A I N S H I E L D
//  =================================================
    void AIN()
    {
    t0 = micros();//-----------------------------Start Cycle Time  
    if(synClock =1)
    sigNo = sigNo+1;
    if(sigNo > 7)
    sigNo = 0;
    bit0= bitRead(sigNo, 0);
    digitalWrite(3, bit0);//---------------------Set Bit Steering Bus MUX S0
    bit1= bitRead(sigNo, 1);
    digitalWrite(4, bit1);//---------------------Set Bit Steering Bus MUX S1
    bit2= bitRead(sigNo, 2);
    digitalWrite(5, bit2);//---------------------Set Bit Steering Bus MUX S2
    inAn0[sigNo]=analogRead(0);//----------------Set Signals 0...7 to variables
    inAn1[sigNo]=analogRead(1);//----------------Set Signals 0...7 to variables
    inAn2[sigNo]=analogRead(2);//----------------Set Signals 0...7 to variables
    inAn3[sigNo]=analogRead(3);//----------------Set Signals 0...7 to variables
    t1 = micros()-t0;//--------------------------Cicle Time  
   }
//  =================================================
//  S E T U P   A I N S H I E L D
//  =================================================
    void AINsetup()
    {
    pinMode(3, OUTPUT);//----------------------------Set Steering Bus MUX, PIN3 to Output
    pinMode(4, OUTPUT);//----------------------------Set Steering Bus MUX, PIN4 to Output
    pinMode(5, OUTPUT);//----------------------------Set Steering Bus MUX, PIN5 to Output
    }
//  F U N C T I O N   S C A D A
//  =================================================
    void SCADA_SER()//-------------------------------only for Test
    {
    Serial.print("#");
    Serial.print(80);
    Serial.print("M");
    Serial.print("26");
    Serial.print(thisDevice);
    Serial.println("<");

    for (int i=0; i <= 7; i++)
    {  
    Serial.print("#");
    Serial.print(i+1);
    Serial.print("M");
    Serial.print(inAn0[i]);
    Serial.println("<");
    }
    for (int i=0; i <= 7; i++)
    {  
    Serial.print("#");
    Serial.print(i+9);
    Serial.print("M");
    Serial.print(inAn2[i]);
    Serial.println("<");
    }
   
    }



