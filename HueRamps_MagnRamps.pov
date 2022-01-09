// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
/*

https://github.com/t-o-k/POV-Ray-complex-functions

Copyright (c) 2022 Tor Olav Kristensen, http://subcube.com

Use of this source code is governed by the GNU Lesser General Public License version 3,
which can be found in the LICENSE file.

*/
// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#version 3.7;

global_settings { assumed_gamma 1.0 }

#include "colors.inc"
#include "Complex_Functions.inc"
#include "Color_Functions.inc"

default {
    texture {
        pigment { color White }
        finish {
            diffuse 0
            emission color White
        }
    }
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
/*
The function below is from Kurtz le pirate in this POV-Ray newsgroup post:

    Subject: How to ...
    From: kurtz le pirate
    Date: Nov 2021-11-28 10:46:21
    Newsgroup: povray.general
    http://news.povray.org/povray.general/message/%3C61a3a44d%241%40news.povray.org%3E


Prefix/Infix:

    Fn(Z) = (-Z^3 + Z^2*j + 1)/(Z - 1 + j)^2


Prefix:

    Fn(Z) =
        Div(
            Add(
                Add(
                    Neg(
                        Pow(
                            Z(),
                            Const(+3.0)
                        ),
                    ),
                    Mul(
                        Sqr(
                            Z()
                        ),
                        Const(+1.0*j)
                    )
                ),
                Const(+1.0)
            ),
            Sqr(
                Add(
                    Z(),
                    Const(-1.0 +1.0*j)
                )
            )
        )


Postfix:

    (Z)Fn =
        (
            (
                (
                    (
                        (
                            ()Z,
                            (+3.0)Const
                        )Pow
                    )Neg,
                    (
                        (
                            ()Z
                        )Sqr,
                        (+1.0*j)Const
                    )Mul
                )Add,
                (+1.0)Const
            )Add,
            (
                (
                    ()Z,
                    (-1.0 +1.0*j)Const
                )Add
            )Sqr
        )Div
*/

#declare No = 16;

#declare PartTypes = array[No];
#declare Arguments = array[No];

#declare PartTypes[0] = "Z";
#declare Arguments[0] = ZFn();

#declare PartTypes[1] = "Const";
#declare Arguments[1] = RealConstFn(+3.0);

#declare PartTypes[2] = "Pow";
#declare Arguments[2] = Arg2Fn(0, 1);

#declare PartTypes[3] = "Neg";
#declare Arguments[3] = Arg1Fn(2);

#declare PartTypes[4] = "Z";
#declare Arguments[4] = ZFn();

#declare PartTypes[5] = "Sqr";
#declare Arguments[5] = Arg1Fn(4);

#declare PartTypes[6] = "Const";
#declare Arguments[6] = ImagConstFn(+1.0);

#declare PartTypes[7] = "Mul";
#declare Arguments[7] = Arg2Fn(5, 6);

#declare PartTypes[8] = "Add";
#declare Arguments[8] = Arg2Fn(3, 7);

#declare PartTypes[9] = "Const";
#declare Arguments[9] = RealConstFn(+1.0);

#declare PartTypes[10] = "Add";
#declare Arguments[10] = Arg2Fn(8, 9);

#declare PartTypes[11] = "Z";
#declare Arguments[11] = ZFn();

#declare PartTypes[12] = "Const";
#declare Arguments[12] = ComplexConstFn(-1.0, +1.0);

#declare PartTypes[13] = "Add";
#declare Arguments[13] = Arg2Fn(11, 12);

#declare PartTypes[14] = "Sqr";
#declare Arguments[14] = Arg1Fn(13);

#declare PartTypes[15] = "Div";
#declare Arguments[15] = Arg2Fn(10, 14);


#declare ReFunctions = array[No];
#declare ImFunctions = array[No];

AssembleFunctions(PartTypes, Arguments, ReFunctions, ImFunctions)

#declare MagnitudeFn =
    MagnitudeFunction(
        FinalFunction(ReFunctions),
        FinalFunction(ImFunctions)
    )
;
#declare PhaseFn =
    PhaseFunction(
        FinalFunction(ReFunctions),
        FinalFunction(ImFunctions)
    )
;

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#declare HueFn = HueFunction(PhaseFn);

#declare HueRampInterval = 15.00;  // (Degrees)
#declare HueRampFn =
    RampFunction(
        HueRampInterval,
        0.50  // Shift fraction
    )
;

#declare LnMagnitudeFn = function(re, im) { ln(MagnitudeFn(re, im)) };

#declare MagnitudeRampInterval = 1.00;  // (Degrees)
#declare MagnitudeRampFn =
    RampFunction(
        MagnitudeRampInterval,
        0.00  // Shift fraction
    )
;

#declare LightnessFn =
    function(re, im) {
        (0.50 + HueRampFn(HueFn(re, im))/HueRampInterval)
        *
        (0.50 + MagnitudeRampFn(LnMagnitudeFn(re, im))/MagnitudeRampInterval)
        // *
        // 0.80
    }
;

#declare Saturation = 1.00;

plane {
    +y, 0
    FunctionsPigmentRGB(
        function { HSL_RD_FN(HueFn(x, z), Saturation, LightnessFn(x, z)) },
        function { HSL_GN_FN(HueFn(x, z), Saturation, LightnessFn(x, z)) },
        function { HSL_BU_FN(HueFn(x, z), Saturation, LightnessFn(x, z)) }
    )
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

camera {
    orthographic
    direction -y
    right +12*x
    up +12*z
    sky +z
    location +y
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
                                                                   