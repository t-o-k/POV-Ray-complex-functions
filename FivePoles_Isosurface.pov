// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

/*
https://github.com/t-o-k/POV-Ray-complex-functions

Copyright (c) 2021 Tor Olav Kristensen, http://subcube.com

Use of this source code is governed by the GNU Lesser General Public License version 3,
which can be found in the LICENSE file.
*/

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#version 3.7;

global_settings { assumed_gamma 1.0 }

#include "colors.inc"
#include "Complex_Functions.inc"
#include "Color_Functions.inc"

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

/*
https://matlabarticlesworld.blogspot.com/2020/01/what-is-coolest-thing-you-can-do-with.html

Fn(Z) = 1/(Z^5 - 2)^2

Fn =
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

AssembleFunctions(
    OperatorTypes,
    NoOfArguments,
    ReOperatorFunctions,
    ImOperatorFunctions,
    PartTypes,
    Arguments,
    ReFunctions,
    ImFunctions
)

#declare MagnitudeFn =
    MagnitudeFunction(
        OperatorTypes,
        FinalFunction(ReFunctions),
        FinalFunction(ImFunctions)
    )
;
#declare PhaseFn =
    PhaseFunction(
        OperatorTypes,
        FinalFunction(ReFunctions),
        FinalFunction(ImFunctions)
    )
;

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#declare H_Fn = function(re, im) { degrees(mod(Tau + PhaseFn(re, im), Tau)) };
#declare S = 1.0;
#declare L = 0.5;

#declare pMin = <-3.0, -0.2, -2.0>;
#declare pMax = <+3.0, +2.0, +2.0>;

isosurface {
    function { y - MagnitudeFn(x, z) }
    contained_by {
        box { pMin, pMax }
    }
    accuracy 0.001
    max_gradient 20
    FunctionsPigmentRGB(
        function { HSL_Rd_Fn(H_Fn(x, z), S, L) },
        function { HSL_Gn_Fn(H_Fn(x, z), S, L) },
        function { HSL_Bu_Fn(H_Fn(x, z), S, L) }
    )
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

background { color Gray70 }

light_source {
    100*<-3,  3, -1>
    color White
    shadowless
}

camera {
    angle 35
    location < -4,  7, -11>
    look_at < 0,  0,  0>
}

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
