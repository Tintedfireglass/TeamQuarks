"""
Demonstration of the GazeTracking library.
Check the README.md for complete documentation.
"""
import time
import requests
import cv2
from gaze_tracking import GazeTracking

ct=0
url = 'http://192.168.43.78:80'
gaze = GazeTracking()
webcam = cv2.VideoCapture(0)
data = ""
while True:
    # We get a new frame from the webcam
    _, frame = webcam.read()

    # We send this frame to GazeTracking to analyze it
    gaze.refresh(frame)

    frame = gaze.annotated_frame()
    text = ""

    if gaze.is_blinking():
        while gaze.is_blinking():
            ct+=1
            time.sleep(0.2)
            if ct>4:
                break
        if ct>4 :
            if data=="START":
                data="STOP"
            else:
                data = "START"
            response = requests.post(url, data=data)
            print(response.text)
        else:
             text = "Blinking"
    elif gaze.is_right():
        text = "Looking right"
        data = "RIGHT"
        response = requests.post(url, data=data)
        print(response.text)
    elif gaze.is_left():
        text = "Looking left"
        data = "LEFT"
        response = requests.post(url, data=data)
        print(response.text)
    elif gaze.is_center():
        text = "Looking center"
        data = "CENTER"
        response = requests.post(url, data=data)
        print(response.text)

    cv2.putText(frame, text, (90, 60), cv2.FONT_HERSHEY_DUPLEX, 1.6, (147, 58, 31), 2)

    left_pupil = gaze.pupil_left_coords()
    right_pupil = gaze.pupil_right_coords()
    cv2.putText(frame, "Left pupil:  " + str(left_pupil), (90, 130), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
    cv2.putText(frame, "Right pupil: " + str(right_pupil), (90, 165), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)

    import requests

    



    cv2.imshow("Demo", frame)

    if cv2.waitKey(1) == 27:
        break
   
webcam.release()
cv2.destroyAllWindows()
