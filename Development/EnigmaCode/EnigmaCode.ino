/*
  @uthor Aitor Nevzorov
*/
#include <SoftwareSerial.h> //Library to stablish a serial connection with hc-06

SoftwareSerial BT(12,11); // Bluetooth Connection

// -- Variables for the code -- 
// SegmentRegister connections to Arduino
const int latchPin = 10;
const int clockPin = 8;
const int dataPin = 9;

// LedMatrixRegister connections to Arduino
const int latchPin2 = 7;
const int clockPin2 = 5;
const int dataPin2 = 6;

// Final values for choosing writing register
const int SEGMENT_DISPLAY = 0;
const int LED_MATRIX = 1;

// Registers data
boolean segmentRegisters[16];
boolean ledRegisters[16];

// BT data
char chain[255];
int chainLength = 0;

int segmentLetters[4] = {0,0,0,0}; // Constant var

int displayNumber = 100; // 25+ Won't display nothing
int reflector[] = {1,0,10,22,12,24,17,14,9,8,2,18,4,21,7,16,15,6,11,25,23,13,3,20,5,19}; // This must join the numbers only in pairs beeing between 0 and 25
int scramblerA[] = {8,19,1,12,3,5,15,4,18,7,21,13,14,6,2,16,24,17,0,20,10,25,23,11,22,9};// Each scrambler can be different but the rescrambler have to mach it, numbers can't repeat and be between 0 and 25
int scramblerB[] = {8,19,1,12,3,5,15,4,18,7,21,13,14,6,2,16,24,17,0,20,10,25,23,11,22,9};
int scramblerC[] = {8,19,1,12,3,5,15,4,18,7,21,13,14,6,2,16,24,17,0,20,10,25,23,11,22,9};
int reScramblerA[] = {18,2,14,4,7,5,13,9,0,25,20,23,3,11,12,6,15,17,8,1,19,10,24,22,16,21};
int reScramblerB[] = {18,2,14,4,7,5,13,9,0,25,20,23,3,11,12,6,15,17,8,1,19,10,24,22,16,21};
int reScramblerC[] = {18,2,14,4,7,5,13,9,0,25,20,23,3,11,12,6,15,17,8,1,19,10,24,22,16,21};
int scramblerAPosition = 0;
int scramblerBPosition = 0;
int scramblerCPosition = 0;

boolean rotorMode = false; // Mode of setting the rotor
int rotorPosition = 0; // Keeps trak of the changed rotor in the rotorMode 

// -- Code --
void setup() {
  BT.begin(9600);

  Serial.begin(9600);
  Serial.write("Arduino ON");
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  
  writeReg(SEGMENT_DISPLAY);
  writeReg(LED_MATRIX);
}

void loop() {
  //Reads if there is bt input
  if(BT.available()){handleBT();}
  if(rotorMode){
    segmentLetters[3] = scramblerAPosition;
    segmentLetters[2] = scramblerBPosition;
    segmentLetters[1] = scramblerCPosition;
    segmentLetters[0] = 37; // 37 Does't display anything
    segmentLetters[3-rotorPosition] = 36;
  }else{
    segmentLetters[3] = scramblerAPosition;
    segmentLetters[2] = scramblerBPosition;
    segmentLetters[1] = scramblerCPosition;
    segmentLetters[0] = 37;
  }
  // Here the matrix of leds refreh
  long letter[8] = {0,0,0,0,0,0,0,0};
  getletter(displayNumber, letter);
  displayLetter(letter);
}

