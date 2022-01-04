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
#include "Complex_Functions.inc"
#include "Function_Meshes.inc"

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

/*
Fn(Z) = (Z^2 + 1)/(Z^2 - 1)

Fn =
    Div(
        Add(
            Sqr(
                Z()
            ),
            Const(1.0)
        ),
        Sub(
            Sqr(
                Z()
            ),
            Const(1.0)
        )
    )
*/


#declare No = 9;

#declare PartTypes = array[No];
#declare Arguments = array[No];

#declare PartTypes[0] = "Z";
#declare Arguments[0] = ZFn();

#declare PartTypes[1] = "Sqr";
#declare Arguments[1] = Arg1Fn(0);

#declare PartTypes[2] = "Const";
#declare Arguments[2] = RealConstFn(1.0);

#declare PartTypes[3] = "Add";
#declare Arguments[3] = Arg2Fn(1, 2);

#declare PartTypes[4] = "Z";
#declare Arguments[4] = ZFn();

#declare PartTypes[5] = "Sqr";
#declare Arguments[5] = Arg1Fn(4);

#declare PartTypes[6] = "Const";
#declare Arguments[6] = RealConstFn(1.0);

#declare PartTypes[7] = "Sub";
#declare Arguments[7] = Arg2Fn(5, 6);

#declare PartTypes[8] = "Div";
#declare Arguments[8] = Arg2Fn(3, 7);


/*
// Alternative way

#declare No = 6;

#declare PartTypes = array[No];
#declare Arguments = array[No];

#declare PartTypes[0] = "Z";
#declare Arguments[0] = ZFn();

#declare PartTypes[1] = "Sqr";
#declare Arguments[1] = Arg1Fn(0);

#declare PartTypes[2] = "Const";
#declare Arguments[2] = RealConstFn(1.0);

#declare PartTypes[3] = "Add";
#declare Arguments[3] = Arg2Fn(1, 2);

#declare PartTypes[4] = "Sub";
#declare Arguments[4] = Arg2Fn(1, 2);

#declare PartTypes[5] = "Div";
#declare Arguments[5] = Arg2Fn(3, 4);
*/


#declare ReFunctions = array[No];
#declare ImFunctions = array[No];

AssembleFunctions(PartTypes, Arguments, ReFunctions, ImFunctions)

#declare RealFn = FinalFunction(ReFunctions);
#declare ImagFn = FinalFunction(ImFunctions);

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

#declare ColorWheel =
    color_map {
        [ 0/6 color rgb <1, 0, 0> ]
        [ 1/6 color rgb <1, 1, 0> ]
        [ 2/6 color rgb <0, 1, 0> ]
        [ 3/6 color rgb <0, 1, 1> ]
        [ 4/6 color rgb <0, 0, 1> ]
        [ 5/6 color rgb <1, 0, 1> ]
        [ 6/6 color rgb <1, 0, 0> ]
    }

#declare ColorSelectFn = function(re, im) { mod(TAU + PhaseFn(re, im), TAU)/TAU };

#declare pMin = <-3, -4, -3>;
#declare pMax = < 3,  4,  3>;

#declare NoOfIntervalsX = 80;
#declare NoOfIntervalsZ = 80;

object {
    ClippedFunctionMesh(MagnitudeFn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)
    // ClippedFunctionMesh(RealFn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)
    // ClippedFunctionMesh(ImagFn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)
    pigment {
        function { ColorSelectFn(x, z) }
        color_map { ColorWheel }
    }
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

background { color Gray70 }

light_source {
    100*(3*y -4*z)
    color White
    shadowless
    rotate +140*y
}

camera {
    angle 60
    location 5.5*y -10.0*z
    look_at 1.0*y
    rotate -150*y
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
