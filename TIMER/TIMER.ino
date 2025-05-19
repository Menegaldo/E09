// TIMER

// TCCR0A - MODO DE OPERAÇÃO
// (1 << WGM01) (1 << WGM00) 

// 00 - NORMAL
// 01 - PWM
// 10 - CTC (COMPARAÇÃO)
// 11 - FAST PWM

// TCCR0B - PRESCALER
// (1 << CS02) (1 << CS01) (1 << CS00)

// 000 - 0     - 0 Hz       - 0 s
// 001 - 1     - 16 MHz     - 65,5 ns
// 010 - 8     - 2 MHz      - 500 ns
// 011 - 64    - 250 KHz    - 4 us
// 100 - 256   - 62,5 KHz   - 16 us
// 101 - 1024  - 15,625 KHz - 64 us

// TIMSK0 - MASCARA PARA HABILITAR O TIMER
// (1 << OCIE0A) - LIGA INTERRUPÇÃO DO COMPARADOR A DO TIMER 0

// I. (Fácil) Elaborar um firmware para criar um cronômetro HH:MM:SS com amostragem na interface
// sempre que um segundo for contado.

long int valor_contagem = 0;
const int valor_comparacao = 199;

long int seg = 0;
long int min = 0;
long int hora = 0;

ISR(TIMER0_COMPA_vect){
  
  valor_contagem++;

  if(valor_contagem >= 10000){

    valor_contagem = 0;
    seg++;

    if (seg >= 60){
      min++;
      seg = 0;
    }
    if (min >= 60){
      hora++;
      min = 0;
    }

    Serial.print(hora);
    Serial.print(":");
    Serial.print(min);
    Serial.print(":");
    Serial.println(seg);

  }
}

int main(){

  Serial.begin(9600);

  TCCR0A |= (1 << WGM01);    // MODO DE OPERAÇÃO - CTC (COMPARAÇÃO)
  TCCR0B |= (1 << CS01);     // PRESCALER 8

  OCR0A = valor_comparacao;  // NUMERO DE CICLOS (200 ticks)

  TIMSK0 |= (1 << OCIE0A);    // LIGA INTERRUPÇÃO DO COMPARADOR A DO TIMER 0

  sei();

  while(1){

  }
}
