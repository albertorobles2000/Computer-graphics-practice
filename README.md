# Computer-graphics-practice

First Computer Graphics program I have created using OpenGl and QTcreator

## How to execute
First of all you should have QT creator installed. 
You can download it [cliking here](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5).

Then you have to open the project selecting **esqueleto_qt.pro**
Now depending on your operating sistem you have to open the file **esqueleto_qt.pro** and if you are using windows leave it like this:  
```python
#Windows
LIBS += -L/usr/X11R6/lib64 -lopengl32
#Linux
#LIBS += -L/usr/X11R6/lib64 -lGL
```
Or if you are using Linux leave it like this:

```python
#Windows
#LIBS += -L/usr/X11R6/lib64 -lopengl32
#Linux
LIBS += -L/usr/X11R6/lib64 -lGL
```

The you just clik start and the program will be runnig

## What will I see?
1. For example I have done a car which can move, rotating the wheels or open the door, automatically or manually with some sliders
    1. <img src="https://github.com/albertorobles2000/Computer-graphics-practice/blob/main/images/Car.jpeg" width="40%">
2. You can see a Toroide, draw with lines and triangles
    1. <img src="https://github.com/albertorobles2000/Computer-graphics-practice/blob/main/images/Toroide.jpeg" width="40%">
3. Or the same Toroide but this time each triangle reflects the light (FLAT) 
    1. <img src="https://github.com/albertorobles2000/Computer-graphics-practice/blob/main/images/Toroide1.jpeg" width="40%">
4. Or the same Toroide but this time each vertex reflects the light (SMOOTH) 
    1. <img src="https://github.com/albertorobles2000/Computer-graphics-practice/blob/main/images/Toroide2.jpeg" width="40%">

You can do many more things, just feel free to experiment with it
