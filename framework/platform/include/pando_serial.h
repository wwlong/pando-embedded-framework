/*********************************************************
 * File name: pando_serial.h
 * Author: xiaoxiao
 * Versions: 1.0
 * Description: declare serial port comunication
 * History:
 *   1.Date: Oct 28, 2015
 *     Author: xiaoxiao
 *     Modification:
 *********************************************************/

#ifndef _PANDO_SERIAL_H_
#define _PANDO_SERIAL_H_

//define data handler callback
typedef void (* data_handler_callback)(unsigned char *buffer, unsigned short length);

/******************************************************************************
 * FunctionName : serial_port1_init
 * Description  : initialize serial port1
 * Parameters   : 
 * Returns      : 
*******************************************************************************/
void serial_port1_init(void);

/******************************************************************************
 * FunctionName : serial_port1_send
 * Description  : send data via serial port1
 * Parameters   : buffer: the data buffer to send
 *                length: the data length to send
 * Returns      : the data length that be sent successfully
*******************************************************************************/
unsigned short serial_port1_send(unsigned char *buffer, unsigned short length);

/******************************************************************************
 * FunctionName : on_serial_port1_recv_data_callback
 * Description  : register the handler callback when serial port1 receiving data
 * Parameters   : data_recv_cb: the callback handler
 * Returns      : 
*******************************************************************************/
void on_serial_port1_recv_data_callback(data_handler_callback data_recv_cb);

#endif /* _PANDO_SERIAL_H_ */
