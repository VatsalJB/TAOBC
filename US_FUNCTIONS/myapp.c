#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int convert(int hex_complement)
{
    if(hex_complement&1<<16)        //negative.
    {
        int i;
        for(i = 17; i<33; i++)
        {
            hex_complement|=1<<i;
        }
    }
    return hex_complement;
}

int main()
{
    /* initialization of userspace function*/
    int file;
    int adapter_number = 0;     //check this.
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", adapter_number);
    file = open(filename, O_RDWR);
    if(file<0)
    {
        perror("File not opened");
    }
    int addr = 0x1E;
    if(ioctl(file, I2C_SLAVE, addr)<0)
    {
        perror("ioctl could not open file");
    }
    i2c_smbus_write_byte_data(file, 0x00, 0x70);
    i2c_smbus_write_byte_data(file, 0x01, 0xA0);
    /* End of initialization*/
    //measurement
    while(1)
    {
        i2c_smbus_write_byte_data(file, 0x02, 0x01);
        int hex_complement_x = i2c_smbus_read_word_data (file, 0x03);
        int hex_complement_y = i2c_smbus_read_word_data (file, 0x07);
        int hex_complement_z = i2c_smbus_read_word_data (file, 0x05);
        int final_x = convert(hex_complement_x);
        int final_y = convert(hex_complement_y);
        int final_z = convert(hex_complement_z);
        printf("%d %d %d\n", final_x, final_y, final_z);
    }
}
