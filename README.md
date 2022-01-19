# POV-Ray-complex-functions
[POV-Ray](http://www.povray.org) v3.7 include file for working with complex functions

[List](OPERATORS.md) of available complex operators

## Images created with the examples:

```
j = Sqrt(-1)
Z = re + im*j
Re(Z) = re
Im(Z) = im
|Z| = Sqrt(re^2 + im^2)
```

### Isosurface with domain colors of a complex function
### F(Z) = 1/(Z<sup>5</sup> - 2)<sup>2</sup>

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | \|Fn(Z)\| |   im   |

[Source code](Examples/FivePoles_Isosurface.pov)\
![Image - Isosurface - Five poles](Examples/FivePoles_Isosurface.png)

### Mesh with domain colors of a complex function
### F(Z) = 1/(Z<sup>5</sup> - 2)<sup>2</sup>

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | \|Fn(Z)\| |   im   |

[Source code](Examples/FivePoles_ClippedMesh2_Magn.pov)\
![Image - Mesh - Five poles - Magn](Examples/FivePoles_ClippedMesh2_Magn.png)

### Mesh with domain colors of a complex function
### F(Z) = 1/(Z<sup>5</sup> - 2)<sup>2</sup>

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | Re(Fn(Z)) |   im   |

[Source code](Examples/FivePoles_ClippedMesh2_Real.pov)\
![Image - Mesh - Five poles - Real](Examples/FivePoles_ClippedMesh2_Real.png)

### Mesh with domain colors of a complex function
### F(Z) = 1/(Z<sup>5</sup> - 2)<sup>2</sup>

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | Im(Fn(Z)) |   im   |

[Source code](Examples/FivePoles_ClippedMesh2_Imag.pov)\
![Image - Mesh - Five poles - Imag](Examples/FivePoles_ClippedMesh2_Imag.png)

### Mesh with domain colors of a complex function
### F(Z) = (Z<sup>2</sup> + 1)/(Z<sup>2</sup> - 1)

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | \|Fn(Z)\| |   im   |

[Source code](Examples/Two_Zeros_Two_Poles.pov)\
![Image - Mesh - Two zeros & Two poles](Examples/Two_Zeros_Two_Poles.png)

### Mesh with domain colors of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |     y-axis    | z-axis |
| ------ | ------------- | ------ |
|   re   | Ln(\|Fn(Z)\|) |   im   |

[Source code](Examples/HueStripes_MagnHeight.pov)\
![Image - Mesh - Hue stripes & Magnitude height](Examples/HueStripes_MagnHeight.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](Examples/HueRamps_MagnRamps.pov)\
![Image - Plane - Hue ramps & Magnitude ramps](Examples/HueRamps_MagnRamps.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](Examples/HueRamps_MagnStripes.pov)\
![Image - Plane - Hue ramps & Magnitude stripes](Examples/HueRamps_MagnStripes.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](Examples/HueStripes_MagnRamps.pov)\
![Image - Plane - Hue stripes & Magnitude ramps](Examples/HueStripes_MagnRamps.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](Examples/HueStripes_MagnStripes.pov)\
![Image - Plane - Hue stripes & Magnitude stripes](Examples/HueStripes_MagnStripes.png)

### Mesh with domain colors of magnitude of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | \|Fn(Z)\| |   im   |

[Source code](Examples/HueStripes_MagnHeight_NonLn.pov)\
![Image - Mesh - Hue stripes & Magnitude height](Examples/HueStripes_MagnHeight_NonLn.png)

### Mesh with domain colors of real part of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |   y-axis   | z-axis |
| ------ | ---------- | ------ |
|   re   | Re(Fn(Z))  |   im   |

[Source code](Examples/HueStripes_RealHeight_NonLn.pov)\
![Image - Mesh - Hue stripes & Real height](Examples/HueStripes_RealHeight_NonLn.png)

### Mesh with domain colors of imaginary part of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |   y-axis   | z-axis |
| ------ | ---------- | ------ |
|   re   | Im(Fn(Z))  |   im   |

[Source code](Examples/HueStripes_ImagHeight_NonLn.pov)\
![Image - Mesh - Hue stripes & Imag height](Examples/HueStripes_ImagHeight_NonLn.png)

### Plane with domain colors of the 7th iterate of a complex function (Ln magnitude scale)
### G(Z) = (1 + j)*Sin(Z)
### F(Z) = G<sup>7</sup>(Z) = G(G(G(G(G(G(G(Z)))))))

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](Examples/Iterated_Sine.pov)\
![Image - Plane - Iterated function](Examples/Iterated_Sine.png)
