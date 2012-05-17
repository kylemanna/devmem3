
#ifndef INPUTMODULEINTERFACE_H
#define INPUTMODULEINTERFACE_H_

#include <string>
#include <vector>

#include "types.h"

class DeviceInterface
{
public:
	virtual ~DeviceInterface() {};

	/* Configure the device, maybe set the baudrate for serial buses */
	virtual StatusType configure(Arguments& params) = 0;
	virtual StatusType unconfigure(Arguments& params) = 0;

	/* Start up the operation, open file, etc */
	virtual StatusType start(void) = 0;
	virtual StatusType stop(void) = 0;

	virtual StatusType read_byte(DataType& d) = 0;
	virtual StatusType read_word(DataType& d) = 0;
	virtual StatusType read_block(DataType& d) = 0;

	virtual StatusType write_byte(DataType& d) = 0;
	virtual StatusType write_word(DataType& d) = 0;
	virtual StatusType write_block(DataType& d) = 0;

	/* Parse and print options passed from command line */
	virtual StatusType parse_cmd(std::string& s, Arguments& args) = 0;
	virtual StatusType print_cmd(Arguments& args, std::string& s) = 0;

protected:
	Arguments args;
};

#endif // INPUTMODULEINTERFACE_H_
