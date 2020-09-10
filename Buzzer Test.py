import time
import board
import pulseio
import digitalio

buzzer = pulseio.PWMOut(pin=board.D13,duty_cycle=0,frequency=262,variable_frequency=True)
button = digitalio.DigitalInOut(board.D12)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP
button_state = False

#frequencies = [0, 440, 480, 520, 560, 600, 640, 680, 740, 780]
#frequencies = [0, 440, 450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650]


frequencies=[]
mode = 0

if mode == 0:
    frequencies = [0,440,450,460,470,480,490,500,510]

if mode == 0.5:
    frequencies = [0,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,640,660]

if mode == 1:
    frequencies = [440,450,460,470,480,490,500,510,500,490,480,470,460,450]

f_index = 1

print("Mode: " + str(mode) + "  " + str(frequencies))


while True:

    if (mode == 0 or mode == 0.5):
        #print(not button.value)
        if not button.value == True and button_state == False:
            if (f_index == 0):
                buzzer.duty_cycle = 0
            else:
                buzzer.duty_cycle = 1000//3
                buzzer.frequency = frequencies[f_index]
            print(f_index)
            f_index = (f_index + 1) % len(frequencies)
            button_state = True
        if not button.value == False:
            button_state = False

        #time.sleep(1)

    if (mode == 1):
        buzzer.duty_cycle = 1000//3
        buzzer.frequency = frequencies[f_index]
        f_index = (f_index + 1) % len(frequencies)
        time.sleep(.15)



