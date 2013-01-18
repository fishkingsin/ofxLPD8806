//
//  ofxLPD8806.cpp
//  
//
//  Created by james KONG on 18/1/13.
//
//

#include "ofxLPD8806.h"
ofxLPD8806::ofxLPD8806()
{
	device = "/dev/spidev0.0";
	connected = false;
	spi_device = 0;
}
ofxLPD8806::~ofxLPD8806()
{
	close(spi_device);
}
bool ofxLPD8806::connect()
{
	spi_device = open(device.c_str(),O_WRONLY);
	if(spi_device<0) {
		fprintf(stderr, "Can't open device.\n");
		connected = false;
	}else connected = true;
	int ret=spi_init(spi_device);
	if(ret==-1) {
		fprintf(stderr,"error=%d, %s\n", errno, strerror(errno));
		connected = false;
	}else connected = true;
	return connected;
}

//--------------------------------------------------------------
void ofxLPD8806::send(const std::vector<uint8_t>& data)
{
	if (connected)
		write(spi_device, (char*)data.data(), data.size());
}

int ofxLPD8806::spi_init(int filedes) {
	int ret;
	const uint8_t mode = SPI_MODE_0;
	const uint8_t bits = 8;
	const uint32_t speed = 15000000;
	
	ret = ioctl(filedes,SPI_IOC_WR_MODE, &mode);
	if(ret==-1) {
		return -1;
	}
	
	ret = ioctl(filedes,SPI_IOC_WR_BITS_PER_WORD, &bits);
	if(ret==-1) {
		return -1;
	}
	
	ret = ioctl(filedes,SPI_IOC_WR_MAX_SPEED_HZ,&speed);
	if(ret==-1) {
		return -1;
	}
	
	return 0;
}