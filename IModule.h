#include <string>
#include <vector>

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


class IModule
{
public:
	virtual ~IModule() {};

	virtual StatusType Configure(Arguments& params) = 0;
	virtual StatusType Unconfigure(Arguments& params) = 0;

	virtual StatusType Start(void) = 0;
	virtual StatusType Stop(void) = 0;

	virtual StatusType ReadByte(DataType& d) = 0;
	virtual StatusType ReadWord(DataType& d) = 0;
	virtual StatusType ReadBlock(DataType& d) = 0;

	virtual StatusType WriteByte(DataType& d) = 0;
	virtual StatusType WriteWord(DataType& d) = 0;
	virtual StatusType WriteBlock(DataType& d) = 0;

	/* Parse and print options passed from command line */
	virtual StatusType ParseCmd(std::string& s, Arguments& args) = 0;
	virtual StatusType PrintCmd(Arguments& args, std::string& s) = 0;

protected:
	Arguments args;
};
