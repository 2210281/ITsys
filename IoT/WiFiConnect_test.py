#import
import network
import machine
import time

#WiFi setting
SSID = "CampusIoT-WiFi"
PASS = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c"

#Connect to WiFi
print()
print("WiFi initializing...")
wlan = network.WLAN(network.STA_IF)
wlan.active(False)
time.sleep(1)
wlan.active(True)
time.sleep(1)
print("Scanning WLAN...")
print(wlan.scan())

if not wlan.isconnected():
    print("Connecting WiFi:",SSID, end="")
    wlan.connect(SSID,PASS)
    time.sleep_ms(100)
    while not wlan.isconnected():
        print(".",end="")
        time.sleep_ms(200)
        pass

print("\n\nConnected.")
rssi = wlan.status('rssi')
myip,mynetmask,myroute,mydns = wlan.ifconfig()
wifiinfo = (myip,myroute,mydns,rssi)
print("ip: %s\ngateway: %s\ndns: %s\nrssi: %.1f" % wifiinfo)
