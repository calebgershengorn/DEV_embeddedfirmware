import serial
#TODO:
#write it to a file constantly
#make it so that it can be stopped with a keystroke
def doyourprocessinghere(line,times,angleX,angleY,angleZ,accelX,accelY,accelZ):
    print(line)
    temp = line.split()
    if (len(temp) != 7):
        return;
    times.append(temp[0])
    #ftime.write(temp[0])
    angleX.append(temp[1])
    #fangleX.write(temp[1])
    angleY.append(temp[2])
    #fangleY.write(temp[2])
    angleZ.append(temp[3])
    #fangleZ.write(temp[3])
    accelX.append(temp[4])
    #faccelX.write(temp[4])
    accelY.append(temp[5])
    #faccelY.write(temp[5])
    accelZ.append(temp[6])
    #faccelZ.write(temp[6])

ser = serial.Serial(
    port='/dev/cu.usbmodem4542331',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)
message = str("")
count=1
times=[]
angleX=[]
angleY=[]
angleZ=[]
accelX=[]
accelY=[]
accelZ=[]
#ftime = open("timeFile.txt","x")
#fangleX = open("angleXFile.txt","x")
#fangleY = open("angleYFile.txt","x")
#fangleZ = open("angleZFile.txt","x")
#faccelX = open("accelXFile.txt","x")
#faccelY = open("accelXFile.txt","x")
#faccelZ = open("accelXFile.txt","x")
line = ""
while True :
    for character in ser.read():
        #print(chr(character) , end="")
        line = line+chr(character);
        if (character==10):
            doyourprocessinghere(line,times,angleX,angleY,angleZ,accelX,accelY,accelZ);
            line = ""
        #message += chr(line)
ser.close()
