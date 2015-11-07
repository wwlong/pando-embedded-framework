/******************************************************* 
* File name： exfuns.h
* Author   :  wfq
* Versions :  1.0
* Description: 扩展文件处理函数
* History: 
*   1.Date:    2015-1-10 
*     Author:  wfq
*     Action:  create
*********************************************************/ 




#ifndef __EXFUNS_H
#define __EXFUNS_H 			   
#include <stm32f10x.h>
#include "ff.h"

extern FATFS *g_ldisk[2];  
extern FIL *g_file;	 
extern FIL *g_ftemp;	 
extern UINT g_br,g_bw;
extern FILINFO g_fileinfo;
extern DIR g_dir;
extern u8 *g_fatbuf;//SD卡数据缓存区


//f_typetell返回的类型定义
//根据表FILE_TYPE_TBL获得.在exfuns.c里面定义
#define T_BIN		0X00	//bin文件
#define T_LRC		0X10	//lrc文件
#define T_NES		0X20	//nes文件
#define T_TEXT		0X30	//.txt文件
#define T_C			0X31	//.c文件
#define T_H			0X32    //.h文件
#define T_FLAC		0X4C	//flac文件
#define T_BMP		0X50	//bmp文件
#define T_JPG		0X51	//jpg文件
#define T_JPEG		0X52	//jpeg文件		 
#define T_GIF		0X53	//gif文件  

 
u8 exfuns_init(void);							//申请内存
u8 f_typetell(u8 *fname);						//识别文件类型
u8 exf_getfree(u8 *drv,u32 *total,u32 *free);	//得到磁盘总容量和剩余容量
u32 exf_fdsize(u8 *fdname);						//得到文件夹大小			 																		   
#endif


