/*
 * PipeType.h
 *
 *  Created on: Feb 6, 2017
 *      Author: ducky
 */

#ifndef DUCKY_PIPE_TYPE_H_
#define DUCKY_PIPE_TYPE_H_

namespace ducky {
namespace pipe {

enum PipeType{
	PT_UNKNOWN = 0,
	PT_READ,
	PT_WRITE
};

} /* namespace pipe */
} /* namespace ducky */

#endif /* DUCKY_PIPE_TYPE_H_ */
