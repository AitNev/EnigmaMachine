/*
  @uthor Aitor Nevzorov
*/

// -- Variables for the code -- 
// BtnRegister connections to Arduino
const int latchPin = 10;
const int clockPin = 8;
const int dataPin = 9;

// BtnRegister connections to Arduino
const int latchPin2 = 7;
const int clockPin2 = 5;
const int dataPin2 = 6;

// BtnRegister connections to Arduino 
const int latchPin3 = 4;
const int clockPin3 = 2;
const int dataPin3 = 3;
const int btnIn = 11;

// Final values for choosing writing register
const int SEGMENT_DISPLAY = 0;
const int LED_MATRIX = 1;
const int BUTTON_REGISTERS = 2; 

// Milis delay functions
unsigned long previousMillis;
unsigned long previousStateMillis;
unsigned long delayBouncingLength = 5;
unsigned long delaySateLength = 2000; // Makes a small delay between each state

// Registers data
boolean segmentRegisters[16];
boolean ledRegisters[16];
boolean buttonRegisters[8];

// Button values
int buttonRegister = 0;
boolean isCheckingButtons = false;
boolean isFirstPressed = false;
boolean isButtonFound = false;

// -- Testing Variables --
// Led Matrix letter adding
int letterCount = 0; 
unsigned long previousCountMillis;
// 7Display letter adding
int count = 0;
int segmentLetters[4] = {0,35,35,35}; // Constant var


// -- Code --
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);

  pinMode(latchPin3, OUTPUT);
  pinMode(clockPin3, OUTPUT);
  pinMode(dataPin3, OUTPUT);
  pinMode(btnIn, INPUT);

  for(int i=0;i<sizeof(buttonRegisters);i++){
      buttonRegisters[i] = HIGH;  
  }
  
  writeReg(SEGMENT_DISPLAY);
  writeReg(LED_MATRIX);
  writeReg(BUTTON_REGISTERS);
}

void loop() {/*
  // One button handling
  if(digitalRead(btnIn) == HIGH){ // The button is pusshed and has current
    if(isButtonFound){
      // code
    }else{
      handleBtnPusshed();
    }
  }else if(isCheckingButtons){ // It's checking new buttons
    if(buttonRegister > sizeof(buttonRegisters)){ // Something went totaly wrong. It stops looking for a button input 
      isCheckingButtons = false;
      isFirstPressed = false;
      for(int i=0;i<sizeof(buttonRegisters);i++){
        buttonRegisters[i] = HIGH;  
      }
      writeReg(BUTTON_REGISTERS);
    }else if((unsigned long)(millis()-previousStateMillis)>= delaySateLength){ // Its going for each state with the delay
      previousStateMillis = millis();
      buttonRegister = buttonRegister + 1;
      prepareButton(buttonRegister);
      writeReg(BUTTON_REGISTERS);
    }
  }else if(isButtonFound){ 
    isButtonFound = false;
    for(int i=0;i<sizeof(buttonRegisters);i++){
        buttonRegisters[i] = HIGH;  
    }
  }
  else if(!isCheckingButtons){
    for(int i=0;i<sizeof(buttonRegisters);i++){
        buttonRegisters[i] = HIGH;  
    }
    writeReg(BUTTON_REGISTERS);
  }*/
  // Here the seven segment display refresh
  for(int i=0; i<4;i++){// Sets a special digit for each number
    if(count == 36){count = 0;}
    segmentRegisters[(8+i)] = HIGH;
    prepareNumber(segmentLetters[i]);
    writeReg(SEGMENT_DISPLAY);
    count++;
    segmentRegisters[(8+i)] = LOW;
    
  }
  segmentLetters[3] = segmentLetters[3]+1;
  if(segmentLetters[3]> 26){
    segmentLetters[3] = 0;
  }
  delay(4000);
  // Led matrix adding test
  if((unsigned long)(millis()-previousCountMillis)>= 1000){
    previousCountMillis = millis();
    letterCount++;
    if(letterCount == 26){
      letterCount = 0;
    }
  }
  // Here the matrix of leds refreh
  long letter[8] = {0,0,0,0,0,0,0,0};
  getletter(letterCount, letter);
  displayLetter(letter);
}

void handleBtnPusshed(){ // There is an actual input on the button
    if(!isFirstPressed){ // Here is preparing for the delay to get rid of the bouncing button
      isFirstPressed = true;
      previousMillis = millis();
      segmentLetters[0] = 7 + 26;
      //segmentLetters[0] = segmentLetters[0] + 1;
    }else if(!isCheckingButtons && (unsigned long)(millis() - previousMillis) >= delayBouncingLength){ // Now is the first time it recognices the button
      isCheckingButtons = true;
      buttonRegister = 0;
      prepareButton(0);
      writeReg(BUTTON_REGISTERS);
    }else if(isCheckingButtons){ // After all shifting it finds the actual pressed button, 
      isCheckingButtons = false;
      isFirstPressed = false;
      isButtonFound = true;
      // handle button
      
    }
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
  }else if(type == BUTTON_REGISTERS){ // Updates the register for checking each button
    digitalWrite(latchPin3, LOW);
    for(int i= 15; i>=0; i--){
      digitalWrite(clockPin3, LOW);
      digitalWrite(dataPin3, buttonRegisters[i]);
      digitalWrite(clockPin3, HIGH);
    }
    digitalWrite(latchPin3, HIGH);
  }    
}
void displayLetter(long letter[]){
  for(int i=0; i<8; i++){
      ledRegisters[i] = LOW;
  }
  for(int i=0; i<8;i++){ // Prepares for rendering
    ledRegisters[(8+i)] = HIGH; // Wont display
  }
  for(int i=0; i<8;i++){
    ledRegisters[(8+i)] = LOW;
    
    long num = letter[i];
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
  }
}
void prepareButton(int buttonNumber){ // Prepares the arry for the button shift register
  for(int i=0;i<sizeof(buttonRegisters);i++){
    buttonRegisters[i] = LOW;  
  }buttonRegisters[buttonNumber] = HIGH;
}
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
      segmentRegisters[7]= HIGH;
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
      segmentRegisters[7]= HIGH;
      break;
    }case 8:{ // I
      segmentRegisters[5]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 9:{ // J
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      break;
    }case 10:{ // K
      segmentRegisters[5]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 11:{ // L
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 12:{ // M
      segmentRegisters[0]= HIGH; segmentRegisters[3]= HIGH;
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
      segmentRegisters[6]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 20:{ // U
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 21:{ // V
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[5]= HIGH;
      break;
    }case 22:{ // W
      segmentRegisters[1]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 23:{ // X
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[5]= HIGH; segmentRegisters[7]= HIGH;
      break;
    }case 24:{ // Y
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[6]= HIGH;
      segmentRegisters[7]= HIGH;
      break;
    }case 25:{ // Z
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
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
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[4]= HIGH; segmentRegisters[5]= HIGH;
      segmentRegisters[6]= HIGH;
      break;
    }case 29:{ // 3
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
      segmentRegisters[3]= HIGH; segmentRegisters[4]= HIGH;
      segmentRegisters[6]= HIGH;
      break;
    }case 30:{ // 4
      segmentRegisters[1]= HIGH; segmentRegisters[3]= HIGH;
      segmentRegisters[6]= HIGH; segmentRegisters[7]= HIGH;
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
      segmentRegisters[0]= HIGH; segmentRegisters[1]= HIGH;
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
      break;  
    }
  }
}
