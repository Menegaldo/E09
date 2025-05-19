//                       PINO NO ARDUINO 
#define BT_0B PB0   //   8
#define BT_1B PB1   //   9

int cont = 0;

// Função PCINT0 - B
ISR(PCINT0_vect){

  if (cont == 0)
    Serial.println("REGISTRADOR B");
  
  if (cont == 1)
    cont = 0;

  if(!(PINB & 0b00000001)){

    Serial.println("PINO 8");
    cont++;
  }

  else if(!(PINB & 0b00000010)){
    
    Serial.println("PINO 9");
    cont++;
  }
}

int main(void){

  Serial.begin(9600);



  // QUAL GRUPO VAI TER INTERRUPÇÃO
  PCICR |= (1 << PCIE0); // B - PCIE0 | C - PCIE1 | D - PCICE2

  // REGISTRADOR USADO PARA DEFINIR QUAL PINO VAI TER INTERRUPÇÃO
  PCMSK0 |= (1 << BT_0B) | (1 << BT_1B); // B


  sei();

  for (;;){

  }
}
