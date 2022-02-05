import cv2 as cv
import numpy as np
import serial
from serial import Serial
import time

arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)

wht = 320
confThreshold = 0.5
nmsThreshold = 0.3

cap = cv.VideoCapture(0)

file = 'coco-names.txt'
names = []
with open(file, 'rt') as f:
    names = f.read().rstrip('\n').split('\n')

print(names)
print(len(names))

modelConfiguration = 'C:/Users/User/OneDrive - g.bracu.ac.bd/Documents/Codes/Computer Vision/YOLO/yolo-v3.cfg'
modelWeights = 'C:/Users/User/OneDrive - g.bracu.ac.bd/Documents/Codes/Computer Vision/YOLO/yolov3_320.weights'

net = cv.dnn.readNetFromDarknet(modelConfiguration, modelWeights)
net.setPreferableBackend(cv.dnn.DNN_BACKEND_OPENCV)
net.setPreferableTarget(cv.dnn.DNN_TARGET_CPU)


def write_read(x, y):
    arduino.write(int(x, y))
    time.sleep(0.05)
    data = arduino.readline()
    return data

def findObjects(outputs, img):
    hT, wT, cT = img.shape
    bbox = []
    classIds = []
    confs = []

    for output in outputs:
        for det in output:
            scores = det[5:]
            classId = np.argmax(scores)
            confidence = scores[classId]
            if confidence>confThreshold:
                w,h = int(det[2]*wT), int(det[3]*hT)
                x,y = int((det[0]*wT)-w/2), int((det[1]*hT)-h/2)
                bbox.append([x,y,w,h])
                classIds.append(classId)
                confs.append(float(confidence))

    indices = cv.dnn.NMSBoxes(bbox, confs, confThreshold, nmsThreshold)
    # print(indices)
    for i in indices:
        i = i[0]
        box = bbox[i]
        x,y,w,h = box[0],box[1],box[2],box[3]
        cv.rectangle(img, (x,y), (x+w, y+h), (255,0,255),2)
        cv.putText(img, f'{names[classIds[i]].upper()} {int(confs[i]*100)}%',
                   (x,y-10), cv.FONT_HERSHEY_SIMPLEX, 0.6, (255,0,255),2)

    
    try:
        string='X{0:d}Y{1:d}'.format((x+w//2),(y+h//2))
        print(string)
        arduino.write(string.encode('utf-8'))
        print(string.encode ('utf-8'))
    except:
        print("No value")


while(True):
    success, img = cap.read()
    img = cv.flip(img, 1)

    blob = cv.dnn.blobFromImage(img, 1/255, (wht,wht), [0,0,0], 1, crop=False)
    net.setInput(blob)

    layernames = net.getLayerNames()
    # print(layernames)

    outputNames = [layernames[i[0]-1] for i in net.getUnconnectedOutLayers()]
    # print(outputNames)
    #
    # print(net.getUnconnectedOutLayers())

    outputs = net.forward(outputNames)
    # print(outputs[0].shape)
    # print(outputs[1].shape)
    # print(outputs[2].shape)
    # print(outputs[0][0])

    findObjects(outputs, img)

    cv.imshow("Image", img)

    cv.waitKey(1)