Robot GUI

Note that an external jar is used, which is included in the jars folder.
Must be connected to Arduino to run.

To compile:
javac -cp ".:../jars/jSerialComm-1.3.11.jar" Robot_GUI.java

To run:
java -cp ".:../jars/jSerialComm-1.3.11.jar" Robot_GUI

This GUI accepts commands in the format of the node.toString() method.
It ignores anything else printed to Serial.

It can also write ints to Serial, however this functionality is untested.

[intersectionName:visited:tokenColor]
ex. [Y3:f:U] 