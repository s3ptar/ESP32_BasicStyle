#***********************************************************************
#! \file:                   FMain.py
#  \projekt:                ESP Basic Tamplate
#  \created on:             2020 10 08
#  \author:                 R. Gräber
#  \version:                0
#  \history:                -
#  \brief
#**********************************************************************/



#***********************************************************************
# Includes / Imports
#**********************************************************************/
import streams
import mcu
import streams
import socket

# import the wifi interface
from wireless import wifi
from espressif.esp32net import esp32wifi as wifi_driver
from solomon.ssd1306 import ssd1306
# import the wifi interface


#***********************************************************************
# Informations
#**********************************************************************/
#
#***********************************************************************
# Declarations
#**********************************************************************/
 
#***********************************************************************
# Global Variable
#**********************************************************************/
glb_var_projektname = "ESP32_Basic"
glb_var_devicename = ""
glb_var_mac = ""
glb_var_ip = ""
#***********************************************************************
# Constant
#**********************************************************************/
 
#***********************************************************************


streams.serial()
wifi_driver.auto_init()
new_resource("index.html")

sleep(1000)

########################## Build Project Dependecies ############################

glb_var_ip, netmask, gateway_ip, dns, mac = wifi.link_info()
glb_var_mac = str(hex(mac[0]).split('x')[-1]) + ":" + hex(mac[1]).split('x')[-1] + ":" + hex(mac[2]).split('x')[-1] + ":" + hex(mac[3]).split('x')[-1] + ":" + hex(mac[4]).split('x')[-1] + ":" + hex(mac[5]).split('x')[-1]
glb_var_devicename = glb_var_projektname+"_"+glb_var_mac
print(glb_var_devicename)

########################## Reset LCD ############################################
pinMode(D16 ,OUTPUT)
digitalWrite(D16, LOW)  # turn the LED ON by setting the voltage HIGH
sleep(1000)               # wait for a second
digitalWrite(D16, HIGH)   # turn the LED OFF by setting the voltage LOW
sleep(1000)               # wait for a second

########################## Init LCD ############################################
try:
    # Setup display 
    # This setup is referred to ssd1306 mounted on a XinaBox CW02
    ssd = ssd1306.SSD1306(I2C0)
    ssd.init(128,64)
    ssd.on()
    ssd.clear()
    ssd.draw_text("Wellcome",0,0,96,8,1)
except Exception as e:
    print("LCD Init Error", e)

########################## Connect WLan #####################################


for x in range(0,3):
    print("Establishing Link...")
    try:
     # FOR THIS EXAMPLE TO WORK, "Network-Name" AND "Wifi-Password" MUST BE SET
        # TO MATCH YOUR ACTUAL NETWORK CONFIGURATION
        wifi.link("chilihotdog",wifi.WIFI_WPA2,"bxJHckMMkGqEPfY3Jf3nZnAn5FtGYwKZSkzVvbzFHNbpUZfv79GXm8afDuNu")
    except Exception as e:
        print("ooops, something wrong while linking :(", e)
        
    if wifi.is_linked():
        break
    if x > 2:
        while True:
            print("no WLan Connection")
            sleep(1000)
    sleep(1000)
        
# Yes! we are connected
print("Linked!")
# refresh network data
glb_var_ip, netmask, gateway_ip, dns, mac = wifi.link_info()
ssd.draw_text(glb_var_ip,0,10,96,8,1)
print(glb_var_ip)
print(glb_var_mac)
########################## MWebserver ######################################

# Now let's create a socket and listen for incoming connections on port 80
sock = socket.socket()
sock.bind(80)
sock.listen()

########################## Main ############################################

while True:
    try:
        # Type in your browser the board ip!
        print("Waiting for connection...")
        # here we wait for a connection
        clientsock,addr = sock.accept()
        print("Incoming connection from",addr)
        
        # yes! a connection is ready to use
        # first let's create a SocketStream
        # it's like a serial stream, but with a socket underneath.
        # This way we can read and print to the socket
        print("read streams")
        client = streams.SocketStream(clientsock)
        # let's read all the HTTP headers from the browser
        # stop when a blank line is received
        line = client.readline()
        print(line)
        while line!="\n" and line!="\r\n":
            line = client.readline()
        print("HTTP request received!")
        
        f = open("resource://index.html",'rb')

        html_response = "HTTP/1.1 200 OK\r\n"
        html_response += "Content-Type: text/html\r\n"
        html_response += "Content-Length: "+str(f.size)+"\r\n"
        html_response += "Connection: close\r\n\r\n"

        clientsock.send(html_response)
        print("send response")
        
        offset = 0
        chunk = 32
        while True:
            data = f.read(chunk)
            if data:
                if '@' in data:
                    data = data.replace('@',str(random(0,100)))
                    clientsock.send(data)
                    offset += chunk
                    f.seek(offset)
            else:
                break

        clientsock.close()

    except Exception as e:
        print("ooops, something wrong:",e)
    