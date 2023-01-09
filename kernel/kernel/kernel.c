#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint16_t* terminal_buffer;
uint8_t terminal_colour;

uint16_t generate_vga_2byte(char data, uint8_t foreground, uint8_t background)
{
    return (uint16_t) data | (uint16_t) ((foreground | (background << 4)) << 8);
}

void terminal_initialize()
{  
    terminal_row = 0;
    terminal_column = 0;
    terminal_buffer = (uint16_t*) 0xB8000;
    for(size_t j = 0; j < VGA_HEIGHT; j++)
    {
        for(size_t i = 0; i < VGA_WIDTH; i++)
        {   
            terminal_buffer[j * VGA_WIDTH + i] = generate_vga_2byte(' ', 7, 0);
        }
    }
}

size_t strlen(const char* data)
{
    size_t len = 0;
    while(data[len])
    {
        len += 1;
    }
    return len;
}

void terminal_putchar(const char data)
{
    // if(data == "\n")
    // {
    //     terminal_column = 1;
    //     terminal_row += 1;
    //     return;
    // }
    terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = generate_vga_2byte(data, 7, 0);
    if(++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
    }
}
void terminal_write(const char* data)
{
    size_t len = strlen(data);
    for(size_t i = 0; i < len; i++)
    {
        terminal_putchar(data[i]);
    }
}
void kmain(void)
{   

    terminal_initialize();
    terminal_write("Gowtham");
    // const char *str = "Hello World";
    // char *videoPtr = (char *)0xb8000; // Video memory begins here
    // unsigned int i = 0;
    // unsigned int j = 0;

    // while(j < 80 * 25 * 2)   // 25 lines with each 80 column. Each element takes 2 bytes
    // {   
    //     // First byte ASCII char
    //     videoPtr[j] = ' ';
    //     // Second byte attribute-byte (Colour)
    //     videoPtr[j + 1] = 0x07;

    //     j = j + 2;
    // } 

    // j = 0;

    // while(str[j] != '\0')
    // {
    //     videoPtr[i] = str[j];
    //     videoPtr[i + 1] = 0x07;
    //     j++;
    //     i = i + 2;
    // }

    return;
}