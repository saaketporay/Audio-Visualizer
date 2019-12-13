
//mic code
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
//mic code

//led matrix code
int dataIn = 2;
int load = 3;
int clock = 4;
int maxInUse = 4; 
int e = 0;           
 
// define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;
 
void putByte(byte data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);      // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask){            // choose bit
      digitalWrite(dataIn, HIGH);// send 1
    }else{
      digitalWrite(dataIn, LOW); // send 0
    }
    digitalWrite(clock, HIGH);   // tock
    --i;                         // move to lesser bit
  }
}
 
void maxSingle( byte reg, byte col) {    
//function to use for a single max7219
  digitalWrite(load, LOW);       // begin    
  putByte(reg);                  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data  
  digitalWrite(load, LOW);       // and load da stuff
  digitalWrite(load,HIGH);
}
 
void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  digitalWrite(load, LOW);  // begin    
  for ( c =1; c<= maxInUse; c++) {
  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
  digitalWrite(load, LOW);
  digitalWrite(load,HIGH);
}
 
void maxOne(byte maxNr, byte reg, byte col) {    
//maxOne is for addressing different MAX7219's,
//while having a couple of them cascaded
 
  int c = 0;
  digitalWrite(load, LOW);  // begin    
 
  for ( c = maxInUse; c > maxNr; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }
  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
  for ( c =maxNr-1; c >= 1; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }
 
  digitalWrite(load, LOW); // and load da stuff
  digitalWrite(load,HIGH);
}
 
 
void setup () {
//mic code
  Serial.begin(9600);
//mic code

  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);
  digitalWrite(13, HIGH);  
 
//initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);      
  maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
   for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off
    maxAll(e,0);
  }
  maxAll(max7219_reg_intensity, 0x0f & 0x0f);    // the first 0x0f is the value you can set
                                                  // range: 0x00 to 0x0f
}  
 
void loop () {
 
  
//mic code
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(A13);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
 
   Serial.println(volts);
// mic code

   if (volts < 0.4)
   {
    maxAll(1,255);                       
    maxAll(2,0);                      
    maxAll(3,0);                      
    maxAll(4,0);                      
    maxAll(5,0);                      
    maxAll(6,0);                      
    maxAll(7,0);                   
    maxAll(8,0);                    
   }
   else if (volts > 0.4 && volts < 0.7)
   {
    maxAll(1,255);                      
    maxAll(2,255);                      
    maxAll(3,0);                      
    maxAll(4,0);                      
    maxAll(5,0);                      
    maxAll(6,0);                      
    maxAll(7,0);                     
    maxAll(8,0);                     
   }
   else if(volts > 0.7 && volts < 1.0)
   {
    maxAll(1,255);                       
    maxAll(2,255);                       
    maxAll(3,255);                       
    maxAll(4,0);                      
    maxAll(5,0);                      
    maxAll(6,0);                     
    maxAll(7,0);                     
    maxAll(8,0);                     
   }
   else if (volts > 1.0 && volts < 1.3)
   {
    maxAll(1,255);                       
    maxAll(2,255);                     
    maxAll(3,255);                       
    maxAll(4,255);                     
    maxAll(5, 0);                    
    maxAll(6,0);                    
    maxAll(7,0);                    
    maxAll(8,0);                    
   }
   else if( volts > 1.3 && volts < 1.6)
   {
    maxAll(1,255);                       
    maxAll(2,255);                      
    maxAll(3,255);                      
    maxAll(4,255);                     
    maxAll(5,255);                    
    maxAll(6,0);                      
    maxAll(7,0);                   
    maxAll(8,0);                     
   }
   else if ( volts > 1.6 && volts < 1.9)
   {
    maxAll(1,255);                     
    maxAll(2,255);                      
    maxAll(3,255);                      
    maxAll(4,255);                      
    maxAll(5,255);                      
    maxAll(6,255);                    
    maxAll(7,0);                    
    maxAll(8,0);                     
   }
   else if ( volts > 1.9 && volts < 2.1)
   {
    maxAll(1,255);                      
    maxAll(2,255);                       
    maxAll(3,255);                      
    maxAll(4,255);                      
    maxAll(5,255);                      
    maxAll(6,255);                       
    maxAll(7,255);                     
    maxAll(8,0);                     
   }
   else if (volts > 2.1 && volts < 2.4)
   {
    maxAll(1,255);                       
    maxAll(2,255);                       
    maxAll(3,255);                       
    maxAll(4,255);                      
    maxAll(5,255);                     
    maxAll(6,255);                     
    maxAll(7,255);                     
    maxAll(8,255);                     
   }
 
}
