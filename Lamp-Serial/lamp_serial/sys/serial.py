# In The Name Of God
# ========================================
# [] File Name : serial.py
#
# [] Creation Date : 5/8/16
#
# [] Created By : Abolfazl Danayi
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================

import serial


class LampSerial:
    def __new__(cls, *args, **kwargs):
        cls.interface = serial.Serial()
        cls.interface.open()

    @classmethod
    def __write_it(cls, msg):
        cls.interface.write((msg + "\n").encode('ascii'))
        print("Send msg:{}".format(msg))

    @classmethod
    def __get_data(cls, self):
        temp = cls.interface.read_until(b")")
        return temp[1:-1].decode('ascii')
