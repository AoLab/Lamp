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
    interface = None

    def __new__(cls, *args, **kwargs):
        if cls.interface is None:
            cls.interface = serial.Serial()
            cls.interface.open()

    @classmethod
    def write_data(cls, msg: str):
        cls.interface.write((msg + "\n").encode('ascii'))
        print("Send msg:{}".format(msg))

    @classmethod
    def read_data(cls) -> str:
        buffer = cls.interface.read_until(b")")
        return buffer[1:-1].decode('ascii')


class LampSerialServer:
    pass
