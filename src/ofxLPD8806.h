//
//  ofxLPD8806.h
//  
//
//  Created by james KONG on 18/1/13.
//
//

#pragma once

#include "ofMain.h"
#ifdef OF_TARGET_LINUXARMV6L 
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

class ofxLPD8806
{
public:
	ofxLPD8806();
	~ofxLPD8806();
	bool connect();
	void send(const std::vector<uint8_t>& data);
private:
	int spi_init(int filedes);
	string device;
	int spi_device;
	bool connected;
};
#endif