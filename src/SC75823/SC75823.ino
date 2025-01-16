#include <SPI.h>

#define INH 7 // PORTD bit
#define CE  6 // PORTD bit
#define DI  5 // PORTD bit
#define CL  4 // PORTD bit


#define CCB_address   0x82



#define SYMBOL_ST         0
#define SYMBOL_FILE       12
#define SYMBOL_AF         27
#define SYMBOL_TA         42
#define SYMBOL_TP         57
#define SYMBOL_CARD       72 
#define SYMBOL_FOLDER     75
#define SYMBOL_DP         87 // Decimal Point
#define SYMBOL_PENDRIVE   120
#define SYMBOL_XBS        122
#define SYMBOL_PHONE      123
#define SYMBOL_FRAME      135
#define SYMBOL_EQ         136
#define SYMBOL_SUBW       144
#define SYMBOL_LOCAL      154
#define SYMBOL_BLUETOOTH  155






uint8_t displayBuffer[156] = {
  
  0,0,0,0, 0,0,0,0, // byte 0
  0,0,0,0, 0,0,0,0, // byte 1
  0,0,0,0, 0,0,0,0, // byte 2
  0,0,0,0, 0,0,0,0, // byte 3
  0,0,0,0, 0,0,0,0, // byte 4
  0,0,0,0, 0,0,0,0, // byte 5
  0,0,0,0, 0,0,0,0, // byte 6
  0,0,0,0, 0,0,0,0, // byte 7
  0,0,0,0, 0,0,0,0, // byte 8
  0,0,0,0, 0,0,0,0, // byte 9
  0,0,0,0, 0,0,0,0, // byte 10
  0,0,0,0, 0,0,0,0, // byte 11
  0,0,0,0, 0,0,0,0, // byte 12
  0,0,0,0, 0,0,0,0, // byte 13
  0,0,0,0, 0,0,0,0, // byte 14
  0,0,0,0, 0,0,0,0, // byte 15
  0,0,0,0, 0,0,0,0, // byte 16
  0,0,0,0, 0,0,0,0, // byte 17
  0,0,0,0, 0,0,0,0, // byte 18
  0,0,0,0           // byte 19
  
};




// A to G
uint8_t displaySegmentMiniDigitOutputs[8] = {15, 30, 60, 102, 105, 117, 45};




uint8_t displaySegmentDigitsOutputs[8][14] = {
  {
     7,  // A
    13,  // B
    14,  // C
     6,  // D
     2,  // E
     1,  // F
     5,  // G1
    11,  // G2
     4,  // H
     8,  // J,M
    10,  // K
     9,  // L
     8,  // J,M
     3   // N
    }, // Digit 1

  {22, 28, 29, 21, 17, 16, 20, 26, 19, 23, 25, 24, 23, 18},               // Digit 2
  {37, 43, 44, 36, 32, 31, 35, 41, 34, 38, 40, 39, 38, 33},               // Digit 3
  {52, 58, 59, 51, 47, 46, 50, 56, 49, 53, 55, 54, 53, 48},               // Digit 4
  {67, 73, 74, 66, 62, 61, 65, 71, 64, 68, 70, 69, 68, 63},               // Digit 5
  {82, 88, 89, 81, 77, 76, 80, 86, 79, 83, 85, 84, 83, 78},               // Digit 6
  {97, 103, 104, 96, 92, 91, 95, 101, 94, 98, 100, 99, 98, 93},           // Digit 7
  {112, 118, 119, 111, 107, 106, 110, 116, 109, 113, 115, 114, 113, 108}  // Digit 8
};




const uint8_t digitMap7[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };







const uint16_t digitMap14[] = {
	0x0000, /* (space) */
	0x4006, /* ! */
	0x0202, /* " */
	0x12CE, /* # */
	0x12ED, /* $ */
	0x3FE4, /* % */
	0x2359, /* & */
	0x0200, /* ' */
	0x2400, /* ( */
	0x0900, /* ) */
	0x3FC0, /* * */
	0x12C0, /* + */
	0x0800, /* , */
	0x00C0, /* - */
	0x4000, /* . */
	0x0C00, /* / */
	0x003F, /* 0 */
	0x0406, /* 1 */
	0x00DB, /* 2 */
	0x008F, /* 3 */
	0x00E6, /* 4 */
	0x00ED, /* 5 */
	0x00FD, /* 6 */
	0x0007, /* 7 */
	0x00FF, /* 8 */
	0x00EF, /* 9 */
	0x1200, /* : */
	0x0A00, /* ; */
	0x2440, /* < */
	0x00C8, /* = */
	0x0980, /* > */
	0x5083, /* ? */
	0x02BB, /* @ */
	0x00F7, /* A */
	0x128F, /* B */
	0x0039, /* C */
	0x120F, /* D */
	0x0079, /* E */
	0x0071, /* F */
	0x00BD, /* G */
	0x00F6, /* H */
	0x1209, /* I */
	0x001E, /* J */
	0x0C70, /* K */
	0x0038, /* L */
	0x0536, /* M */
	0x0936, /* N */
	0x003F, /* O */
	0x00F3, /* P */
	0x083F, /* Q */
	0x08F3, /* R */
	0x00ED, /* S */
	0x1201, /* T */
	0x003E, /* U */
	0x2430, /* V */
	0x2836, /* W */
	0x2D00, /* X */
	0x00EE, /* Y */
	0x2409, /* Z */
	0x0039, /* [ */
	0x2100, /* \ */
	0x000F, /* ] */
	0x2800, /* ^ */
	0x0008, /* _ */
	0x0100, /* ` */
	0x1058, /* a */
	0x2078, /* b */
	0x00D8, /* c */
	0x088E, /* d */
	0x0858, /* e */
	0x14C0, /* f */
	0x048E, /* g */
	0x1070, /* h */
	0x1000, /* i */
	0x0A10, /* j */
	0x3600, /* k */
	0x0030, /* l */
	0x10D4, /* m */
	0x1050, /* n */
	0x00DC, /* o */
	0x0170, /* p */
	0x0486, /* q */
	0x0050, /* r */
	0x2088, /* s */
	0x0078, /* t */
	0x001C, /* u */
	0x0810, /* v */
	0x2814, /* w */
	0x2D00, /* x */
	0x028E, /* y */
	0x0848, /* z */
	0x0949, /* { */
	0x1200, /* | */
	0x2489, /* } */
	0x0CC0, /* ~ */
	0x0000, /* (del) */
};







