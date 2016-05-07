"""
    In the name of God
    This is the class of our Serial device
    It works!!!!
    I repeat the last words:
    It works!!!
    Also this time, this one uses auto discovery,
    meaning the there is no need to find the name of ttyACMx device every time.
    Add this module to the main and does everything for you.

    Sincerely
    Abolfazl Danayi, The author!

    AUT-CEIT:
    IoT lab
"""

import serial
import threading
import os
import logging
import re
import time

__author__ = "Abolfazl Danayi"

re_PIR = re.compile(r'^\d:P:(\d)$')
re_LDR = re.compile(r'^\d:D:(\d*)$')


def findSerial():
    for i in range(10):
        path = "/dev/ttyACM" + str(i)
        if os.path.exists(path):
            return path
    return ""


class ANASER:
    def __init__(self, IntFunc):
        self.last_com = ""
        self.msgctr = 0
        self.comctr = 0
        self.intctr = 0
        self.intdata = ""
        self.msgdata = ""
        self.IntFunc = IntFunc
        self.path = findSerial()
        if self.path is not "":
            self.ser = serial.Serial(self.path, 115200)
            while not self.ser.isOpen():
                self.ser.open()
            time.sleep(2)
            self.debug_th = threading.Thread(target=self.debug, daemon=True)
            self.debug_th.start()

    def __write_it(self, msg):
        self.ser.write((msg + "\n").encode('ascii'))
        print("Send msg:{}".format(msg))

    def __get_data(self):
        temp = self.ser.read_until(b")")
        return temp[1:-1].decode('ascii')

    def setLight(self, x, y, state):
        if type(x) == type(1) == type(y) and type(state) == type(True):
            if state:
                k = 1
            else:
                k = 0
            ctr = self.msgctr
            self.__write_it(("L{}{}{}".format(x, y, k)))
            while ctr is self.msgctr:
                pass
            # print(self.last_com)
            if self.last_com != b'@':
                return False
            return True

    def getPIR(self, x):
        pcom = self.comctr
        pmsg = self.msgctr
        if type(x) == type(1):
            self.__write_it("P{}".format(x))
        else:
            return -1
        # print("w1")
        while pcom == self.comctr:
            pass
        # print("w2")
        while pmsg == self.msgctr:
            pass
        # print("endw")
        if (self.last_com == b"!") or (self.last_com == b"~"):
            return -1
        res = re_PIR.match(self.msgdata)
        if res:
            return int(res.group(1))
        return -1

    def getLDR(self, x):
        pcom = self.comctr
        pmsg = self.msgctr
        if type(x) == type(1):
            self.__write_it("D{}".format(x))
        else:
            return -1
        # print("w1")
        while pcom == self.comctr:
            pass
        # print("w2")
        while pmsg == self.msgctr:
            pass
        if (self.last_com == b"!") or (self.last_com == b"~"):
            return -1
        res = re_LDR.match(self.msgdata)
        if res:
            return int(res.group(1))
        return -1

    def getLight(self, x, y):
        if type(x) == type(y) == type(1):
            pcom = self.comctr
            pmsg = self.comctr
            self.__write_it("L{}{}2".format(x, y))
            while self.comctr == pcom:
                pass
            logging.log(1, "GL: sent")
            while self.msgctr == pmsg:
                pass
            logging.log(1, "GL: new")
            if self.last_com == b"!":
                return -1
            return int(self.msgdata)

    def __del__(self):
        if self.path is not "":
            self.ser.close()

    def debug(self):
        while 1:
            if self.ser.inWaiting() > 0:
                temp = self.ser.read(1)
                if temp == b"$":
                    logging.debug("Commanded")
                    # print("Commanded")
                    self.comctr += 1
                elif temp == b"!":
                    self.last_com = temp
                    self.msgctr += 1
                    logging.debug("Unknown command")
                elif temp == b"@":
                    self.last_com = temp
                    self.msgctr += 1
                    logging.debug("Command done")
                elif temp == b"~":
                    self.msgctr += 1
                    self.last_com = temp
                    logging.debug(print("Bad RF"))

                elif temp == b"I":
                    # print("Interrupt: ", end="")
                    while self.ser.inWaiting() == 0:
                        pass
                    temp = self.ser.read(1)
                    if temp == b"#":
                        # print("Good RF")
                        self.intdata = self.__get_data()
                        self.intctr += 1
                        self.IntFunc(self.intdata)
                        # print(self.intdata, end="\n")
                    else:
                        pass
                        # print("Bad Int/RF")

                elif temp == b"#":
                    # print("Coming data", end="")
                    while self.ser.inWaiting() == 0:
                        pass
                    self.msgdata = self.__get_data()
                    self.last_com = b"#"
                    self.msgctr += 1
                    # print(self.msgdata, end="\n")

                else:
                    logging.debug("Unkown command: {}".format(temp))
