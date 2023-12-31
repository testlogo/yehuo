#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "key.h"
#include "bsp_led.h"

/** 按键按下标置宏
* 按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
* 若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
*/
#define KEY_ON  1
#define KEY_OFF 0

/**
* @brief   检测是否有按键按下
* @param  GPIOx:具体的端口, x可以是（A...G）
* @param  GPIO_PIN:具体的端口位， 可以是GPIO_PIN_x（x可以是0...15）
* @retval  按键的状态
*     @arg KEY_ON:按键按下
*     @arg KEY_OFF:按键没按下
*/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    /*检测是否有按键按下 */
    if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) {
        /*等待按键释放 */
        while (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);
        return  KEY_ON;
    } else
        return KEY_OFF;
}
int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。
	/* LED 端口初始化 */
    LED_GPIO_Config();

    /*初始化按键*/
    Key_GPIO_Config();

    /* 轮询按键状态，若按键按下则反转LED */
    while (1) {
        if ( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  ) {
            /*LED1反转*/
            LED1_TOGGLE;
        }

        if ( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  ) {
            /*LED2反转*/
            LED2_TOGGLE;
        }
    }
}


