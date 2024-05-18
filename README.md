# MQTT
An implementation of MQTT protocol using Publisher Subscriber model for IOT devices.

It uses the Publish Subscribe model to establish the connection and control communication between different clients called MQTT clients. It can withstand number of connections defined in macro definition as "MAX_CLIENTS" currently set to 10 and can easily be scaled to meet requirements.
Clone the repository and compile the server and client program separately to test them out using a terminal or Command Prompt Window-

Compile server and client as-
gcc mqttbroker.c -o mqttserver
gcc mqttclient.c -o mqttclient

Run on a local machine as-
./mqttserver <PORT_NO>
./mqttclient <LOOPBACK_ADDR> <PORT_NO>

where <LOOPBACK_ADDR> can be replaced by your own loopback address as example- 127.0.0.1
