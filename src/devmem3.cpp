//============================================================================
// Name        : devmem3.cpp
// Author      : Kyle Manna
// Version     :
// Copyright   : GPLv2
// Description : Modular access to memory and devices
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <argp.h>

#include "CDevMemModule.h"

using namespace std;

#define ARRAY_SIZE(x)	sizeof(x)/sizeof(x[0])

const char *devmem3_version = "devmem3 0.1-beta";
const char *devmem3_addr =	"<kyle@kylemanna.com>";
const char *devmem3 = "devmem3 -- Modular access to memory and devices";

/* A description of the arguments we accept. */
static char args_doc[] = "ADDR [ TYPE [ DATA ]]";

/* The options we understand. */
static struct argp_option options[] = {
		{"devtype",	'd', 0,      0,	"Device type (default: devmem)" },
		{"verbose",	'v', 0,      0,	"Produce verbose output" },
		{"quiet",	'q', 0,      0,	"Produce minimal output" },
		{"silent",	's', 0,      0,	"Produce no output" },
		{"output", 	'w', "FILE", 0,	"Output to FILE instead of standard output" },
		{"clear",	'o', 0,      0,	"Clear (logical OR) bits set in DATA at ADDR" },
		{"set",		'a', 0,      0,	"Set (logical AND) bits set in DATA at ADDR" },
		{"cmd",		'c', "CMD",  0,	"Command to run (devtype dependent, try -c help)" },

		{ 0 }
};

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
	Arguments* args = (Arguments*)state->input;


	string argStr;

	if (arg)
		argStr.append(arg);

	switch (key)
	{
	case 'd':
		if (argStr == "mem")
			args->dev = DEV_MEM;
		break;
	case 'v':
		args->verbose = 1;
		break;
	case 'q':
		args->quiet = 1;
		break;
	case 's':
		args->silent = 1;
		break;
	case 'w':
		args->outputFile = argStr;
		break;
	case 'o':
		args->set = 1;
		break;
	case 'a':
		args->clear = 1;
		break;
	case 'c':
		args->cmd = argStr;
		break;

	case ARGP_KEY_ARG:

		switch (state->arg_num) {
		case 0: /* ADDR */

		{
			unsigned long temp;
			stringstream iss;
			iss << std::hex << argStr;
			iss >> std::setbase(0) >> temp;
			args->addr1 = temp;
		}

			break;

		case 1: /* TYPE */

			if (argStr == "b")
				args->displaySize = 1;
			else if (argStr == "h")
				args->displaySize = 2;
			else
				args->displaySize = 4;

			break;

		case 2: /* DATA */
		{
			unsigned long temp;
			stringstream iss;
			iss << std::hex << argStr;
			iss >> std::setbase(0) >> temp;
			args->data = temp;
		}

			break;

		default: /* Uhoh */
			argp_usage (state);
			assert(false);
			break;
		}

		break;

	case ARGP_KEY_END:
		if (state->arg_num < 1)
			/* Not enough arguments. */
			argp_usage (state);
		break;

	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, devmem3 };

int main (int argc, char **argv)
{
	IDevMemModule *mod;
	Arguments args;

	argp_parse (&argp, argc, argv, 0, 0, &args);

	if (args.verbose) {

		printf("ADDR1 = 0x%08lx\n",	args.addr1);
		printf("ADDR2 = 0x%08lx\n",	args.addr2);

		printf("TYPE = %d\n",		args.displaySize);
		printf("DATA = 0x%08lx\n",	args.data);

		printf("VERBOSE = %s\n",	args.verbose ? "yes" : "no");
		printf("SILENT = %s\n",		args.silent	? "yes" : "no");
		printf("QUIET = %s\n",		args.quiet	? "yes" : "no");
		printf("SET = %s\n", 		args.set	? "yes" : "no");
		printf("CLEAR = %s\n",		args.clear	? "yes" : "no");

		printf("OUTPUT_FILE = %s\n", args.outputFile.c_str());
	}

	mod = new CDevMemModule();

	mod->Configure(args);
	mod->Start();

	DataType d;
	mod->ReadWord(d);

	printf("Read: 0x%08x\n", d.buf[0]);

	mod->Stop();
	mod->Unconfigure(args);

	return 0;
}
