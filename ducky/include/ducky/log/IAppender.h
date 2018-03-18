/*
 * IAppender.h
 *
 *  Created on: 2018年3月16日
 *      Author: liyawu
 */

#ifndef DUCKY_LOG_IAPPENDER_H_
#define DUCKY_LOG_IAPPENDER_H_

#include <ducky/Object.h>
#include <ducky/log/LogInfo.h>

namespace ducky {
namespace log {

class IAppender: virtual public Object {
public:
	virtual void log(const ducky::log::LogInfo& logInfo) = 0;
};

} /* namespace log */
} /* namespace ducky */

#endif /* DUCKY_LOG_IAPPENDER_H_ */
