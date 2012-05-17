/*
 * CModuleMem.cpp
 *
 *  Created on: Jan 19, 2012
 *      Author: nitro
 */

#include "DeviceMemory.h"

StatusType DeviceMemory::start(void)
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

StatusType DeviceMemory::stop(void)
{
	if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);

    return STATUS_SUCCESS;
}

StatusType DeviceMemory::read_byte(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType DeviceMemory::read_word(DataType& d)
{
	printf("reading 0x%p\n", virt_addr);
	d.buf[0] = *((unsigned char *) virt_addr);
	printf("reading 0x%p\n", virt_addr);

    return STATUS_SUCCESS;
}
StatusType DeviceMemory::read_block(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType DeviceMemory::write_byte(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType DeviceMemory::write_word(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType DeviceMemory::write_block(DataType& d)
{
    return STATUS_FAILURE;
}
StatusType DeviceMemory::parse_cmd(std::string& s, Arguments& args)
{
    return STATUS_FAILURE;
}
StatusType DeviceMemory::print_cmd(Arguments& args, std::string& s)
{
    return STATUS_FAILURE;
}





