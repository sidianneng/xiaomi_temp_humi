#include "log.h"
#include <stdarg.h>
#include <string.h>

void Log_Init(void)
{
#if DEBUG_LOG
    MX_USART2_UART_Init();
#endif
}

void itoa(int value, char *str, int base) {
    char *ptr = str, *ptr1 = str, tmp_char;
    int tmp_value;
    if (base < 2 || base > 36) {
        *str = '\0';
        return;
    }
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[tmp_value - value * base];
    } while (value);

    if (tmp_value < 0 && base == 10) *ptr++ = '-';
    *ptr-- = '\0';

    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}

int8_t Log_Printf(char *format, ...)
{
#if DEBUG_LOG
    char log_buf[MAX_LOG_BUF_LEN] = { 0 };
    char *buf_ptr = log_buf;
    uint16_t time_cnt = 0;

    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int value = va_arg(args, int);
                char temp[16];
                itoa(value, temp, 10); 
                strcpy(buf_ptr, temp);
                buf_ptr += strlen(temp);
            } else if (*format == 'x') {
                int value = va_arg(args, int);
                char temp[16];
                itoa(value, temp, 16); 
                strcpy(buf_ptr, temp);
                buf_ptr += strlen(temp);
            } else if (*format == 's') {
                char *str = va_arg(args, char*);
                strcpy(buf_ptr, str);
                buf_ptr += strlen(str);
            } else {
                *buf_ptr++ = '%';
                *buf_ptr++ = *format;
            }
        } else {
            *buf_ptr++ = *format;
        }
        format++;
    }
    *buf_ptr = '\0';

    va_end(args);

    for (char *p = log_buf; *p; p++) {
        LL_USART_TransmitData8(USART2, *p);
        while(LL_USART_IsActiveFlag_TC(USART2) == 0){
            LL_mDelay(1);
            if(time_cnt++ > 1000)
                return -1;
        }
    }
#endif
    return 0;
}

