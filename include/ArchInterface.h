/*
 * ArchInterface.h
 *
 *  Created on: May 16, 2012
 *      Author: null
 */

#ifndef ARCHINTERFACE_H_
#define ARCHINTERFACE_H_

#include "types.h"

/*
 * Provide a generic way for the device and output interfaces to query
 * the underlying system architecture
 */

class ArchInterface
{
public:
	virtual ~DeviceInterface() = 0;

	/*
	 * Get the native memory width for the platform
	 */
	virtual int get_word_len(void) = 0;

	/*
	 * Get the native endianess for the platform
	 */
	virtual EndianType get_endianess(void) = 0;
}


#endif /* ARCHINTERFACE_H_ */
