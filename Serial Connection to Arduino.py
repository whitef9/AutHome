import serial
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
import time
from datetime import datetime

#debug is on
debug = 1


#sources
#https://www.instructables.com/id/Arduino-Python-Communication-via-USB/



#####Database preping#####
cred = credentials.Certificate("firestore_service_key.json")
firebase_admin.initialize_app(cred)

db = firestore.client()
doc = db.collection("user_0").document("doc")
TriggeredTimes = db.collection("user_0").document("TriggeredTimes")
TriggeredCount = 0
if debug:
    print("Printing Data: ")
    data = doc.get().to_dict()
    print(data)

doc.update({"reset":"0"})





#####StartUp#####
#Initial booting
port = serial.Serial("COM6", 115200)
if debug:
    print("\n\nPrinting Port: ")
    print(port)

#wait for it to turn on
time.sleep(6)





#####Functions#####
#returns true if owner wants device to be on
def checkForOn():
    temp = bool(int(doc.get({"On"}).to_dict()["On"]))
    print(temp)
    if temp:
        if debug:
            print("Command wants device on: (" + str(temp) + ")")
        return True
    return False

def checkForReset():
    temp = bool(int(doc.get({"reset"}).to_dict()["reset"]))
    if temp:
        return True
    return False

def registerTriggered():
    global TriggeredCount
    ct = datetime.now()
    string = str(ct.year)+" "+str(ct.month)+" "+str(ct.day)+" "+\
             str(ct.hour)+" "+str(ct.minute)+" "+str(ct.second)
    TriggeredTimes.update({str(TriggeredCount):string})
    TriggeredCount+=1

#readies arduino to accept signals
def awaken():
    port.write(b'\x01')

#turns arduino off to stimulus
def hibernate():
    port.write(b'\x02')

def reset():
    port.write(b'\x03')

#check to see if signal went off
def checkForTriggered():
    text = port.readline()
    if debug:
        print(text)
    if ("Triggered" in str(text)):
        return True;
    return False;
        




#####RUN#####
while True:
    if checkForOn():
        awaken()
    else:
        hibernate()

    if checkForReset():
        reset()

    if checkForTriggered():
        registerTriggered()
        


    time.sleep(1)
