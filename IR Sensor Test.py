import board
import time
import digitalio
import pulseio

#Notes
#   - button_value is True when not pressed and False when pressed

#Debug
debug = True

#Button Setup
button = digitalio.DigitalInOut(board.D13)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP
button_state = False

#IR Sensor Setup
IRSensor = digitalio.DigitalInOut(board.D12)
IRSensor.direction = digitalio.Direction.INPUT

#variables
device_state = False

#functions
def turn_on():
    if debug:
        print("Turning on.")



def turn_off():
    if debug:
        print("Truning off.")




while True:
    #If button pressed
    if (button_state == False and button.value != True):
        #turn on
        if device_state == False:
            turn_on()
            device_state = True
        #turn off
        else:
            turn_off()
            device_state = False

        if (debug):
            print(IRSensor.value)


        button_state = True

    #button not pressed
    if (button.value != False):
        button_state = False


