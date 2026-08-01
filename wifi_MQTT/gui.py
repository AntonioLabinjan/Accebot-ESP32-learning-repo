import tkinter as tk
import paho.mqtt.client as mqtt

MQTT_BROKER = "localhost"
MQTT_PORT = 1883
MQTT_TOPIC = "home/led"

client = mqtt.Client()
client.connect(MQTT_BROKER, MQTT_PORT, 60)

def led_on():
    client.publish(MQTT_TOPIC, "ON")
    status_label.config(text="Sent: ON")

def led_off():
    client.publish(MQTT_TOPIC, "OFF")
    status_label.config(text="Sent: OFF")

root = tk.Tk()
root.title("ESP32 LED Controller")
root.geometry("250x150")

btn_on = tk.Button(root, text="LED ON", bg="lightgreen", width=15, height=2, command=led_on)
btn_on.pack(pady=10)

btn_off = tk.Button(root, text="LED OFF", bg="salmon", width=15, height=2, command=led_off)
btn_off.pack(pady=5)

status_label = tk.Label(root, text="Ready")
status_label.pack(pady=10)

root.mainloop()
