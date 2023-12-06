#ifndef MYFILE_H
#define MYFILE_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

ssize_t readfile(const char filename[], char * buf, ssize_t size)
{
    char * tbuf = buf;
    int fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        std::cout << "error opening file \"" << filename << '\"' << std::endl;
        exit(1);
    }
    ssize_t total_size = 0;  // total number of bytes read
    while (1)
    {
        ssize_t result_size = read(fd, buf, size);
        if (result_size == 0) break; // EOF
        if (result_size == -1)
        {
            std::cout << "error reading file \"" << filename << '\"'
                      << std::endl;
            exit(1);
        }

        buf += result_size;
        total_size += result_size;
        if (total_size > size)
        {
            std::cout << "buffer overflow on reading file \"" << filename
                      << "\". total_size:" << total_size
                      << ". size:" << size << '.'
                      << std::endl;
            exit(1);
        }
    }
    
    // Insert '\0' if necessary.
    if (tbuf[total_size - 1] != 0)
    {
        std::cout << "warning reading file \"" << filename << '\"'
                  << ": last byte not '\\0'. '\\0' added to buffer."
                  << std::endl;
        tbuf[total_size] = 0;
        ++total_size;
    }

    // Check characters are visible (ASCII code 32 to 126) or '\0' or '\t'
    // or '\n';
    for (int i = 0; i < total_size; ++i)
    {
        char ch = tbuf[i];
        if (ch != '\0' && ch != '\t' && ch != '\n' && !(32 <= ch && ch <= 126))
        {
            std::cout << "invalid char found at index " << i
                      << ": ASCII code " << (unsigned int)(ch) << '\n';
            exit(1);
        }
    }
    
    return total_size;
}

#endif
