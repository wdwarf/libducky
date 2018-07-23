/*
 * Serial.h
 *
 *  Created on: 2018年7月23日
 *      Author: liyawu
 */

#ifndef SERIAL_SERIAL_H_
#define SERIAL_SERIAL_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <string>
#include <termios.h>

namespace ducky {
namespace serial {

EXCEPTION_DEF(SerialException);

enum EParity{
	PARITY_NONE,		//无校验
	PARITY_ODD,			//奇校验
	PARITY_EVEN		//偶校验
};

enum EStopBit{
	STOPBIT_1,
	STOPBIT_1P5,
	STOPBIT_2,
};

class Serial: public Object {
public:
	Serial();
	virtual ~Serial();

	void open(const std::string& device);
	bool isOpen() const;
	void close();

	int read(char* buf, int len, int msTimeout = -1);
	int send(char* buf, int len);

	int getBaudrate() const;
	void setBaudrate(int baudrate);
	int getDatabit() const;
	void setDatabit(int databit);
	int getFd() const;
	EParity getParity() const;
	void setParity(EParity parity);
	EStopBit getStopBit() const;
	void setStopBit(EStopBit stopBit);
	void flush();

private:
	int fd;
	struct termios newTermios;
	struct termios oldTermios;
};

} /* namespace serial */
} /* namespace ducky */

#endif /* SERIAL_SERIAL_H_ */
