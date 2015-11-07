/*******************************************************
 * File name: pando_files.h
 * Author: xiaoxiao
 * Versions: 1.0
 * Description: This module is to used to define the file interfaces.
 * History:
 *   1.Date:
 *     Author:
 *     Modification:
 *********************************************************/

#ifndef _PANDO_FILES_H_
#define _PANDO_FILES_H_

/******************************************************************************
 * FunctionName : file_open
 * Description  : open file
 * Parameters   : path: file name
 * Returns      : if succeeds, return the file descriptor; else, return -1.
*******************************************************************************/
int file_open(const char *path);

/******************************************************************************
 * FunctionName : file_read
 * Description  : read data from the file.
 * Parameters   : fd: the descriptor of the file.
 *              : nbytes: the bytes to read.
 * Returns      : if succeeds, return the bytes have been read; else, return -1.
*******************************************************************************/
signed short file_read(int fd, void *buf, unsigned short nbytes);

/******************************************************************************
 * FunctionName : file_write
 * Description  : write data to the file.
 * Parameters   : fd: the descriptor of the file.
 *              : nbytes: the bytes to write.
 * Returns      : if succeeds, return "nbytes"; else, return -1.
*******************************************************************************/
signed short file_write(int fd, const void *buf, unsigned short nbytes);

/******************************************************************************
 * FunctionName : file_close
 * Description  : close the file.
 * Parameters   : fd: the descriptor of the file.
 * Returns      : if succeeds, return 0; else, return -1.
*******************************************************************************/
int file_close(int fd);

#endif /* _PANDO_FILES_H_ */
