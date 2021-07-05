/*============================================================================*/
#ifndef DISPLAY_7_SEG_MAP_H
#define DISPLAY_7_SEG_MAP_H
/*============================================================================*/
#include <stdint.h>
#include "../../pic18f4520/gpio/gpio.h"
/*============================================================================
 *      __A__           PINOS PORTB: 0b P7 P6 P5 P4 P3 P2 P1 P0
 *   F |     | B                        .  G  F  E  D  C  B  A
 *     |__G__|
 *   E |     | C
 *     |_____|
 *        D
==============================================================================*/
// Funções para concatenação  de comandos PORT e TRIS
#define PASTE2D(a, b)       a##b

#define OUTPUT_DISPLAY_CONFIG(a)         PASTE2D(TRIS, a)        
#define DISPLAY_SHOW_PORT(a)             PASTE2D(PORT, a)

/*============================================================================*/
// Definição do port que o display está conectado
#define DISPLAY_PORT               B       // Port de saída para o display

/*============================================================================*/
// Quantidade de caracteres definidos para o contador
#define characters_vector_length        0x0A

/*============================================================================*/
// Defineição de caracteres no display de 7 segmentos catodo comum
#define GENERIC_NUMBER      NUMBER_
//                        .GFEDCBA      // Segmentos em nível Alto:
#define NUMBER_0        0b00111111      // 0 = ABCDEF -> ON
#define NUMBER_1        0b00000110      // 1 = BC     -> ON
#define NUMBER_2        0b01011011      // 2 = ABGED  -> ON
#define NUMBER_3        0b01001111      // 3 = ABCDG  -> ON
#define NUMBER_4        0b01100110      // 4 = FGCB   -> ON
#define NUMBER_5        0b01101101      // 5 = ACDFG  -> ON
#define NUMBER_6        0b01111101      // 6 = ACDEFG -> ON
#define NUMBER_7        0b00000111      // 7 = ABC    -> ON
#define NUMBER_8        0b01111111      // 8 = ABCDEFG-> ON
#define NUMBER_9        0b01101111      // 9 = ABCDFG -> ON

/*============================================================================*/
// Struct para acesso a funções do display
typedef struct {
    uint8_t characters_vector [characters_vector_length];
    uint8_t characters_vector_pos;
}display_7_seg_t;

/*============================================================================*/
// Declaração de funções para configuração de apresentação de dados no display
void Display_Config(void);      
uint8_t display_show(display_7_seg_t *displayShow);

/*============================================================================*/
#endif /* DISPLAY_7_SEG_MAP_H */
/*============================================================================*/