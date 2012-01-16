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

#include "IDevMemModule.h"

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)


class CDevMemModule : public IDevMemModule
{
    public:
        CDevMemModule() {};
        virtual ~CDevMemModule() {};

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

StatusType CDevMemModule::Start(void)
{
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    if (args.verbose) {
    	printf("/dev/mem opened.\n");
    	fflush(stdout);
    }

    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, args.addr1 & ~MAP_MASK);
    if(map_base == (void *) -1) FATAL;

    if (args.verbose) {
    	printf("Memory mapped at address %p.\n", map_base);
    	fflush(stdout);
    }
    virt_addr = map_base + (args.addr1 & MAP_MASK);


    return STATUS_SUCCESS;
}

StatusType CDevMemModule::Stop(void)
{
	if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);

    return STATUS_SUCCESS;
}

StatusType CDevMemModule::ReadByte(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CDevMemModule::ReadWord(DataType& d)
{
	printf("reading 0x%llx\n", virt_addr);
	d.buf[0] = *((unsigned char *) virt_addr);
	printf("reading 0x%llx\n", virt_addr);

    return STATUS_SUCCESS;
}
StatusType CDevMemModule::ReadBlock(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CDevMemModule::WriteByte(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CDevMemModule::WriteWord(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CDevMemModule::WriteBlock(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CDevMemModule::ParseCmd(std::string& s, Arguments& args)
{
    return STATUS_FAILURE;
}
StatusType CDevMemModule::PrintCmd(Arguments& args, std::string& s)
{
    return STATUS_FAILURE;
}


/* vim: set ts=4 sw=4 et: */
