from ergojunior.client import Client

client = Client('127.0.0.1', 9000) # Connect to the local server on port 9000
client.set_motor(6, 45.3) # Set the first motor at an angle of 127.3 degrees

client.toggle_led(1, 1)
client.toggle_led(2, 1)
client.toggle_led(3, 1)
client.toggle_led(4, 1)


