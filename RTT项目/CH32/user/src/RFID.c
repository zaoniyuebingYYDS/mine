
#include "modbus.h"
#include "stdio.h"
#include "string.h"
#include <rtconfig.h>
#include <rtdbg.h>

rt_mailbox_t mb;


static void RFID_thread(void *param)
{
    modbus_t* ctx= RT_NULL;
    ctx = modbus_new_rtu("/dev/uart2", 9600, 'N', 8, 1);
    modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485);
    modbus_connect(ctx);
    modbus_set_response_timeout(ctx, 0, 1000000);
    uint16_t recieve[4] = {0};
    int regs;
    while (1)
    {
        modbus_set_slave(ctx, 2);
        memset(recieve, 0, 8 );
        rt_thread_mdelay(1000);
        regs = modbus_read_registers(ctx, 2, 4, recieve);

        if(regs == -1)
        {
            rt_kprintf("read RFID failed! \n");
        }else{
            rt_kprintf("read RFID successed  regs number = %d,%d,%d,%d\n",recieve[0],recieve[1],recieve[2],recieve[3]);
        }

        switch(recieve[3]) {
        case 0:
                rt_kprintf("I'm read0= %d \n",recieve[3]);
                rt_thread_mdelay(500);
                break;
        case 1:
                 rt_kprintf("I'm read1= %d \n",recieve[3]);
                 rt_mb_send(mb, 1);
                 rt_thread_mdelay(2000);
                 break;
        case 2:
                 rt_kprintf("I'm read2= %d \n",recieve[3]);
                 rt_mb_send(mb, 2);
                 rt_thread_mdelay(2000);
                 break;
        case 3:
                 rt_kprintf("I'm read3= %d \n",recieve[3]);
                 rt_mb_send(mb, 3);
                 rt_thread_mdelay(2000);
                 break;
             }
        }
    //7-关闭
    modbus_close(ctx);
    //8-释放句柄
    modbus_free(ctx);
}


 static int rtu_RFID_init(void)
{

    rt_thread_t rfid_tid;
    mb = rt_mb_create("mbox", 1, RT_IPC_FLAG_FIFO);
    if (mb != RT_NULL)
        rt_kprintf("mb creat successed! \n");
    else{
        rt_kprintf("mb creat failed! \n");
    }

    rfid_tid = rt_thread_create("rfid_th",
                               RFID_thread, RT_NULL,
                               2048,
                               12, 10);
    if (rfid_tid != RT_NULL)
        rt_thread_startup(rfid_tid);
    else{
        rt_kprintf("rfid_thread failed! \n");
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

INIT_APP_EXPORT(rtu_RFID_init);