void handleBT(){
    char data=BT.read(); 
    chain[chainLength++]=data; 
    if(data=='\n')
    {
      if(strstr(chain,"E_A")!=0){
        displayNumber = scramble(0);Serial.println("A--> "+displayNumber);
      } else if(strstr(chain,"E_B")!=0){
        displayNumber = scramble(1);Serial.println("B--> "+displayNumber);
      } else if(strstr(chain,"E_C")!=0){
        displayNumber = scramble(2);Serial.println("C--> "+displayNumber);
      } else if(strstr(chain,"E_D")!=0){
        displayNumber = scramble(3);Serial.println("D--> "+displayNumber);
      } else if(strstr(chain,"E_E")!=0){
        displayNumber = scramble(4);Serial.println("E--> "+displayNumber);
      } else if(strstr(chain,"E_F")!=0){
        displayNumber = scramble(5);Serial.println("F--> "+displayNumber);
      } else if(strstr(chain,"E_G")!=0){
        displayNumber = scramble(6);Serial.println("G--> "+displayNumber);
      } else if(strstr(chain,"E_H")!=0){
        displayNumber = scramble(7);Serial.println("H--> "+displayNumber);
      } else if(strstr(chain,"E_I")!=0){
        displayNumber = scramble(8);Serial.println("I--> "+displayNumber);
      } else if(strstr(chain,"E_J")!=0){
        displayNumber = scramble(9);Serial.println("J--> "+displayNumber);
      } else if(strstr(chain,"E_K")!=0){
        displayNumber = scramble(10);Serial.println("K--> "+displayNumber);
      } else if(strstr(chain,"E_L")!=0){
        displayNumber = scramble(11);Serial.println("L--> "+displayNumber);
      } else if(strstr(chain,"E_M")!=0){
        displayNumber = scramble(12);Serial.println("M--> "+displayNumber);
      } else if(strstr(chain,"E_N")!=0){
        displayNumber = scramble(13);Serial.println("N--> "+displayNumber);
      } else if(strstr(chain,"E_O")!=0){
        displayNumber = scramble(14);Serial.println("O--> "+displayNumber);
      } else if(strstr(chain,"E_P")!=0){
        displayNumber = scramble(15);Serial.println("P--> "+displayNumber);
      } else if(strstr(chain,"E_Q")!=0){
        displayNumber = scramble(16);Serial.println("Q--> "+displayNumber);
      } else if(strstr(chain,"E_R")!=0){
        displayNumber = scramble(17);Serial.println("R--> "+displayNumber);
      } else if(strstr(chain,"E_S")!=0){
        displayNumber = scramble(18);Serial.println("S--> "+displayNumber);
      } else if(strstr(chain,"E_T")!=0){
        displayNumber = scramble(19);Serial.println("T--> "+displayNumber);
      } else if(strstr(chain,"E_U")!=0){
        displayNumber = scramble(20);Serial.println("U--> "+displayNumber);
      } else if(strstr(chain,"E_V")!=0){
        displayNumber = scramble(21);Serial.println("V--> "+displayNumber);
      } else if(strstr(chain,"E_W")!=0){
        displayNumber = scramble(22);Serial.println("W--> "+displayNumber);
      }else if(strstr(chain,"E_X")!=0){
        displayNumber = scramble(23);Serial.println("X--> "+displayNumber);
      } else if(strstr(chain,"E_Y")!=0){
        displayNumber = scramble(24);Serial.println("Y--> "+displayNumber);
      } else if(strstr(chain,"E_Z")!=0){
        displayNumber = scramble(25);Serial.println("Z--> "+displayNumber);
      }else if(strstr(chain,"R___E")!=0){
        rotorMode = true;Serial.println("Rotor mode");
        displayNumber = 100; // Won't display nothing while changing scramblers 
      }
      
      BT.write("\r");
      clean();
    }
}

