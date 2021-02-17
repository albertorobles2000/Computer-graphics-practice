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
