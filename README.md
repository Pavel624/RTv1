# RTv1
## Overall review
And so here we got a project in which you have to implement ray tracing algorithm.
4 standart shapes are included: sphere, plane, cylinder and cone. Also you can add multiple light with different 
color and brightness. Above all of that you can set such properties as specular and reflection values 
to any of these 4 shapes.

Just use a scene from scenes folder as a parameter and this scene will be drawn in the window.
## Installation
```
make
./RTv1 scenes/scene1.rt
```
## Some examples
### One light source, 1 sphere, 1 cylinder, 1 cone, 2 planes
![](https://user-images.githubusercontent.com/39954654/75985694-c995dc80-5efd-11ea-864a-b3578475d89e.png)
### Two light sources, 9 spheres, 4 cylinders, 3 planes
![](https://user-images.githubusercontent.com/39954654/75985913-2d200a00-5efe-11ea-8e2e-1b4f2f602127.png)
### Two light sources, 1 sphere, 5 planes: all reflective
![](https://user-images.githubusercontent.com/39954654/75986093-76705980-5efe-11ea-94d9-7e1628b90252.png)
## Scene description file
There must be a file that follows some specific rules mentioned below:
### Camera
```
camera
{
  pos(0 0 -400)
  dir(0 0 1)
  fov(90)
}
```
pos - position (x y z),  
dir - direction (x y z) - can't be a null vector,  
fov - field of view (from 0 to 180)
### Light
```
light
{
	col(255 255 255)
	pos(-200 50 -200)
	bright(400)
}
```
color - color (x y z) - from 0 to 255 each,  
pos - position (x y z),  
bright - brightness value (from 0 to 1000)
### Sphere
```
sphere
{
	col(255 127 0)
	center(-50 -140 -100)
	radius(40)
	specular(1000)
	reflection(0)
}
```
col - color (red green blue) - from 0 to 255 each,  
center - center (x y z),  
radius - radius (positive number or zero),  
specular - specular value (positive number or zero) - get "shinny" effect,  
reflection - reflection value (from 0 to 100) - 0 no reflection at all, 100 - mirror-like surface
### Plane
```
plane
{
	col(80 80 80)
	norm(0 1 0)
	point(-100)
	specular(700)
	reflection(0)
}
```
col - color (red green blue) - from 0 to 255 each,  
norm - normal vector (x y z)  - can't be a null vector,  
point - shift a plane by a value (any number),  
specular - specular value (positive number or zero) - get "shinny" effect,  
reflection - reflection value (from 0 to 100) - 0 no reflection at all, 100 - mirror-like surface
### Cylinder
```
cylinder
{
	col(50 255 50)
	dir(1 1 0)
	center(-70 0 230)
	radius(30)
	specular(760)
	reflection(0)
}
```
col - color (red green blue) - from 0 to 255 each,  
dir - direction (x y z) - can't be a null vector,  
center - center (x y z),  
radius - radius (positive number or null),  
specular - specular value (positive number or zero) - get "shinny" effect,  
reflection - reflection value (from 0 to 100) - 0 no reflection at all, 100 - mirror-like surface
### Cone
```
cone
{
	col(255 255 0)
	dir(-1 3 0)
	center(80 -10 240)
	angle(30)
	specular(800)
	reflection(0)
}
```
col - color (red green blue) - from 0 to 255 each,  
dir - direction (x y z) - can't be a null vector,  
center - center (x y z),  
angle - angle of the cone (from 0 to 90) - in degrees,  
radius - radius (positive number or null),  
specular - specular value (positive number or zero) - get "shinny" effect,  
reflection - reflection value (from 0 to 100) - 0 no reflection at all, 100 - mirror-like surface