int scramble(int number){
  if(rotorMode){
    rotorPosition = rotorPosition + 1;
    switch(rotorPosition){
      case 1:{
        scramblerAPosition = number;
        break;
      }case 2:{
        scramblerBPosition = number;
        break;
      }case 3:{
        scramblerCPosition = number;
        rotorPosition = 0;
        rotorMode = false;
        break;
      }default:{
        rotorPosition = 0;
        rotorMode = false; 
        break;
      }
    } return 100; // Won't display nothing while changing scramblers
  }else{
    int r = scrambleC(scrambleB(scrambleA(number,true),true),true);  
    r = reflector[r];
    if(r >= 26){
      r = r-26;
    } r = scrambleA(scrambleB(scrambleC(r, false),false),false);
    scramblerPositionIncrease();
    return r;
  }
}
int scrambleA(int number, boolean foward){
  int s = mod(number + 26 - scramblerAPosition, 26);
  int r;
  if(foward){
    r = scramblerA[s];
  }else{
    r = reScramblerA[s];
  }r = mod(r + scramblerAPosition, 26);
  return r;
}
int scrambleB(int number, boolean foward){
  int s = mod(number + 26 - scramblerBPosition, 26);
  int r;
  if(foward){
    r = scramblerB[s];
  }else{
    r = reScramblerB[s];
  }r = mod(r + scramblerBPosition, 26);
  return r;
}
int scrambleC(int number, boolean foward){
  int s = mod(number + 26 - scramblerCPosition, 26);
  int r;
  if(foward){
    r = scramblerC[s];
  }else{
    r = reScramblerC[s];
  }r = mod(r + scramblerCPosition,26);
  return r;
}
int mod(int num, int maxN){
  if(num >=maxN){
    return num-maxN;
  }return num;
}
void scramblerPositionIncrease(){
  scramblerAPosition = scramblerAPosition +1;
  if(scramblerAPosition == 26){
    scramblerAPosition = 0;
    scramblerBPosition = scramblerBPosition +1;
    if(scramblerBPosition == 26){
      scramblerBPosition = 0;
      scramblerCPosition = scramblerCPosition +1;
      if(scramblerCPosition == 26){
        scramblerCPosition = 0;
      }
    }
  }
}

void DisplaySegmentrs(){
  // Here the seven segment display refresh
  for(int i=0; i<4;i++){// Sets a special digit for each number
    segmentRegisters[(8+i)] = HIGH;
    prepareNumber(segmentLetters[i]);
    writeReg(SEGMENT_DISPLAY);
    segmentRegisters[(8+i)] = LOW;
  }
}

void clean() // Resets the chain
{
  for (int cl=0; cl<=chainLength; cl++)
  {
    chain[cl]=0;
  }
  chainLength=0;
}

void writeReg(int type){ // Upload the data to the shift registers
  if(type == SEGMENT_DISPLAY){ // Sends the registers of the seven segment display
    digitalWrite(latchPin, LOW);
    for(int i= 15; i>=0; i--){
      digitalWrite(clockPin, LOW);
      digitalWrite(dataPin, segmentRegisters[i]);
      digitalWrite(clockPin, HIGH);
    }
    digitalWrite(latchPin, HIGH);
  }else if(type == LED_MATRIX){ // Sends the registers of the matrix of leds
    digitalWrite(latchPin2, LOW);
    for(int i= 15; i>=0; i--){
      digitalWrite(clockPin2, LOW);
      digitalWrite(dataPin2, ledRegisters[i]);
      digitalWrite(clockPin2, HIGH);
    }
    digitalWrite(latchPin2, HIGH);  
  } 
}
void displayLetter(long letter[]){
  for(int i=0; i<8; i++){
      ledRegisters[i] = LOW;
  }
  for(int i=0; i<8;i++){ // Prepares for rendering
    ledRegisters[(8+i)] = HIGH; // Wont display
  }
  DisplaySegmentrs();
  for(int i=0; i<8;i++){
    ledRegisters[(8+i)] = LOW;

    // Note that is reading from right to left due to welding issues
    long num = letter[7-i]; 
    if(num >= 10000000){
      num = num - 10000000;
      ledRegisters[0] = HIGH;
    }if(num >= 1000000){
      num = num - 1000000;
      ledRegisters[1] = HIGH;
    }if(num >= 100000){
      num = num - 100000;
      ledRegisters[2] = HIGH;
    }if(num >= 10000){
      num = num - 10000;
      ledRegisters[3] = HIGH;
    }if(num >= 1000){
      num = num - 1000;
      ledRegisters[4] = HIGH;
    }if(num >= 100){
      num = num - 100;
      ledRegisters[5] = HIGH;
    }if(num >= 10){
      num = num - 10;
      ledRegisters[6] = HIGH;
    }if(num >= 1){
      ledRegisters[7] = HIGH;
    }
    
    writeReg(LED_MATRIX);
    // Prepares for the next pass
    for(int i=0; i<8; i++){
      ledRegisters[i] = LOW;
    }
    ledRegisters[(8+i)] = HIGH;

    if(i>0){
      DisplaySegmentrs();
    }
  }
}

