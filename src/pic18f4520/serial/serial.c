/*============================================================================*/
#include "serial.h"
/*============================================================================*/
#include <stdint.h>

/*============================================================================*/
void Serial_1_Config(serial_config_t* serialConfig) {

    /*
        SPEN: Serial Port Enable bit
            1 = Serial port enabled (configures RX/DT
            0 = Serial port disabled (held in Reset)
     */
    RCSTAbits.SPEN = 0x00;

    /*
        SYNC: EUSART Mode Select bit
            1 = Synchronous mode
            0 = Asynchronous mode
     */
    TXSTAbits.SYNC = serialConfig->serial_sync_com;



    /*
        TX9: 9-Bit Transmit Enable bit
            1 = Selects 9-bit transmission
            0 = Selects 8-bit transmission
     */
    TXSTAbits.TX9 = serialConfig->serial_data_length;

    /*
     * RX9: 9-Bit Receive Enable bit
        1 = Selects 9-bit reception
        0 = Selects 8-bit reception
     */

    RCSTAbits.RX9 = serialConfig->serial_data_length;
    
    /*
        TXEN: Transmit Enable bit(1)
            1 = Transmit enabled
            0 = Transmit disabled
     */
    TXSTAbits.TXEN = 0x01;
    
    
    /*
     * CREN: Continuous Receive Enable bit
        Asynchronous mode:
            1 = Enables receiver
            0 = Disables receiver
        Synchronous mode:
            1 = Enables continuous receive until enable bit, CREN, is cleared (CREN overrides SREN)
            0 = Disables continuous receive
    */
    RCSTAbits.CREN = 0x01;
    
    /*
        SPEN: Serial Port Enable bit
            1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
            0 = Serial port disabled (held in Reset)
     */
    RCSTAbits.SPEN = 0x01;



}


/*============================================================================
 * To set up an Asynchronous Reception:
    1. Initialize the SPBRGH:SPBRG registers for the appropriate baud rate.
        Set or clear the BRGH and BRG16 bits, as required, to achieve the
        desired baud rate.
    2. Enable the asynchronous serial port by clearing bit, SYNC, and setting 
        bit, SPEN.
    3. If interrupts are desired, set enable bit, RCIE.
    4. If 9-bit reception is desired, set bit, RX9.
    5. Enable the reception by setting bit, CREN.
    6. Flag bit, RCIF, will be set when reception is complete and an interrupt 
       will be generated if enable bit, RCIE, was set.
    7. Read the RCSTA register to get the 9th bit (if enabled) and determine if 
       any error occurred during reception.
    8. Read the 8-bit received data by reading the RCREG register.
    9. If any error occurred, clear the error by clearing enable bit, CREN.
    10. If using interrupts, ensure that the GIE and PEIE bits in the INTCON 
        register (INTCON<7:6>) are set.
 */

/*============================================================================*/
void Serial_Config(long int desired_baud) {
    /*
     *                  BAUD RATE FORMULAS
     *  BRG16 | BRGH  |   UART MODE     |  Baud Rate Formula
     *   1    |   1   | 16 bit   async  |   FOSC/[4 (n + 1) ]
     * 1 - 0  | 0 - 1 | 8/16 bit async  |   FOSC/[16 (n + 1)]
     *   0    |   0   | 8 bit    async  |   FOSC/[64 (n + 1)]
     */

    uint8_t brg_value;
    brg_value = (_XTAL_FREQ / (desired_baud * 64)) - 1;

    SPBRG = brg_value;

    TXSTAbits.SYNC = 0x00; // Asynchronous mode

    RCSTAbits.SPEN = 0x01; // Enable serial port

    TXSTAbits.TX9 = 0x00; // Define 9 bits of data

    TXSTAbits.TXEN = 0x01; // Enabel serial transmit


}

/*============================================================================*/
void Serial_Transmit(uint8_t data) {
    TXREG = data;
}

/*============================================================================
 * To set up an Asynchronous Transmission:
    1.  Initialize the SPBRGH:SPBRG registers for the appropriate baud rate. 
        Set or clear the BRGH and BRG16 bits, as required, to achieve the
        desired baud rate.
    2.  Enable the asynchronous serial port by clearing bit, SYNC, and setting 
        bit, SPEN.
    3.  If interrupts are desired, set enable bit, TXIE.
    4.  If 9-bit transmission is desired, set transmit bit, TX9. 
        Can be used as address/data bit.
    5.  Enable the transmission by setting bit, TXEN, which will also set bit, TXIF.
    6.  If 9-bit transmission is selected, the ninth bit
        should be loaded in bit, TX9D.
    7.  Load data to the TXREG register (starts transmission).
    8.  If using interrupts, ensure that the GIE and PEIE bits in the INTCON 
        register (INTCON<7:6>) are set.
 */

