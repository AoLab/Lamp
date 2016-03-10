#include "serial.h"
#include <stdio.h>
#include <unistd.h>

int main(){
    open_serial("/dev/ttyUSB0");

    init_serial();

    writechar('0');

    return 0;
}
