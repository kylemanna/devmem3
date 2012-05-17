/*
 * OutputInterface.h
 *
 *  Created on: May 16, 2012
 *      Author: null
 */

#ifndef OUTPUTINTERFACE_H_
#define OUTPUTINTERFACE_H_

class OutputInterface {
public:
	virtual ~OutputInterface();

	/* Set the file name for writing output, etc */
	virtual StatusType configure(Arguments& params) = 0;
	virtual StatusType unconfigure(Arguments& params) = 0;

	/* Goal is to maybe support a display "service" that continually
	 * reads and displays something, but these are likely unused for
	 * most cases
	 */
	virtual StatusType start(void) = 0;
	virtual StatusType stop(void) = 0;

	/* Accept a data type, format it according to the params passed in
	 * during configure and store it within the object
	 */
	virtual StatusType generate_output(DataType& d) = 0;

	/* Write the output, this could be via stdout/stderr or to an
	 * xml/json file
	 */
	virtual StatusType write_output(void) = 0;

	/* Rather then write to the ultimate destination, return a string
	 * representation of the data (useful?)
	 */
	virtual StatusType return_output(std::string& output) = 0;

};

#endif /* OUTPUTINTERFACE_H_ */
