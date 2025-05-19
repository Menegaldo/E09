// INTERRUPÇÃO INT0 E INT1

#define BT1 PD2 // INT0
#define BT2 PD3 // INT1

ISR(INT0_vect){

  Serial.println("INT0");
}

ISR(INT1_vect){

  Serial.println("INT1");
}

int main(){

  Serial.begin(9600);

  // EICRA

  // INT1 - (ISC11) (ISC10) - PD3
  // INT0 - (ISC01) (ISC00) - PD2

  // 0 0 = GND / 0 1 = TRANSIÇÃO / 1 0 = DESCIDA / 1 1 = SUBIDA

  // CONFIGURAÇÃO DE INTERRUPÇÃO
  EICRA |= (1 << ISC11) | (1 << ISC10); // INT1
  EICRA |= (1 << ISC01) | (1 << ISC00); // INT0

  // ON/OFF DA INTERRUPÇÃO
  EIMSK |= (1 << INT0) | (1 << INT1);

  sei();

  while(1){

  }
}
