/*============================================================================*/
#ifndef SERIAL_H
#define	SERIAL_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
/*============================================================================*/
#define _XTAL_FREQ 10000000
/*============================================================================*/
typedef enum {
    SERIAL_ASSYNC_MODE = 0x00,
    SERIAL_SYNC_MODE   = 0x01
}SERIAL_SYNC_COM;
/*============================================================================*/
typedef enum {
    SERIAL_DATA_LENGTH_8 = 0x00, 
    SERIAL_DATA_LENGTH_9 = 0x01
}SERIAL_DATA_LENGTH;
/*============================================================================*/
typedef enum {
    SERIAL_MASTER_MODE = 0x00, 
    SERIAL_SLAVE_MODE  = 0x01
}SERIAL_OP_MODE;

typedef enum {
    SERIAL_BAUD_9600 = 0x00, 
    SERIAL_BAUD_11250 = 0x01,
}SERIAL_DESIRED_BAUD;
/*============================================================================*/
typedef struct {
    SERIAL_SYNC_COM serial_sync_com;
    SERIAL_DATA_LENGTH serial_data_length; 
    SERIAL_OP_MODE serial_op_mode;
}serial_config_t;
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/    
    void Serial_Config( long int desired_baud /* serial_config_t* serialConfig */);
/*============================================================================*/
    void Serial_Transmit( uint8_t data );
    uint8_t Serial_Receive( void );     
/*============================================================================*/
    void Serial_BufferTransmit( uint8_t* dataBuffer );
    uint8_t Serial_BufferReceive( void );
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* SERIAL_H */
/*============================================================================*/
