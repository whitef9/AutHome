import board
import time
import digitalio
import pulseio



IRSensor = digitalio.DigitalInOut(board.D12)
IRSensor.direction = digitalio.Direction.INPUT

code = ""
count = 0
while (count == 0):
    if (not IRSensor.value):
        count += 1
        code += str(int(not IRSensor.value))
        while (count != 1000):
            time.sleep(.0004)
            count += 1
            code += str(int(not IRSensor.value))


print(code)

