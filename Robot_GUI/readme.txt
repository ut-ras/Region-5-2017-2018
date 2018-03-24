Robot GUI

Note that an external jar is used, which is included in the jars folder.
Must be connected to Arduino to run.

To compile:
javac -cp ".:../jars/jSerialComm-1.3.11.jar" Robot_GUI.java

To run:
java -cp ".:../jars/jSerialComm-1.3.11.jar" Robot_GUI

This GUI only works with data in the format of the node.toString() method.
This must be the ONLY data sent over Serial.
Each data packet must be exactly 6 characters long with NO newline character or any delimiter.

<intersectionName:visited:tokenColor>
ex. Y3:f:U 