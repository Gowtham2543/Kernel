void kmain(void)
{
    const char *str = "Hello World";
    char *videoPtr = (char *)0xb8000; // Video memory begins here
    unsigned int i = 0;
    unsigned int j = 0;

    while(j < 80 * 25 * 2)   // 25 lines with each 80 column. Each element takes 2 bytes
    {   
        // First byte ASCII char
        videoPtr[j] = ' ';
        // Second byte attribute-byte (Colour)
        videoPtr[j + 1] = 0x07;

        j = j + 2;
    } 

    j = 0;

    while(str[j] != '\0')
    {
        videoPtr[i] = str[j];
        videoPtr[i + 1] = 0x07;
        j++;
        i = i + 2;
    }

    return;
}