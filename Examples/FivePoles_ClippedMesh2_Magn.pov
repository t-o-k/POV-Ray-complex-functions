// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
/*

https://github.com/t-o-k/POV-Ray-complex-functions

Copyright (c) 2021-2022 Tor Olav Kristensen, http://subcube.com

Use of this source code is governed by the GNU Lesser General Public License version 3,
which can be found in the LICENSE file.

*/
// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#version 3.7;

global_settings { assumed_gamma 1.0 }

#include "colors.inc"
#include "../Complex_Functions.inc"
#include "../Color_Functions.inc"
#include "../Function_Meshes.inc"

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

/*
The function below was found here:

    https://matlabarticlesworld.blogspot.com/2020/01/what-is-coolest-thing-you-can-do-with.html


Prefix/Infix notation:

    Fn(Z) = 1/(Z^5 - 2)^2


Prefix notation:

    Fn(Z) =
        Inv(
            Sqr(
                Sub(
                    Pow(
                        Z(),
                        Const(5.0)
                    ),
                    Const(2.0)
                )
            )
        )


Postfix notation:

    (Z)Fn =
        (
            (
                (
                    (
                        ()Z,
                        (5.0)Const
                    )Pow,
                    (2.0)Const
                )Sub
            )Sqr
        )Inv
*/


#declare No = 7;

#declare PartTypes = array[No];
#declare Arguments = array[No];

#declare PartTypes[0] = "Z";
#declare Arguments[0] = ZFn();                                  


#declare PartTypes[1] = "Const";
#declare Arguments[1] = RealConstFn(+5.0);

#declare PartTypes[2] = "Pow";
#declare Arguments[2] = Arg2Fn(0, 1);

#declare PartTypes[3] = "Const";
#declare Arguments[3] = RealConstFn(+2.0);

#declare PartTypes[4] = "Sub";
#declare Arguments[4] = Arg2Fn(2, 3);

#declare PartTypes[5] = "Sqr";
#declare Arguments[5] = Arg1Fn(4);

#declare PartTypes[6] = "Inv";
#declare Arguments[6] = Arg1Fn(5);


#declare ReFunctions = array[No];
#declare ImFunctions = array[No];

AssembleFunctions(PartTypes, Arguments, ReFunctions, ImFunctions)

#declare RealFn = FinalFunction(ReFunctions);
#declare ImagFn = FinalFunction(ImFunctions);

#declare MagnitudeFn = MagnitudeFunction(RealFn, ImagFn);
#declare PhaseFn = PhaseFunction(RealFn, ImagFn);

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#declare HueFn = HueFunction(PhaseFn);

#declare A = 0.20;  // 0 < A < 1
#declare LightnessFn = function(re, im) { 1 - pow(A, MagnitudeFn(re, im)) }; 

#declare Saturation = 1.00;

#declare pMin = <-3, -2, -2>;
#declare pMax = <+3, +2, +2>;

#declare NoOfIntervalsX = 400;
#declare NoOfIntervalsZ = 400;

object {
    ClippedFunctionMesh2(MagnitudeFn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)
    FunctionsPigmentRGB(
        function { HSL_RD_FN(HueFn(x, z), Saturation, LightnessFn(x, z)) },
        function { HSL_GN_FN(HueFn(x, z), Saturation, LightnessFn(x, z)) },
        function { HSL_BU_FN(HueFn(x, z), Saturation, LightnessFn(x, z)) }
    )
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

background { color Gray70 }

light_source {
    100*<-3, +3, -1>
    color White
    shadowless
}

camera {
    angle 35
    location <-4, +7, -11>
    look_at < 0,  0,  0>
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
