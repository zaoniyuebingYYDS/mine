/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-28     Administrator       the first version
 */
/*#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "modbus.h"
#include "stdio.h"
#include "string.h"


modbus_t *ctx1 = RT_NULL;
rt_thread_t touch_screen_tid;
uint16_t send[3]={1,0,1};
void touch_screen_thread(void *param)
{
    modbus_t* ctx1;
    ctx1 = modbus_new_rtu("/dev/uart4", 9600, 'N', 8, 1);
    if (ctx1 != NULL) {
                    rt_kprintf("success to create the libmodbus context\n");
                }
    modbus_rtu_set_serial_mode(ctx1, MODBUS_RTU_RS485);
    modbus_connect(ctx1);
    modbus_set_response_timeout(ctx1, 0, 1000000);

    uint16_t recieve[16] = {0};

    int regs=6;
    while (1)
    {
               modbus_set_slave(ctx1, 3);
               int c = modbus_write_registers(ctx1, 32, 3, send);
               rt_kprintf("I'm  %d \n",c);
               rt_thread_mdelay(10000);

//        modbus_set_slave(ctx1, 1);
//        memset(recieve, 0, 16);
//        regs = modbus_read_registers(ctx1, 1, 1, recieve);
//        if(regs == -1)
//        {
//            rt_kprintf("read touch_screen failed! \n");
//            continue;
//        }else{
//            rt_kprintf("read touch_screen successed  regs=%d\n",regs);
//        }
//
//        rt_kprintf("I'm read %d \n",recieve[0]);
//        rt_thread_mdelay(3000);
//        modbus_write_register(ctx1, 10, 0);
//        rt_thread_mdelay(10000);
//        modbus_write_register(ctx1, 10, 1);
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

INIT_APP_EXPORT(touch_screen_init);*/
