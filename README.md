# 42 Project miniRT

This project is an introduction to the beautiful world of Raytracing.  
I had to write a C program that can create simple form (i.e square, cylinder, sphere, plane, triangle),  
with light management (shadow, colored light, intensity...). 
I also implement refraction and reflexion.

## Usage :

`make && ./miniRT scene.rt`  

or to save as .bmp use 

`make && ./miniRT scene.rt --save`

## Configuration file

File must be a .rt extension. 
example configuration with all type :  
```
# scenes/example.rt
# R is the render size (x y)
# A is the ambiante light with intensity value 0 < intensity <= 1 and color in RGB

R    1080  720
A    0.8                                        255,255,255


# c are the cameras, you can have multiple. You need to give coordinates, orientation and FOV
# l are the light, you can have multiple. You need to give coordinates, intensity and color in RGB

c    0,-10,20             0,0,1   70
l    20,-35,-65                   0.4          255,215,0
l    -20,-35,-65                   0.4          0,215,50
l    20,-35,-35                   0.4          0,50,215
l    -20,-35,-35                   0.4          255,0,215
l    -15,-10,-50                   0.4          255,215,0
l    15,-10,-50                   0.4          255,0,255
l    -40,-10,-10                   0.4          0,125,180
l    40,-10,-10                   0.4          50,20,125


# For each object you must specify the coordinates (except for triangles) and color in RGB.
# pl for plane, you need to specify orientation (x,y,z   a,b,c   RGB)
# sp for sphere, you need to specify diameter (x,y,z   diameter   RGB)
# tr for triangle, you need to specify three position (x,y,z   a,b,c  l,m,o   RGB)
# sq for square, you need to specify inclination and size of side (x,y,z   a,b,c   SIZE   RGB)
# cy for cylinder, you need to specify diameter (x,y,z   diameter   RGB)
# You can specify option m after an object to make it reflective
# You can also specify t and a value 0 < v <= 1 to make it transparent with an indice of refraction

pl    0,10,-55          0,-1,0             230,230,230
pl    0,-40,-55          0,-1,0             100,100,100
pl    0,-40,-80          0,0,1             153,0,0
cy    40,-40,-65   0,1,0   12 50           140,140,140
cy    -40,-40,-65   0,1,0   12 50           140,140,140
cy    40,-40,-35   0,1,0   12 50           140,140,140
cy    -40,-40,-35   0,1,0   12 50           140,140,140
sp    40,10,-65  20    110,110,110
sp    -40,-40,-65  20  190,190,190
sp    -40,10,-65  20    110,110,110
sp    40,-40,-65  20   190,190,190
sp    -40,10,-35  20   110,110,110
sp    -40,-40,-35  20  190,190,190
sp    40,10,-35  20    110,110,110
sp    40,-40,-35  20    190,190,190
sp    0,4,-50  10   255,0,0 m
sp    0,-15,-50  15   125,80,200
sq    0,-10,5 1,1,0 5  255,0,255 t 1
tr    10,4,-70   20,4,-70   15,-4,-70    0,0,255
```

![alt text](https://github.com/lucasmln/miniRT/blob/master/scenes/example.bmp?raw=true)
