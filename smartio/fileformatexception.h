/*
 * fileformatexception.h
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#pragma once
#ifndef FILEFORMATEXCEPTION_H_
#define FILEFORMATEXCEPTION_H_

#include <sstream>
#include <stdexcept>

namespace io
{
/**
 * An appropriate exception to throw if the fileformat is violated
 */
class fileformatexception : std::logic_error
{
private:
	const char *mess;
	static std::ostringstream cnvt;
public:
	fileformatexception(const char *message);
	virtual ~fileformatexception();
	virtual const char* what() const throw();
};

} /* namespace io */

#endif /* FILEFORMATEXCEPTION_H_ */
