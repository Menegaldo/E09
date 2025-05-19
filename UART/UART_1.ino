#include <avr/io.h>
#include <avr/interrupt.h>  // Necessário para interrupções

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR (F_CPU / 16 / BAUD - 1)

// Inicializa UART para transmissão e recepção
void UART_Init(unsigned int ubrr) {

    // Configura Baud Rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // 8 bits, 1 stop bit, sem paridade
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    // Habilita transmissor (TX) e receptor (RX), além da interrupção RX
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Habilita interrupção de recepção
}

// Transmite um único caractere via UART
void UART_TX(char data) {

    while (!(UCSR0A & (1 << UDRE0)));  // Espera buffer de transmissão estar pronto
    UDR0 = data;                       // Escreve o caractere
}

// Função de interrupção para RX
ISR(USART_RX_vect) {

    char received = UDR0;  // Lê o dado recebido
    
    UART_TX(received);  // Echo (envia de volta o dado recebido)
    UART_TX('\n');      // Quebra de linha
}

int main(void) {

    UART_Init(MYUBRR);  // Inicializa UART para TX e RX

    UART_TX('H');  // Envia caractere 'H'
    UART_TX('\n'); // Quebra de linha

    sei();  // Habilita interrupções globais

    while (1) {
        // O código principal pode ficar vazio, pois a recepção é tratada por interrupção
    }
}
