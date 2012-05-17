#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "DeviceInterface.h"

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
		__LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

class DeviceMemory : public DeviceInterface
{
    public:
        DeviceMemory() {};
        virtual ~DeviceMemory() {};

        virtual StatusType configure(Arguments& params)
        {
            args = params;
        	return STATUS_SUCCESS;
        };

        virtual StatusType unconfigure(Arguments& params)
        {
            return STATUS_SUCCESS;
        };

        virtual StatusType start(void);
        virtual StatusType stop(void);

        virtual StatusType read_byte(DataType& d);
        virtual StatusType read_word(DataType& d);
        virtual StatusType read_block(DataType& d);

        virtual StatusType write_byte(DataType& d);
        virtual StatusType write_word(DataType& d);
        virtual StatusType write_block(DataType& d);

        /* Parse and print options passed from command line */       
        virtual StatusType parse_cmd(std::string& s, Arguments& args);
        virtual StatusType print_cmd(Arguments& args, std::string& s);

    private:
        int fd;
        void *map_base, *virt_addr;
};

/* vim: set ts=4 sw=4 et: */
