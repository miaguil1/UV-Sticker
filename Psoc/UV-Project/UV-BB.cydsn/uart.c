#include "uart.h"

void send_string(char *text)
{
    unsigned int text_length = strlen(text);
    unsigned int message_length = text_length + 2;
    char message[message_length]; //Initializes the Character Array
    message[0] = 's'; //Places an s as the first element in the arrray
    message[message_length-1] = '\n'; //Places a new line character in the last spot in the array
    
    //Placing Value in Packet between new message carrier and last message carrier
    for(unsigned int j = 1; j<message_length; j++)
    {
        message[j] = text[j-1];    
    }
    
    //Sends the Value over UART
    for(unsigned int i = 0; i<message_length; i++)
    {
        send_char(message[i]);           
    }
}

void send_char(char character)
{
    UART_UartPutChar(character);
}

void send_uint8(uint8 number8)
{
    UART_UartPutChar(number8);
}

void send_uint16(uint16 number16)
{
    uint8 part1 = number16 & 0xFF;
    uint8 part2 = (number16 >> 8) & 0xFF;
    send_uint8(part1);
    send_uint8(part2);
}

void send_uint32(uint32 number32)
{
    uint8 part1 = number32 & 0xFF;
    uint8 part2 = (number32 >> 8) & 0xFF;
    uint8 part3 = (number32 >> 16) & 0xFF;
    uint8 part4 = (number32 >> 24) & 0xFF;
    send_uint8(part1);
    send_uint8(part2);
    send_uint8(part3);
    send_uint8(part4);
}