// Note that segmentRegisters[0] & segmentRegisters[7] are being swaped due to welding issues
void prepareNumber(int number){ // Letter value for the 7 segment display
  for(int i=0; i<8; i++){ // Clears all numbers
      segmentRegisters[i] = LOW;
  }
  switch(number){ // Asigns a number
    case 0:{ // A
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 1:{ // B
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[0]= HIGH;
      break;
    }case 2:{ // C
      segmentRegisters[0]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 3:{ // D
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH;
      break;
    }case 4:{ // E
      segmentRegisters[0]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 5:{ // F
      segmentRegisters[0]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 6:{ // G
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 7:{ // H
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[0]= HIGH;
      break;
    }case 8:{ // I
      segmentRegisters[5]= HIGH; segmentRegisters[0]= HIGH;
      break;
    }case 9:{ // J
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      break;
    }case 10:{ // K
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[0]= HIGH;
      break;
    }case 11:{ // L
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[0]= HIGH;
      break;
    }case 12:{ // M
      segmentRegisters[7]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[5]= HIGH;
      break;
    }case 13:{ // N
      segmentRegisters[5]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[6]= HIGH;
      break;
    }case 14:{ // O
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 15:{ // P
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 16:{ // Q
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 17:{ // R
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      break;
    }case 18:{ // S
      segmentRegisters[0]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 19:{ // T
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[0]= HIGH;
      break;
    }case 20:{ // U
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[0]= HIGH;
      break;
    }case 21:{ // V
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH;
      break;
    }case 22:{ // W
      segmentRegisters[1]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[0]= HIGH;
      break;
    }case 23:{ // X
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[0]= HIGH;
      break;
    }case 24:{ // Y
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[0]= HIGH;
      break;
    }case 25:{ // Z
      segmentRegisters[7]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH;
      break;
    }case 26:{ // 0
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 27:{ // 1
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      break;
    }case 28:{ // 2
      segmentRegisters[7]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH;
      break;
    }case 29:{ // 3
      segmentRegisters[7]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[6]= HIGH;
      break;
    }case 30:{ // 4
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[0]= HIGH;
      break;
    }case 31:{ // 5
      segmentRegisters[0]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 32:{ // 6
      segmentRegisters[0]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 33:{ // 7
      segmentRegisters[7]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH;
      break;
    }case 34:{ // 8
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 35:{ // 9
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 36:{ // _
      segmentRegisters[4]= HIGH;
      break;
    }default:{
      break;  
    }
  }
}

void getletter(int ltr, long letter[]){ // Letter value for the led matrix
  switch(ltr){
    case 0:{ // A
      letter[0] = 0; letter[1] = 111111; letter[2] = 1001000; letter[3] = 1001000; 
      letter[4] = 1001000; letter[5] = 111111; letter[6] = 0; 
      letter[7] = 0;
      break;
    }case 1:{ // B
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1001001; letter[3] = 1001001;  
      letter[4] = 1001001; letter[5] = 110110; letter[6] = 0; 
      letter[7] = 0;
      break;
    }case 2:{ // C
      letter[0] = 0; letter[1] = 111110; letter[2] = 1000001; letter[3] = 1000001; 
      letter[4] = 1000001; letter[5] = 100010;  letter[6] = 0; 
      letter[7] = 0;
      break;
    }case 3:{ // D
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1000001; letter[3] = 1000001;  
      letter[4] = 1000001; letter[5] = 111110; letter[6] = 0; 
      letter[7] = 0;
      break;
    }case 4:{ // E
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1001001; letter[3] = 1001001;  
      letter[4] = 1001001; letter[5] = 1000001; letter[6] = 0;  
      letter[7] = 0;
      break;
    }case 5:{ // F
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1001000; letter[3] = 1001000;  
      letter[4] = 1001000; letter[5] = 1000000;  letter[6] = 0; 
      letter[7] = 0;
      break;
    }case 6:{ // G
      letter[0] = 0; letter[1] = 111110; letter[2] = 1000001; 
      letter[3] = 1000001; letter[4] = 1000101; letter[5] = 100110; letter[6] = 0; 
      letter[7] = 0;
      break;
    }case 7:{ // H
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1000; 
      letter[3] = 1000; letter[4] = 1000; letter[5] = 1111111; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 8:{ // I
      letter[0] = 0; letter[1] = 1000001; letter[2] = 1000001; 
      letter[3] = 1111111; letter[4] = 1000001; letter[5] = 1000001; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 9:{ // J
      letter[0] = 0; letter[1] = 1000010; letter[2] = 1000001; 
      letter[3] = 1000001; letter[4] = 1000001; letter[5] = 1111110; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 10:{ // K
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1000; 
      letter[3] = 1000; letter[4] = 10100; letter[5] = 1100011; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 11:{ // L
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1; 
      letter[3] = 1; letter[4] = 1; letter[5] = 1; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 12:{ // M
      letter[0] = 0; letter[1] = 1111111; letter[2] = 100000; 
      letter[3] = 10000; letter[4] = 100000; letter[5] = 1111111; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 13:{ // N
      letter[0] = 0; letter[1] = 1111111; letter[2] = 10000; 
      letter[3] = 1000; letter[4] = 100; letter[5] = 1111111; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 14:{ // O
      letter[0] = 0; letter[1] = 111110; letter[2] = 1000001; 
      letter[3] = 1000001; letter[4] = 1000001; letter[5] = 111110; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 15:{ // P
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1001000; 
      letter[3] = 1001000; letter[4] = 1001000; letter[5] = 110000; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 16:{ // Q
      letter[0] = 0; letter[1] = 111110; letter[2] = 1000001; 
      letter[3] = 1000101; letter[4] = 1000010; letter[5] = 111101; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 17:{ // R
      letter[0] = 0; letter[1] = 1111111; letter[2] = 1001000; 
      letter[3] = 1001000; letter[4] = 1001000; letter[5] = 110111; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 18:{ // S
      letter[0] = 0; letter[1] = 110001; letter[2] = 1001001; 
      letter[3] = 1001001; letter[4] = 1001001; letter[5] = 1000110; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 19:{ // T
      letter[0] = 0; letter[1] = 1000000; letter[2] = 1000000; 
      letter[3] = 1111111; letter[4] = 1000000; letter[5] = 1000000; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 20:{ // U
      letter[0] = 0; letter[1] = 1111110; letter[2] = 1; 
      letter[3] = 1; letter[4] = 1; letter[5] = 1111110; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 21:{ // V
      letter[0] = 0; letter[1] = 1111100; letter[2] = 10; 
      letter[3] = 1; letter[4] = 10; letter[5] = 1111100; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 22:{ // W
      letter[0] = 0; letter[1] = 1111111; letter[2] = 10; 
      letter[3] = 100; letter[4] = 10; letter[5] = 1111111; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 23:{ // X
      letter[0] = 0; letter[1] = 1100011; letter[2] = 10100; 
      letter[3] = 1000; letter[4] = 10100; letter[5] = 1100011; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 24:{ // Y
      letter[0] = 0; letter[1] = 1100000; letter[2] = 10000; 
      letter[3] = 1111; letter[4] = 10000; letter[5] = 1100000; letter[6] = 0;
      letter[7] = 0;
      break;
    }case 25:{ // Z
      letter[0] = 0; letter[1] = 1000011; letter[2] = 1000101; 
      letter[3] = 1001001; letter[4] = 1010001; letter[5] = 1100001; letter[6] = 0;
      letter[7] = 0;
      break;
    }default:{
      letter[0] = 0; letter[1] = 0; letter[2] = 0; 
      letter[3] = 0; letter[4] = 0; letter[5] = 0; letter[6] = 0;
      letter[7] = 0;
      break;  
    }
  }
}
