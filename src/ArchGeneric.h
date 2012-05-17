/*
 * ArchGeneric.h
 *
 *  Created on: May 16, 2012
 *      Author: null
 */

#ifndef ARCHGENERIC_H_
#define ARCHGENERIC_H_

#include "ArchInterface.h"

class ArchGeneric : public ArchInterface {
public:
	ArchGeneric();
	virtual ~ArchGeneric();

	/*
	 * Get the native memory width for the platform
	 */
	virtual int get_word_len(void);

	/*
	 * Get the native endianess for the platform
	 */
	virtual EndianType get_endianess(void);
};

#endif /* ARCH_GENERIC_H_ */
