#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include <kernel/tty.h>
#include "vga.h"

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint16_t* terminal_buffer;
uint8_t terminal_colour;


void terminal_initialize()
{  
    terminal_row = 0;
    terminal_column = 0;
    terminal_buffer = (uint16_t*) 0xB8000;
    for(size_t j = 0; j < VGA_HEIGHT; j++)
    {
        for(size_t i = 0; i < VGA_WIDTH; i++)
        {   
            terminal_buffer[j * VGA_WIDTH + i] = generate_vga_2byte(' ', VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        }
    }
}

void terminal_putchar(const char data)
{
    if(data == '\n')
    {
        terminal_column = 0;
        terminal_row += 1;
        return;
    }
    terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = generate_vga_2byte(data, VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
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
