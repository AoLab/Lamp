"""
    In the name of God
    This is an example that explains the usage of ANASER device
    Abolfazl Danayi
    AUT-CEIT 2016
    IoT Lab
    Hardware team
"""

from . import CAnADem


def interrupt(data):
    print("hello! I am in the interrupt!!!")
    print("The module automatically runs me with data from interrupt!!!")
    print("This is the data: {}".format(data))


dev = CAnADem.ANASER(
    interrupt)  # The class is made and also will take 2 seconds to open the Serial port

while 1:
    # print("Doing a blink")
    # print(dev.setLight(1, 1, True))   # returns true if done
    # time.sleep(1)
    # print(dev.setLight(1, 1, False))   # returns true if done
    # time.sleep(1)
    # print(dev.getLight(1, 1))         # checks the status, returns 1,0, -1 {-1 = invalid}

    dev.set_light(1, 1, True)
    dev.get_light(1, 1)
    dev.get_pir(1)
    dev.get_ldr(1)

    print("Getting PIR:")
    p = dev.get_pir(1)
    print("got: {}".format(p))

    print("Getting LDR:")
    l = dev.get_ldr(1)
    print("got: {}".format(l))
