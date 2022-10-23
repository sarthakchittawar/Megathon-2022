from onem2mFunctions import *
import matplotlib.pyplot as plt
import requests
import smtplib
from tkinter import *

l=[]
flag=0

uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae = "Entity"
uri_ae = uri_cse + "/" + ae

def reset():
    delete(uri_ae)
    create_ae(uri_cse, ae)
    cnt = "Pothole"
    create_cnt(uri_ae, cnt)
            
def brake():
    # Would use CARLA simulator in order to access car's braking system and brake
    pass
  
reset()
def func():
    while(1):

        uri_cnt = "http://127.0.0.1:8080/~/in-cse/in-name/Entity/Pothole?rcn=4"
        header = {
                'X-M2M-Origin': 'admin:admin',
                'Content-type': 'application/json'}
        response = requests.get(uri_cnt, headers=header)
        data = response.json()
        data = data["m2m:cnt"]["m2m:cin"]
        d={}
        for i in data:
            d = i
        if (float(d["con"]) == 1):
            brake()

func()
