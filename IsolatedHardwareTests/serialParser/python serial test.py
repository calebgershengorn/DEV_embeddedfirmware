import serial

ser = serial.Serial(
    port='/dev/cu.usbmodem4541241',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)
message = str("")
count=1

done = false
while not done :
    for line in ser.read():
        print(chr(line) )
        message += chr(line)
        count += 1
        if message[len(message) - 4: ].equals("done") :
            done = true;

print(message)
ser.close()
