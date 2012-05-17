/*
 * types.h
 *
 *  Created on: May 16, 2012
 *      Author: null
 */

#ifndef TYPES_H_
#define TYPES_H_


typedef enum StatusTypeEnum {
    STATUS_SUCCESS = 0,
    STATUS_FAILURE,
    STATUS_WARNING,
} StatusType;

typedef enum DevTypeEnum {
    DEV_MEM = 0,
    DEV_I2C,
    DEV_SPI,
    DEV_CAN,
} DevType;

typedef enum DataOpEnum {
    DATA_OP_NORMAL = 0,
    DATA_OP_CLEAR,
    DATA_OP_SET,
} DataOpType;


typedef enum EndianTypeEnum {
    ENDIAN_BIG = 0,
    ENDIAN_LITTLE,
} EndianType;


/*
 * Information needed to read data from a device in addition to
 * DevMemModuleParams
 */
class DataType
{
public:
	off_t offset;
	size_t len;
	std::vector<int> buf;
};

/*
 * Information about the device
 */
class Arguments
{
public:
	std::string outputFile, cmd;

	DevType dev;
	DataOpType dataOp;

	int silent, verbose, quiet, set, clear;
	int bus;
	int displaySize;
	unsigned long addr1;	/* Bus addr if device is on a bus, else memory addr */
	unsigned long addr2;	/* Only used if bus != 0, signifies memory addr */
	unsigned long data;

	/* Default constructor */
	Arguments()
	{
		silent = 0;
		verbose = 0;
		quiet = 0;
		set = 0;
		clear = 0;

		dev = DEV_MEM;
		dataOp = DATA_OP_NORMAL;

		bus = 0;
		addr1 = 0;
		addr2 = 0;
		data = 0;
		displaySize = 1;
	}

};



#endif /* TYPES_H_ */
