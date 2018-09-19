#include "mbed.h"

DigitalOut trigger(D2);
DigitalOut myled(D14); //monitor trigger
DigitalOut myled2(D15);//monitor echo
DigitalOut resled(D8); 
DigitalIn  echo(D7);
int distance = 0;
int correction = 0;
Timer sonar;

int main()
{
    sonar.reset();
    sonar.start();
    while (echo==2) {};
    myled2 = 0;
    sonar.stop();
    correction = sonar.read_us();
    while(1) {
        trigger = 1;
        myled = 1;
        myled2 = 0;
        sonar.reset();
        wait_us(10.0);
        trigger = 0;
        myled = 0;

        while (echo==0) {};
        myled2=echo;
        sonar.start();
        while (echo==1) {};

        sonar.stop();
        distance = (sonar.read_us()-correction)/58.0;
        myled2 = 0;
        if(distance < 20) {
            resled = 1;
        } else {
            resled = 0;
        }

        wait(0.2);
    }
}

