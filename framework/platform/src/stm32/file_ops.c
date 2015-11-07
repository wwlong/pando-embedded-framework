#include <stdio.h>
#include "platform/include/pando_files.h"
#include "fatfs/ff.h"

#define MAX_FILE 5

// declare the map between file descriptor between real file structure
// the 0 is not used as the file descriptor.
FIL g_fil_map[MAX_FILE + 1] = { NULL };

int file_open(const char *path)
{
    FIL *p_fil;
    FRESULT res = f_open(p_fil, path, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
    if(res != FR_OK)
    {
        printf("open file failed! file_path:%s, res:%d.\n", path, res);
        f_close(p_fil);
        return -1;
    }

    for(char i = 1; i <= MAX_FILE; i++)
    {
        if(g_fil_map[i].fs == NULL)
        {
            g_fil_map[i] = *p_fil;
            return i;
        }
    }

    return -1;
}


signed short file_read(int fd, void *buf, unsigned short nbytes)
{
    if(fd > MAX_FILE || fd < 0 || g_fil_map[fd].fs == NULL)
    {
        return -1;
    }

    UINT bytes_read;
    FRESULT res;
    res = f_read(&g_fil_map[fd], buf, nbytes, &bytes_read);
    if(res != FR_OK)
    {
        printf("read file failed! res:%d.\n", res);
        f_close(&g_fil_map[fd]);
        return -1;
    }

    return bytes_read;
}

signed short file_write(int fd, const void *buf, unsigned short nbytes)
{
    if(fd > MAX_FILE || fd < 0 || g_fil_map[fd].fs == NULL)
    {
        return -1;
    }

    UINT bytes_written;
    FRESULT res;
    res = f_write(&g_fil_map[fd], buf, nbytes, &bytes_written);
    if(res != FR_OK)
    {
        printf("write file failed! res:%d.\n", res);
        f_close(&g_fil_map[fd]);
        return -1;
    }

    return bytes_written;
}

int file_close(int fd)
{
    if(fd > MAX_FILE || fd < 0 || g_fil_map[fd].fs == NULL)
    {
        return -1;
    }

    FRESULT res;
    res = f_close(&g_fil_map[fd]);
    if(res != FR_OK)
    {
        return -1;
    }

    return 0;
}
