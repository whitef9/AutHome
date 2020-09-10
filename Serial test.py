import serial
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore

cred = credentials.Certificate("firestore_service_key.json")
firebase_admin.initialize_app(cred)

db = firestore.client()
doc = db.collection("user_0").document("doc")
print("Printing Data: ")
data = doc.get().to_dict()
print(data)

print("\n\nPrinting Port: ")
port = serial.Serial("COM6")
print(port)
while True:
    x = port.readline()
    print(str(x))
