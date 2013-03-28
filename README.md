ofxLPD8806
==========

Raspberrypi SPI  LPD8806 addons 

Introduction
------------


Licence
-------
The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).

Copyright (c) [17/12/2012] [James Kong]

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Installation
------------
prepare SD card image [http://www.raspberrypi.org/downloads] download and install lastest wheezy image
INSTALL  First you'll need to download the beta "Wheezy" debian package from here. Then follow the normal instructions for installing it to your board. Once you have installed it and booted up for the second time i ran some updates (That took hours!!) 
<pre>sudo apt-get update
sudo apt-get upgrade
sudo modprobe spi_bcm2708
sudo rpi-update</pre>
SPI BACKGROUND While that is updating lets talk a little bit of SPI background knowledge is needed in order to get this working. First off Serial Peripheral interface (SPI) is made up of 4 wires normally. It is a standard that was designed by Motorola for use with their micro controllers. If you're interested in learning more about SPI i've added the Wikipedia link. Here is what a standard SPI setup looks like, multiple slaves is optional.

SS - Slave Select (Beagleboard community calles this Chip Select (CS))
MOSI - Master Out Slave In
MISO - Master In Slave Out
CLK - Clock

[[Image:SPI_layout.png]]
<pre>sudo apt-get install git
sudo rpi-update
sudo reboot
ls /dev/
sudo nano /etc/modprobe.d/raspi-blacklist.conf</pre>
you will see somthing like that and uncomment  the blacklist spi-bcm2708 by erase "#"

 # blacklist spi and i2c by default (many users don't need them)
 #blacklist spi-bcm2708
 blacklist i2c-bcm2708

[[Image:SPIdev.PNG]]
Next we want to short the MISO and MOSI pins. Located as GPIO 9 & GPIO 10 as seen below.
[[Image:GPIOs.png]]
connect led strip to raspberry pi as below
[[Image:diagram.png]]
clone openframeworks raspberry pi develop-raspberrypi branch following this guide [https://github.com/openFrameworks-RaspberryPi/openFrameworks/wiki/Raspberry-Pi-Getting-Started Raspberry-Pi-Getting-Started ]
you may alos take a deep look in this [https://github.com/openFrameworks-RaspberryPi/openFrameworks/wiki/RaspberryPi OF RaspberryPi Wiki]
clone addons 
<pre>git clone https://github.com/fishkingsin/ofxLPD8806
git clone https://github.com/fishkingsin/ofxLEDs</pre>
to your openframeowrks addons folder
compile
<pre>cd "YOUR_OF_ROOT"/addons/ofxLPD8806/example/
make </pre>

Result
[[Image:401659950_295.jpg]]
[http://vimeo.com/57840898/ Video]

Dependencies
------------

Compatibility
------------
https://github.com/openFrameworks-RaspberryPi/openFrameworks develop-raspberrypi

Known issues
------------

Version history
------------

### Version 0.1 (Date):
