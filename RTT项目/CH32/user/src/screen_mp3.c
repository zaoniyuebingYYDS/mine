/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-28     Administrator       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "modbus.h"
#include "stdio.h"
#include "string.h"
#include "RFID.h"

modbus_t *ctx1 = RT_NULL;
rt_thread_t touch_screen_tid;
rt_uint32_t mbre;
extern rt_mailbox_t mb;
void touch_screen_thread(void *param)
{
    modbus_t* ctx1;
    ctx1 = modbus_new_rtu("/dev/uart4", 9600, 'N', 8, 1);
    if (ctx1 != NULL)
    {
       rt_kprintf("success to create the libmodbus context\n");
     }
    modbus_rtu_set_serial_mode(ctx1, MODBUS_RTU_RS485);
    modbus_connect(ctx1);
    modbus_set_response_timeout(ctx1, 0, 1000000);
    uint16_t send1[3]={1,0,1};
    uint16_t send2[3]={1,0,2};
    uint16_t send3[3]={1,0,3};
    while (1)
    {
        int i =0;
        rt_mb_recv(mb, &mbre, RT_WAITING_FOREVER);
        rt_kprintf("mbre=%d\n",mbre);
        rt_thread_mdelay(500);
        i= mbre;
        switch(i)
       {
          case 1:
               modbus_set_slave(ctx1, 1);
               modbus_write_register(ctx1, 10, 1);
               rt_thread_mdelay(1000);
               int c = modbus_set_slave(ctx1, 3);
               rt_kprintf("I'm  %d \n",c);
               modbus_write_registers(ctx1, 32, 3, send1);
               break;
          case 2:
               modbus_set_slave(ctx1, 1);
               modbus_write_register(ctx1, 10, 2);
               rt_thread_mdelay(1000);
               modbus_set_slave(ctx1, 3);
               modbus_write_registers(ctx1, 32, 3, send2);
               break;
          case 3:
               modbus_set_slave(ctx1, 1);
               modbus_write_register(ctx1, 10, 3);
               rt_thread_mdelay(1000);
               modbus_set_slave(ctx1, 3);
               modbus_write_registers(ctx1, 32, 3, send3);
               break;
        }
    }
    modbus_close(ctx1);
    modbus_free(ctx1);
}

int touch_screen_init(void)
{

    rt_thread_t touch_screen_tid;
    touch_screen_tid = rt_thread_create("touch_screen_th",
                               touch_screen_thread, RT_NULL,
                               2048,
                               13, 10);
    if (touch_screen_tid != RT_NULL){
        rt_thread_startup(touch_screen_tid);
        rt_kprintf("create touch_screen_thread succeed! \n");
    }
    else{
        rt_kprintf("create touch_screen_thread failed! \n");
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

INIT_APP_EXPORT(touch_screen_init);
