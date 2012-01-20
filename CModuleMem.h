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

#include "IModule.h"

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
		__LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

class CModuleMem : public IModule
{
    public:
        CModuleMem() {};
        virtual ~CModuleMem() {};

        virtual StatusType Configure(Arguments& params)
        {
            args = params;
        	return STATUS_SUCCESS;
        };

        virtual StatusType Unconfigure(Arguments& params)
        {
            return STATUS_SUCCESS;
        };

        virtual StatusType Start(void);
        virtual StatusType Stop(void);

        virtual StatusType ReadByte(DataType& d);
        virtual StatusType ReadWord(DataType& d);
        virtual StatusType ReadBlock(DataType& d);

        virtual StatusType WriteByte(DataType& d);
        virtual StatusType WriteWord(DataType& d);
        virtual StatusType WriteBlock(DataType& d);

        /* Parse and print options passed from command line */       
        virtual StatusType ParseCmd(std::string& s, Arguments& args);
        virtual StatusType PrintCmd(Arguments& args, std::string& s);

    private:
        int fd;
        void *map_base, *virt_addr;
};

/* vim: set ts=4 sw=4 et: */
