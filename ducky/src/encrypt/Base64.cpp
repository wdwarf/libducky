#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
#include <ducky/encrypt/Base64.h>

using namespace std;

namespace ducky {
namespace encrypt {

static const char tbCode[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

static char getCode(unsigned int iCode) {
	if (iCode > 63)
		return 0;
	return tbCode[iCode];
}

string Base64::encrypt(string str) {
	if (!str.empty()) {
		return Base64::encrypt(str.c_str(), str.length());
	} else {
		return "";
	}
}

string Base64::encrypt(const char* buf, long len) {
	string re;
	if (NULL != buf && len > 0) {
		int size = len / 3;
		int size2 = len % 3;
		for (int i = 0; i < size; i++) {
			const unsigned char* src = (unsigned char*) buf + i * 3;
			char des[4] = { 0 };
			des[0] = src[0] >> 2;
			des[1] = ((src[0] & 0x03) << 4) | (src[1] >> 4);
			des[2] = ((src[1] & 0x0F) << 2) | (src[2] >> 6);
			des[3] = src[2] & 0x3F;
			for (int n = 0; n < 4; n++) {
				re += getCode(des[n]);
			}
		}
		if (size2 > 0) {
			unsigned char src[3] = { 0 };
			memcpy(src, buf + len - size2, size2);
			unsigned char des[4] = { 0 };
			int s = size2 * 8;
			size = s / 6 + ((s % 6 > 0) ? 1 : 0);

			des[0] = src[0] >> 2;
			des[1] = ((src[0] & 0x03) << 4) | (src[1] >> 4);
			des[2] = ((src[1] & 0x0F) << 2) | (src[2] >> 6);
			des[3] = src[2] & 0x3F;
			for (int n = 0; n < size; n++) {
				re += getCode(des[n]);
			}

			for (int i = 4 - size; i > 0; i--) {
				re += '=';
			}
		}
	}
	return re;
}

void Base64::decrypt(char* des, long* desLen, string src) {
	if (0 == des || 0 == desLen || src.empty()) {
		return;
	}

	*desLen = 0;
	int pos = src.find("=");
	if (pos >= 0) {
		src = src.substr(0, pos);
	}
	int size = src.length() / 4;
	int size2 = src.length() % 4;

	vector<unsigned char> buf(src.length());
	for (string::size_type i = 0; i < src.length(); i++) {
		for (unsigned char n = 0; n < 64; n++) {
			if (tbCode[n] == src[i]) {
				buf[i] = n;
				break;
			}
		}
		if ('=' == src[i]) {
			buf[i] = 0;
		}
	}
	for (int i = 0; i < size; i++) {
		unsigned char* tmpBuf = &buf[0] + i * 4;
		char tmpDes[3] = { 0 };
		tmpDes[0] = (tmpBuf[0] << 2) | ((tmpBuf[1] & 0x30) >> 4);
		tmpDes[1] = ((tmpBuf[1] & 0x0F) << 4) | (tmpBuf[2] >> 2);
		tmpDes[2] = (tmpBuf[2] << 6) | tmpBuf[3];
		memcpy(des + i * 3, tmpDes, 3);
		*desLen += 3;
	}

	if (size2 > 0) {
		string src2 = src.substr(src.length() - size2);
		size = src2.length() * 6 / 8;

		unsigned char tmpBuf[4] = { 0 };
		memcpy(tmpBuf, &buf[0] + src.length() - size2, size2);
		char tmpDes[3] = { 0 };
		tmpDes[0] = (tmpBuf[0] << 2) | ((tmpBuf[1] & 0x30) >> 4);
		tmpDes[1] = ((tmpBuf[1] & 0x0F) << 4) | (tmpBuf[2] >> 2);
		tmpDes[2] = (tmpBuf[2] << 6) | tmpBuf[3];
		memcpy(des + *desLen, tmpDes, size);
		*desLen += size;
	}
}

void Base64::decrypt(ostream& des, string src) {
	vector<char> desBuf(src.length());
	long desLen = 0;
	try {
		Base64::decrypt(&desBuf[0], &desLen, src);
		if (desLen > 0) {
			des.write(&desBuf[0], desLen);
		}
	} catch (...) {
	}
}

void Base64::decrypt(char* des, long* desLen, const char* src, long srcLen) {
	string s(src, srcLen);
	Base64::decrypt(des, desLen, s);
}

}
}
