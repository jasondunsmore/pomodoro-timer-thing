import machine
import time

green = machine.Pin(0, machine.Pin.OUT)
blue1 = machine.Pin(4, machine.Pin.OUT)
blue2 = machine.Pin(5, machine.Pin.OUT)
builtin1 = machine.Pin(16, machine.Pin.OUT)
builtin2 = machine.Pin(2, machine.Pin.OUT)
red = machine.Pin(14, machine.Pin.OUT)
button = machine.Pin(16, machine.Pin.IN)


def all_on():
    blue2.on()
    red.on()
    blue1.on()
    green.on()
    builtin1.on()
    builtin2.on()


def all_off():
    blue2.off()
    red.off()
    blue1.off()
    green.off()
    builtin1.off()
    builtin2.off()


def all_blink(times=5):
    for i in range(times):
        all_off()
        time.sleep(0.5)
        all_on()
        time.sleep(0.5)


def blink(led, seconds=5, ontime=0.2, offtime=0.2):
    ctime = 0
    while ctime < seconds:
        led.on()
        time.sleep(ontime)
        ctime += ontime
        led.off()
        time.sleep(offtime)
        ctime += offtime


def breathe(led, seconds=5, dutymin=10, dutymax=200, dutypause=0.05, rate=5):
    pwm = machine.PWM(led)
    ctime = 0

    while ctime < seconds:
        for i in range(dutymin, dutymax, rate):
            pwm.duty(i)
            time.sleep(dutypause)
            ctime += dutypause
            if ctime >= seconds:
                break

        for i in reversed(range(dutymin, dutymax, rate)):
            pwm.duty(i)
            time.sleep(dutypause)
            ctime += dutypause
            if ctime >= seconds:
                break

        pwm.deinit()


def pomodoro(minutes=25):
    seconds = (minutes * 60) / 5

    blue2.off()
    red.off()
    blue1.off()
    green.off()

    breathe(blue2, seconds)
    blue2.on()

    breathe(red, seconds)
    red.on()

    breathe(blue1, seconds)
    blue1.on()

    breathe(green, seconds)
    green.on()

    breathe(blue2, seconds)

    all_blink()
    all_off()


builtin1.off()
builtin2.off()

while True:
    if button.value():
        pomodoro()
    time.sleep(0.1)
