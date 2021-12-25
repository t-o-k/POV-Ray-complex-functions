# POV-Ray-complex-functions
POV-Ray include file for working with complex functions

j = sqrt(-1)

Z = re + im*j

List of available operators in Complex_Functions.inc:

  Re(Z) = re

  Im(Z) = im

  Pos(Z) = +Z

  Neg(Z) = -Z

  Conj(Z) = re - im*j

  Abs(Z) = |Z| = sqrt(Z*conj(Z))

  Phase(Z) = atan2(im, re)

  Ln(Z) = ln(abs(Z)) + phase(Z)*j

  Exp(Z) = e^Z

  Sqr(Z) = Z^2

  Sqrt(Z) = Z^0.5

  Inv(Z) = 1/Z

  Cos(Z) = (e^(-z*j) + e^(+z*j))/2

  Acos(Z) = -ln(Z + sqrt(1 - Z^2)*j)*j

  Sin(Z) = (e^(-Z*j) - e^(+Z*j))/2*j

  Asin(Z) = -ln(sqrt(1 - Z^2) + Z*j)*j

  Tan(Z) = sin(Z)/cos(Z)

  Atan(z) = (ln(1 - Z*j) - ln(1 + Z*j))/2*j

  Cosh(Z) = (e^(+Z) + e^(-Z)))/2

  Acosh(Z) = +ln(Z + sqrt(Z + 1)*sqrt(Z - 1))

  Sinh(Z) = (e^(+Z) - e^(-Z)))/2

  Asinh(Z) = +ln(Z + sqrt(Z^2 + 1))

  Tanh(Z) = sinh(Z)/cosh(Z)

  Atanh(Z) = (ln(1 + Z) - ln(1 - Z))/2

  Add(Z1, Z2) = Z1 + Z2

  Sub(Z1, Z2) = Z1 - Z2

  Mul(Z1, Z2) = Z1*Z2

  Div(Z1, Z2) = Z1/Z2

  Pow(Z1, Z2) = Z1^Z2
