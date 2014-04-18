## Arduino subsystem
The Arduino subsystem will monitor the flow meters and temperature sensor.  It will log the pulses or "clicks" that the flow sensors log when beer is dispensed.

### Implementation plan
1. Listen for clicks
2. Log clicks for each tap
3. On query from rPi, report number of clicks
4. Read temperature sensor
5. Reset counts
6. Repeat loop (steps 1-2)

It probably wouldn't be a bad idea to functionalize the read and reset pieces into functions that are called inside the loop.

### Wiring guidlines:
#### Flow meter:
Connect the red wire to +5V, the black wire to common ground and the yellow sensor wire to pin #2

#### Temperature sensor
DS18B20 requires the [Dallas library](https://github.com/milesburton/Arduino-Temperature-Control-Library) as well as the [OneWire library](http://playground.arduino.cc/Learning/OneWire) to run.

NOTE: Temperature will be output in kelvin.  Which may necessitate a conversion subroutine either in the rPi or the Web UI.

### Output

Output is a csv triple with temp, tap one, and tap two.

Sample output:

297.21,0,0
297.09,0,0
