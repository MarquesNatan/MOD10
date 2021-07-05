/*============================================================================*/
#include <xc.h>
#include <stdint.h>
/*============================================================================*/
#include "pic18f4520/fuse/fuse.h"
#include "pic18f4520/timer/timer.h"
#include "pic18f4520/interrupt/interrupt.h"
/*============================================================================*/
#include "pic18f4520/gpio/gpio.h"
#include "board/pinout/pinout.h"
/*============================================================================*/
#include "board/display_7_seg/display_7_seg_map.h"
/*============================================================================*/
static uint8_t global_counter;
/*============================================================================*/
// Configura o timer
timer_config_t timerConfig = {
    .timer_length = TIMER_LENGTH_16, 
    .timer_clk_src = TIMER_CLKO_SRC,
    .timer_transition = TIMER_TRANSITION_LOW_HIGH,
    .timer_prescaler_assign = TIMER_PRESCALER_IS_ASSIGNED,
    .timer_prescaler_value = TIMER_PRESCALER_256
};
/*============================================================================*/
display_7_seg_t display_7_seg = {
  
    // Incia os contadores do timer
    .characters_vector = {
        NUMBER_0, NUMBER_1, NUMBER_2, 
        NUMBER_3, NUMBER_4, NUMBER_5,  
        NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9
  },
    // Marca a posição atual do vetor de caracteres
  .characters_vector_pos = 0x00
};
/*============================================================================*/
// Função de interrupção, confirma a fonte de interrupção, chama a função de 
// tratamento do display de 7 segmentos e reinicia o contador do timer
void __interrupt() TC0INT(void){
    if (INTCONbits.TMR0IF == 0x01) {
        
        // Função que atuliza o display
        // global_counter = display_show(&display_7_seg);
      DIGITAL_PIN_TOGGLE(LED_HEARTBEAT1_PORT, LED_HEARTBEAT1_MASK);
      TMR0 = 0xE17B; //  Reinicia  o contador do timer
      INTCONbits.T0IF = 0x00;  // Limpa a flag de interrupção
    }
}

/*============================================================================*/
void main(void) {
    
    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, LED_HEARTBEAT1_PORT, LED_HEARTBEAT1_MASK);
    
    Display_Config();            // Configura o display como saída
    Interrupt_GlobalEnable();    // Habilita as interrupções globais
    Timer0_Config(&timerConfig); // Configura o timer 0
    
    
    while(1){
        // Loop infinito -> Usamos apenas interrupção
    }
    
    return;
}
/*============================================================================*/