void setMiniDigitData(uint8_t data){

  for (uint8_t i = 0; i < sizeof(displaySegmentMiniDigitOutputs); i++){
    uint8_t outputBit = displaySegmentMiniDigitOutputs[i];

    if ( data & 1 << i ){
      displayBuffer[outputBit] = 1;
    }else{
      displayBuffer[outputBit] = 0;
    }

  }

}





void setBigDigitData(uint16_t data, uint8_t digit){

  if ( digit >= 8 ){
    return;
  }

  for (uint8_t i = 0; i < 14; i++){
    uint8_t outputBit = displaySegmentDigitsOutputs[digit][i];

    if ( data & 1 << i ){
      displayBuffer[outputBit] = 1;
    }else{
      displayBuffer[outputBit] = 0;
    }

  }

}





void setBigDigitString(char *txt){

  for (uint8_t i = 0; txt[i] != '\0'; i++){
    if ( i >= 8 ){
      break;
    }
    setBigDigitData( digitMap14[ txt[i] - 0x20 ] , i);
  }

}





void SC75823_update(uint8_t control){
 
  PORTD &= ~(1 << CE); // Chip Select: LOW

  // Send CCB
  for (uint8_t i = 0; i < 8; i++){
    
    if ( CCB_address & 1 << (7-i) ){
      PORTD |= (1 << DI);
    }else{
      PORTD &= ~(1 << DI);
    }

    PORTD |= (1 << CL);
    delayMicroseconds(200);
    PORTD &= ~(1 << CL);
    delayMicroseconds(200);

  }


  PORTD |= 1 << CE; // Chip Select: HIGH
  

  // Send Data
  for (uint8_t i = 0; i < sizeof(displayBuffer); i++){
    
    if ( displayBuffer[i] ){
      PORTD |= (1 << DI);
    }else{
      PORTD &= ~(1 << DI);
    }
    
    PORTD |= (1 << CL);
    delayMicroseconds(200);
    PORTD &= ~(1 << CL);
    delayMicroseconds(200);

  }


  // Send Control
  for (uint8_t i = 0; i < 4; i++){
    
    if ( control & 1 << (3-i) ){
      PORTD |= (1 << DI);
    }else{
      PORTD &= ~(1 << DI);
    }

    PORTD |= (1 << CL);
    delayMicroseconds(200);
    PORTD &= ~(1 << CL);
    delayMicroseconds(200);

  }
  
}










 
 

 

void setup() {

  PORTD = (1 << CE);
  DDRD  = (1 << INH) | (1 << CE) | (1 << DI) | (1 << CL);

  // Simbolos
  displayBuffer[SYMBOL_ST]        = 1;
  displayBuffer[SYMBOL_FILE]      = 1;
  displayBuffer[SYMBOL_AF]        = 1;
  displayBuffer[SYMBOL_TA]        = 1;
  displayBuffer[SYMBOL_TP]        = 1;
  displayBuffer[SYMBOL_CARD]      = 1;
  displayBuffer[SYMBOL_FOLDER]    = 1;
  displayBuffer[SYMBOL_DP]        = 1;
  displayBuffer[SYMBOL_PENDRIVE]  = 1;
  displayBuffer[SYMBOL_XBS]       = 1;
  displayBuffer[SYMBOL_PHONE]     = 1;
  displayBuffer[SYMBOL_FRAME]     = 1;
  displayBuffer[SYMBOL_EQ]        = 1;
  displayBuffer[SYMBOL_SUBW]      = 1;
  displayBuffer[SYMBOL_LOCAL]     = 1;
  displayBuffer[SYMBOL_BLUETOOTH] = 1;
  
  // Digito Pequeno (7 seg)
  setMiniDigitData( digitMap7[4] );

  // Digito Grande (14 seg)
  setBigDigitString((char *)"TEST 321");


  delay(1000);
  SC75823_update(0x00);
  delayMicroseconds(20);
  PORTD |= (1 << INH);
  

}






void loop(){


}
















