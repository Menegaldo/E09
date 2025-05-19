
// Timer 0 - 8 bits       | Timer 1 - 16 bits        | Timer 2 - 8 bits
// -----------------------|--------------------------|------------------------
// OC0A – pino 6   - PD6  | OC1A – pino 9     - PB1  | OC2A – pino 11  - PB3
// OC0B – pino 5   - PD5  | OC1B – pino 10    - PB2  | OC2B – pino 3   - PD2
// 0 a 255                | 0 a 65535                | 0 a 255 

// (1 << WGMx1) | (1 << WGMx0) | TCCRxA
// -------------|--------------|------------------
//       0      |      0       | NORMAL
//       0      |      1       | PWM
//       1      |      0       | CTC (COMPARAÇÃO)
//       1      |      1       | FAST PWM

// TCCR0B - PRESCALER
// (CSx2) | (CSx1) | (CSx0) | PRESCALER | FREQUÊNCIA | TICK
// -------|--------|--------|-----------|------------|----------
//    0   |    0   |    0   |   0       | 0       Hz | 0     s
//    0   |    0   |    1   |   1       | 16     MHz | 65,5 ns
//    0   |    1   |    0   |   8       | 2      MHz | 500  ns
//    0   |    1   |    1   |   64      | 250    KHz | 4    us
//    1   |    0   |    0   |   256     | 62,5   KHz | 16   us
//    1   |    0   |    1   |   1024    | 15,625 KHz | 64   us 

// (COMxA1) | (COMxA0) | TCCRxA
// ---------|----------|---------------------------------------------
//     0    |     0    | DESLIGADO
//     0    |     1    | SINAL QUADRADO - (SEM VALOR DE COMPARAÇÃO)
//     1    |     0    | NL ALTO NO TEMPO ATE A COMPARAÇÃO
//     1    |     1    | NL BAIXO NO TEMPO ATE A COMPARAÇÃO

int Ton_A = 0;
int Ton_B = 255;

int main(void){
  
  // DEFINIÇÃO - PINO DE SAÍDA
  DDRD |= (1 << PD5) | (1 << PD6);
  
  // MODO DE OPERAÇÃO - FAST PWM
  TCCR0A |= (1 << WGM01) | (1 << WGM00);

  // APLICA SET NO PWM EM BOTTOM
  TCCR0A |= (1 << COM0A1);
  TCCR0A |= (1 << COM0B1);

  // DIVISOR DO CLOCK - PRESCALER 1 | 16 MHz - 62,5 ns
  TCCR0B |= (1 << CS00); // cada ticks do time

  // VALOR DE Ton
  OCR0A = 0;
  OCR0B = 255;

  for(;;){
    // /*
    OCR0A = Ton_A;
    OCR0B = Ton_B;

    Ton_A += 10;
    Ton_B -= 10;
      
    if (Ton_A > 255)
      Ton_A = 0;

    if (Ton_B < 0)
      Ton_B = 255;

    _delay_ms(300);
    // */
  }
}
