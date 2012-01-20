/*
 * CModuleMem.cpp
 *
 *  Created on: Jan 19, 2012
 *      Author: nitro
 */

#include "CModuleMem.h"

StatusType CModuleMem::Start(void)
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
    virt_addr = (void *)((unsigned long long)map_base + (args.addr1 & MAP_MASK));


    return STATUS_SUCCESS;
}

StatusType CModuleMem::Stop(void)
{
	if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);

    return STATUS_SUCCESS;
}

StatusType CModuleMem::ReadByte(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CModuleMem::ReadWord(DataType& d)
{
	printf("reading 0x%p\n", virt_addr);
	d.buf[0] = *((unsigned char *) virt_addr);
	printf("reading 0x%p\n", virt_addr);

    return STATUS_SUCCESS;
}
StatusType CModuleMem::ReadBlock(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CModuleMem::WriteByte(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CModuleMem::WriteWord(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CModuleMem::WriteBlock(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType CModuleMem::ParseCmd(std::string& s, Arguments& args)
{
    return STATUS_FAILURE;
}
StatusType CModuleMem::PrintCmd(Arguments& args, std::string& s)
{
    return STATUS_FAILURE;
}





