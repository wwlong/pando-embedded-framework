/******************************************************* 
* File name： pwr_ctrl.h
* Author   :  wfq
* Versions :  1.0
* Description: power control driver: control power of oed, gd_tf, and wifi module.
* History: 
*   1.Date:    2015-5-20 
*     Author:  wfq
*     Action:  create
*********************************************************/

#ifndef __PWR_CTRL__
#define __PWR_CTRL__

void init_pwr_ctrl(void);

void set_pwr_oed(void);
void reset_pwr_ode(void);

void set_pwr_gd_tf(void);
void reset_pwr_gd_tf(void);

void set_pwr_wifi(void);
void reset_pwr_wifi(void);

void set_pwr_all(void);
void reset_pwr_all(void);

#endif
