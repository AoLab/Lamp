![Lamp Project Logo](http://www.googledrive.com/host/0B33KzMHyLoH2eVNHWFJZdmthOVk/Lamp-Logo.png)
# Lamp
## Table of Contents
* [Introduction](#introduction)
* [Device Identification and Discovery](#device-identification-and-discovery)
* [Java Version](#java-version)
* [Project Timeline](#project-timeline)
* [Refrences](#refrences)
* [Lamp-REST API](content/API.md)
* [Steps](#steps)

## Introduction
This project is intended to create an Internet of Things for Amirkabir University of Technology. This project uses [KAA](https://kaaproject.org) as the middle server. In this project we have created a system that can handle RESTful web services to turn the lamps on and off.
![Lamp Project Architecture](http://www.googledrive.com/host/0B33KzMHyLoH2eVNHWFJZdmthOVk/Lamp-Architecture-Main.jpg)
![Lamp-REST Project Architecture](http://www.googledrive.com/host/0B33KzMHyLoH2eVNHWFJZdmthOVk/Lamp-Architecture-Lamp-REST.jpg)

## Device Identification and Discovery
We use Kaa Endpoint Profile for device identification and discovery.
Devices find by Location Info Schema, in this schema we store infomations
about device room number and room owner.

## Java version
You can see java version of this project named JLamp [here](https://github.com/AoLab/JLamp).

## Project Timeline
![Lamp Project Timeline](http://www.googledrive.com/host/0B33KzMHyLoH2eVNHWFJZdmthOVk/Lamp-Gantt-Chart.jpg)


## Steps
1. [main.c](Lamp-RPi/src/main.c) contains source code for simple turn on and off of the lamp.
2. Using KAA notification for turning the light on
  1. Created lamp application in the KAA server.
  2. Created **mandatory** notification topic for our lamp.
  3. Registered our notification topic in the endpoint groups.

## Refrences
* This guide is useful for learning UNIX C Serial Programming: [UNIX Serial C Programming](https://www.cmrr.umn.edu/~strupp/serial.html)
* This guide is useful for connecting your application to KAA server: [Your first KAA application](https://docs.kaaproject.org/display/KAA/Your+first+Kaa+application)
* You need this for emulating serial port: [Null modem emulator](https://github.com/freemed/tty0tty)
* Checkout screen cheatsheet: [Screen cheatsheet](http://aperiodic.net/screen/quick_reference)
* For installing Lamp-RPi on RPi (!):
   1. Donwload Raspbian [here](https://www.raspberrypi.org/downloads/raspbian/)
   2. Install Raspbian on SDcard with `unzip -p 2016-03-18-raspbian-jessie.zip | sudo dd of=/dev/mmcblk0 bs=32M`

## Some points about Kaa 0.8.1
### How to change IP address configuration
You can change listening IP address of Kaa Node service with:
```shell
sudo sed -i 's/transport_bind_interface=.*/transport_bind_interface={IP ADDRESS}/' /etc/kaa-node/conf/kaa-node.properties
sudo service kaa-node restart
```
And you can change embedding IP address of Kaa Node service in auto generated SDK with:
```shell
sudo sed -i 's/transport_public_interface=.*/transport_public_interface={IP ADDRESS}/' /etc/kaa-node/conf/kaa-node.properties
sudo service kaa-node restart
```

## Contributors
* [Prof. Bahador Bakhshi](http://ceit.aut.ac.ir/~bakhshis/)
* [Parham Alvani](http://1995parham.github.io/)
* [Iman Tabrizian](https://github.com/Tabrizian)
