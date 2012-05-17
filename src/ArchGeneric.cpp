/*
 * ArchGeneric.cpp
 *
 *  Created on: May 16, 2012
 *      Author: null
 */
#include <arpa/inet.h>

#include "ArchGeneric.h"

ArchGeneric::ArchGeneric() {
	// TODO Auto-generated constructor stub

}

ArchGeneric::~ArchGeneric() {
	// TODO Auto-generated destructor stub
}

int ArchGeneric::get_word_len() {
	return sizeof(int);
}

EndianType ArchGeneric::get_endianess() {
	return (htonl(47) == 47) ? ENDIAN_BIG : ENDIAN_LITTLE;
}
