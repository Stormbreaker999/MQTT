# MQTT
An implementation of MQTT protocol using Publisher Subscriber model for IOT devices.<BR>

It uses the Publish Subscribe model to establish the connection and control communication between different clients called MQTT clients. It can withstand number of connections defined in macro definition as "MAX_CLIENTS" currently set to 10 and can easily be scaled to meet requirements.<BR>
Clone the repository and compile the server and client program separately to test them out using a terminal or Command Prompt Window-

Compile server and client as-<BR>
gcc mqttbroker.c -o mqttserver<BR>
gcc mqttclient.c -o mqttclient<BR>
<BR>
Run on a local machine as-<BR>
./mqttserver <PORT_NO><BR>
./mqttclient <LOOPBACK_ADDR> <PORT_NO><BR>
<BR>
where <LOOPBACK_ADDR> can be replaced by your own loopback address as example- 127.0.0.1


<BR><BR>
In the new modification have added an additional timer(of 3 seconds) for a subscriber to send requests that perform a checks if data returned by broker same as previous one or not, if not same then message is displayed to the subscriber.

<BR>A sample run of the implementation is ---->

![newmqtt](https://github.com/Stormbreaker999/MQTT/assets/115149477/ef79c9b2-cbc3-4d2f-9a65-8144298d92af)

