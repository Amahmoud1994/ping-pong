import serial
import pyglet
from time import sleep

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=None)

pyglet.options['audio'] = ('openal', 'silent')
player = pyglet.media

bat_hit = player.load('effects/Bathit.wav', streaming=False)
bat_show = player.load('effects/BatShow.wav', streaming=False)
goal = player.load('effects/Goal.wav', streaming=False)
round_start = player.load('effects/Start.wav', streaming=False)

while True:

    data = ser.read(1)
    if data == 'h':
        bat_hit.play()
    elif data == 'b':
        bat_show.play()
    elif data == 'g':
        goal.play()
    elif data == 's':
        round_start.play()

    sleep(0.001)
