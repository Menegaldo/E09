// ADCSRA
// ---------|----------------------------------|----------------------------------------|
// POSIÇÃO  | 0                                | 1                                      |
// ---------|----------------------------------|----------------------------------------|
// 7	ADEN  | Desliga o ADC	                   | Liga o ADC                             |
// 6	ADSC  |	Não inicia conversão             | Inicia uma conversão                   |
// 5	ADATE |	Desativa Auto Trigger	           | Ativa Auto Trigger (modo automático)   | -> configuração
// 4	ADIF	| conversão não terminada          | Conversão terminada                    |
// 3	ADIE	| Interrupção de ADC desabilitada  | Habilita interrupção de ADC            |

// 2  ADPS2 | 1  ADPS1 | 0  ADPS0 | Divisão do Clock (Prescaler)
// ---------|----------|----------|-----------------------------
// 0	      | 0	       | 0        |	2
// 0	      | 0        | 1        | 2
// 0        |	1	       | 0        |	4
// 0	      | 1        | 1        |	8
// 1        |	0        | 0        |	16
// 1        |	0        | 1        |	32
// 1	      | 1        | 0	      | 64
// 1        |	1        | 1        |	128

// PRESCALER 128 (MAIS TEMPO POR DECISÃO)
// clock ADC              125000 ciclo/seg
// ciclos por conversão       13 ciclo
// conversões/seg           9615 conversões/seg

// AADATE |
// ADTS2 | ADTS1 | ADTS0 | Evento que dispara conversão         | Descrição
// ------|-------|-------|--------------------------------------|------------------------------------
// 0	   | 0	   | 0	   | Conversão livre (Free Running Mode)  | Convertendo o tempo todo, sem parar
// 0	   | 0	   | 1	   | Comparador analógico                 | Quando o comparador detecta uma diferença de tensão
// 0	   | 1	   | 0	   | Interrupção externa (INT0)           | Quando uma borda (ex: botão) ativa a interrupção externa 0.
// 0	   | 1     | 1	   | Timer/Counter0 Compare Match A       | Usa o momento de estouro ou comparação dos temporizadores para iniciar a conversão.
// 1	   | 0	   | 0	   | Timer/Counter0 Overflow              | -
// 1	   | 0	   | 1	   | Timer/Counter1 Compare Match B       | -
// 1	   | 1	   | 0	   | Timer/Counter1 Overflow              | - 
// 1	   | 1	   | 1	   | Timer/Counter1 Capture Event         | -

// ADMUX
// ---------|---------------------------------------|-------------------------------------------------------------|
// 7	REFS1	| Referência externa (AREF)	            | Depende da combinação com REFS0 (Tabela abaixo)             |
// 6	REFS0	| Referência externa (AREF)	            | Usa AVCC (5V) como referência                               |
// 5	ADLAR	| Resultado alinhado à direita (normal) |	Resultado alinhado à esquerda (facilita leitura de 8 bits)  |
// 4	MUX4  | -                                     |	-                                                           |
// 3  MUX3  | -                                     | -                                                           |
// 2  MUX2  | Seleção do PINO de entrada analógica  | -                                                           |
// 1  MUX1  | -                                     | -                                                           |
// 0  MUX0  | -                                     | -                                                           |

// REFS1 | REFS0 | Descrição
// ------|-------|----------------------------------
// 0	   | 0	   | AREF externa (pino AREF)
// 0	   | 1	   | AVCC (5V) com capacitor no AREF
// 1	   | 0	   | Reservado (não usar)
// 1	   | 1	   | Referência interna de 1.1V

#define PINO PC4 // ADC4 // PINOS - A0 a A5

unsigned long int LeituraAD = 0;
unsigned long int tensao = 0;

int main(){

  Serial.begin(9600);

  // CONFIGURAÇÃO DO ADC
  ADMUX = (1 << REFS0);                                               // TENSÃO DE REFERENCIA = 5V
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // CONTROLE DO CLOCK (ADPS0/1/2) VELOCIDADE DE CONVERSÃO

  while(1){

    // PINO DE LEITURA
    ADMUX = (ADMUX & 0b11111000) + PINO;

    // INICIAR A CONVERSÃO
    ADCSRA |= (1 << ADSC);

    // ESPERA A CONVERSÃO FINALIZAR
    while((ADCSRA & (1 << ADSC)) == (1 << ADSC));
    // verifica se a posição ADSC está em 1, aguarda enquanto está fazendo a conversão

    // ARMAZENAR CONVERSÃO
    // LeituraAD = ADC;            // ADC é para onde vai o valor convertido

    // LEITOR AD VARIA DE 0 A 1023 PARA 5V
    LeituraAD = ADCL;
    LeituraAD |= (ADCH << 8);

    // CALCULAR TENSÃO
    tensao = (LeituraAD * 5000) / 1023;

    Serial.print(tensao);
    Serial.println(" mV");
  }
}
