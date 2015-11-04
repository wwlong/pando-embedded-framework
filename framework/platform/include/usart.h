/*********************************************************
 * File name: usart.h
 * Author: xiaoxiao
 * Versions: 1.0
 * Description: declare usart operation used in the framework.
 * History:
 *   1.Date: Oct 28, 2015
 *     Author: xiaoxiao
 *     Modification:
 *********************************************************/

#ifndef _USART_H_
#define _USART_H_

//define data handler callback
typedef void (* data_handler_callback)(unsigned char *buffer, unsigned short length);

/******************************************************************************
 * FunctionName : usart1_init
 * Description  : initialize usart1
 * Parameters   : 
 * Returns      : 
*******************************************************************************/
void usart1_init(void);

/******************************************************************************
 * FunctionName : usart1_send
 * Description  : send data via usart1
 * Parameters   : buffer: the data buffer to send
 *                length: the data length to send
 * Returns      : the data length that be sent successfully
*******************************************************************************/
unsigned short usart1_send(unsigned char *buffer, unsigned short length);

/******************************************************************************
 * FunctionName : on_usart1_recv_data_callback
 * Description  : register the handler callback when usart1 receiving data
 * Parameters   : data_recv_cb: the callback handler
 * Returns      : 
*******************************************************************************/
void on_usart1_recv_data_callback(data_handler_callback data_recv_cb);

#endif /* _USART_H_ */
