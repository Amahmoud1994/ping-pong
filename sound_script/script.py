import serial
import pyglet
from time import sleep

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=None)

pyglet.options['audio'] = ('openal', 'silent')
player = pyglet.media

bounce = player.load('effects/bounce.wav', streaming=False)
bat_show = player.load('effects/BatShow.wav', streaming=False)
goal = player.load('effects/Goal.wav', streaming=False)
round_start = player.load('effects/Start.wav', streaming=False)
win = player.load('effects/win.wav', streaming=False)
lose = player.load('effects/lose.wav', streaming=False)
collect = player.load('effects/collect.wav', streaming=False)
miss = player.load('effects/miss.wav', streaming=False)

while True:

    data = ser.read(1)

    if data == 'h':
        bounce.play()
    elif data == 'b':
        bat_show.play()
    elif data == 'g':
        goal.play()
    elif data == 's':
        round_start.play()
    elif data == 'w':
        win.play()
    elif data == 'l':
        lose.play()
    elif data == 'c':
        collect.play()
    elif data == 'm':
        miss.play()

    sleep(0.001)
