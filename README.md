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

[Source code](FivePoles_Isosurface.pov)\
![Image - Isosurface - Five poles](FivePoles_Isosurface.png)

### Mesh with domain colors of a complex function
### F(Z) = (Z<sup>2</sup> + 1)/(Z<sup>2</sup> - 1)

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | \|Fn(Z)\| |   im   |

[Source code](Two_Zeros_Two_Poles.pov)\
![Image - Mesh - Two zeros & Two poles](Two_Zeros_Two_Poles.png)

### Mesh with domain colors of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |     y-axis    | z-axis |
| ------ | ------------- | ------ |
|   re   | Ln(\|Fn(Z)\|) |   im   |

[Source code](HueStripes_MagnHeight.pov)\
![Image - Mesh - Hue stripes & Magnitude height](HueStripes_MagnHeight.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](HueRamps_MagnRamps.pov)\
![Image - Plane - Hue ramps & Magnitude ramps](HueRamps_MagnRamps.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](HueRamps_MagnStripes.pov)\
![Image - Plane - Hue ramps & Magnitude stripes](HueRamps_MagnStripes.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](HueStripes_MagnRamps.pov)\
![Image - Plane - Hue stripes & Magnitude ramps](HueStripes_MagnRamps.png)

### Plane with domain colors of a complex function (Ln magnitude scale)
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](HueStripes_MagnStripes.pov)\
![Image - Plane - Hue stripes & Magnitude stripes](HueStripes_MagnStripes.png)

### Mesh with domain colors of magnitude of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |  y-axis   | z-axis |
| ------ | --------- | ------ |
|   re   | \|Fn(Z)\| |   im   |

[Source code](HueStripes_MagnHeight_NonLn_Magn.pov)\
![Image - Mesh - Hue stripes & Magnitude height](HueStripes_MagnHeight_NonLn_Magn.png)

### Mesh with domain colors of real part of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |   y-axis   | z-axis |
| ------ | ---------- | ------ |
|   re   | Re(Fn(Z))  |   im   |

[Source code](HueStripes_MagnHeight_NonLn_Real.pov)\
![Image - Mesh - Hue stripes & Real height](HueStripes_MagnHeight_NonLn_Real.png)

### Mesh with domain colors of imaginary part of a complex function
### F(Z) = (-Z<sup>3</sup> + Z<sup>2</sup>*j + 1)/(Z - 1 + j)<sup>2</sup>

| x-axis |   y-axis   | z-axis |
| ------ | ---------- | ------ |
|   re   | Im(Fn(Z))  |   im   |

[Source code](HueStripes_MagnHeight_NonLn_Imag.pov)\
![Image - Mesh - Hue stripes & Imag height](HueStripes_MagnHeight_NonLn_Imag.png)

### Plane with domain colors of the 7th iterate of a complex function (Ln magnitude scale)
### G(Z) = (1 + j)*Sin(Z)
### F(Z) = G<sup>7</sup>(Z) = G(G(G(G(G(G(G(Z)))))))

| x-axis | z-axis |
| ------ | ------ |
|   re   |   im   |

[Source code](Iterated_Sine.pov)\
![Image - Plane - Iterated function](Iterated_Sine.png)
