// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
/*

https://github.com/t-o-k/POV-Ray-complex-functions

Copyright (c) 2022-2024 Tor Olav Kristensen, http://subcube.com

Use of this source code is governed by the GNU Lesser General Public License version 3,
which can be found in the LICENSE file.

*/
// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#version 3.7;

global_settings { assumed_gamma 1.0 }

#include "colors.inc"
#include "../Complex_Functions.inc"
#include "../Color_Functions.inc"

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
The function below and the iteration idea was found here:

    https://www.jedsoft.org/fun/complex/gallery.html


Prefix/Infix notation:

    Fn(Z) = (+1.0 +1.0*j)*sin(Z)


Prefix notation:

    Fn(Z) =
        Mul(
            +1.0 +1.0*j,
            Sin(
                Z
            )
        )


Postfix notation:

    (Z)Fn =
        (
            +1.0 +1.0*j,
            (
                Z
            )Sin
        )Mul
*/

#declare No = 4;

#declare PartTypes = array[No];
#declare Arguments = array[No];

#declare PartTypes[0] = "Const";
#declare Arguments[0] = ComplexConstFn(+1.0, +1.0);

#declare PartTypes[1] = "Z";
#declare Arguments[1] = ZFn();

#declare PartTypes[2] = "Sin";
#declare Arguments[2] = Arg1Fn(1);

#declare PartTypes[3] = "Mul";
#declare Arguments[3] = Arg2Fn(0, 2);


#declare ReFunctions = array[No];
#declare ImFunctions = array[No];

AssembleFunctions(PartTypes, Arguments, ReFunctions, ImFunctions)

#declare RealFns = FinalFunction(ReFunctions);
#declare ImagFns = FinalFunction(ImFunctions);

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro Iterate(ReFn, ImFn, ReIterFns, ImIterFns)

    #local Size =
        max(
            dimension_size(ReIterFns, 1),
            dimension_size(ImIterFns, 1)
        )
    ;
    #declare ReIterFns[0] = ReFn;
    #declare ImIterFns[0] = ImFn;
    #for (I, 1, Size-1)
        #declare ReIterFns[I] =
            function(re, im) {
                ReFn(ReIterFns[I-1](re, im), ImIterFns[I-1](re, im))
            }
        ;
        #declare ImIterFns[I] =
            function(re, im) {
                ImFn(ReIterFns[I-1](re, im), ImIterFns[I-1](re, im))
            }
        ;
    #end // for

#end // macro Iterate


#declare NoOfIterations = 7;
#declare ReIterateFunctions = array[NoOfIterations];
#declare ImIterateFunctions = array[NoOfIterations];

Iterate(RealFns, ImagFns, ReIterateFunctions, ImIterateFunctions)

#declare ReFn = FinalFunction(ReIterateFunctions);
#declare ImFn = FinalFunction(ImIterateFunctions);

#declare MagnitudeFn = MagnitudeFunction(ReFn, ImFn);
#declare PhaseFn = PhaseFunction(ReFn, ImFn);

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#declare HueFn = HueFunction(PhaseFn);

#declare LnMagnitudeFn = function(re, im) { ln(MagnitudeFn(re, im)) };

#declare A = 0.90; // 0 < A < 1
#declare LightnessFn = function(re, im) { (1 - pow(A, LnMagnitudeFn(re, im))) }; 

#declare Saturation = 1.0;

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
    right +3*x
    up +3*z
    sky +z
    location +y
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
                                                                   
