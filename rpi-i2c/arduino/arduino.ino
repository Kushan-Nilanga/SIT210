// Light Matrix Pins
#define LATCH 2 
#define CLK 3
#define DATA 4
#define EN 5
#define ROW(x) (x+5)


void setup(){
  pinMode( LATCH, OUTPUT);
  pinMode( CLK, OUTPUT);
  pinMode( DATA, OUTPUT);
  pinMode( EN, OUTPUT);
  pinMode( ROW(1), OUTPUT);
  pinMode( ROW(2), OUTPUT);
  pinMode( ROW(3), OUTPUT);
  pinMode( ROW(4), OUTPUT);

  
}

int data[16] = {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535} ;


void loop(){
  for(short i = 0; i < 16; i++){
    mat_data(i, data[i]);
    delayMicroseconds(750);
  }
}


void mat_data(short row, int bitmask){
  digitalWrite(EN, HIGH);
  digitalWrite(ROW(1),row & 1); // 0001
  digitalWrite(ROW(2),row & 2); // 0010
  digitalWrite(ROW(3),row & 4); // 0100
  digitalWrite(ROW(4),row & 8); // 1000
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, LSBFIRST, ~((bitmask)      & 0xFF)); //lower portion
  shiftOut(DATA, CLK, LSBFIRST, ~((bitmask >> 8) & 0xFF)); //higher portion
  digitalWrite(LATCH, HIGH);
  digitalWrite(EN, LOW);
}
