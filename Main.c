#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "uart.h"
#include <stdio.h>

void ADC1_Init(void);
void Delay_ms (uint16_t time);
int main(void)
{
    char buffer[50];
    uint16_t adcValue;
    float voltage;

    UART1_Init(9600);   
    ADC1_Init();     

    while (1)
    {
        // Bat dau chuyen doi
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);

        // Ðoi ADC xong
        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

        // Lay giá tri ADC
        adcValue = ADC_GetConversionValue(ADC1);

        // Ðoi sang dien ap (Vref = 3.3V)
        voltage = (adcValue * 3300.0) / 4095.0;

        // In ra UART
        sprintf(buffer, "ADC: %d, Voltage: %.2f mV\r\n", adcValue, voltage);
        UART1_SendString(buffer);
        Delay_ms(500);
    }
}

void ADC1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    ADC_InitTypeDef ADC_InitStruct;

    // Bat clock GPIOA và ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    // PA0 = ADC Channel 0
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Cau hình ADC1
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_Cmd(ADC1, ENABLE);

    // Hieu chuan ADC
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));

    // Cau hình kênh 0
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
}
void Delay_ms (uint16_t time){
	uint16_t i,j;
	for(i = 0; i < time; i++){
		for(j = 0; j < 0x2AFF; j++);
		}
}
