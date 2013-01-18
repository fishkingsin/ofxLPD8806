//
//  ofxLPD8806.h
//  
//
//  Created by james KONG on 18/1/13.
//
//

#pragma once

#include "ofMain.h"
#include <linux/spi/spidev.h>

class ofxLPD8806
{
public:
	ofxLPD8806();
	~ofxLPD8806();
	void connect();
	void send();
private:
	int spi_init(int filedes);
	string device;
	int spi_device;
	bool connected;
};