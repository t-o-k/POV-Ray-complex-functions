// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
/*

https://github.com/t-o-k/POV-Ray-complex-functions

Copyright (c) 2021 Tor Olav Kristensen, http://subcube.com

Use of this source code is governed by the GNU Lesser General Public License version 3,
which can be found in the LICENSE file.

*/
// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#version 3.7;

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro FunctionsPigmentRGB(RdFn, GnFn, BuFn)

    pigment {
        average
        pigment_map {
            [
                function { min(max(0, RdFn(x, y, z)), 1) }
                color_map {
                    [ 0 red 0 ]
                    [ 1 red 3 ]
                }
            ]
            [
                function { min(max(0, GnFn(x, y, z)), 1) }
                color_map {
                    [ 0 green 0 ]
                    [ 1 green 3 ]
                }
            ]
            [
                function { min(max(0, BuFn(x, y, z)), 1) }
                color_map {
                    [ 0 blue 0 ]
                    [ 1 blue 3 ]
                }
            ]
        }
    }

#end // macro FunctionsPigmentRGB


#macro HueFunction(PhaseFn)

    function(re, im) { mod(360 + degrees(PhaseFn(re, im)), 360) }

#end // macro HueFunction


#macro RampFunction(Interval, ShiftFraction)

    #local HalfInterval = Interval/2;
    #local SI = ShiftFraction*Interval;

    function(s) {
        mod(s + SI, Interval)
        +
        select(s + SI, +HalfInterval, -HalfInterval)
    }

#end // macro RampFunction


#macro StripeFunction(Width, OutsideValue, InsideValue)
                                                                       
    #local HalfWidth = Width/2;

    function (s) {
        select(
            s + HalfWidth,
            OutsideValue,
            select(
                s - HalfWidth,
                InsideValue,
                OutsideValue
            )
        )
    }

#end // macro StripeFunction

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

// https://en.wikipedia.org/wiki/HSL_and_HSV

#macro HSL2_Function(Fn)

    function(h_, sl_, l_) {
        Fn(
            l_, // L
            (1 - abs(2*l_ - 1))*sl_, // C
            h_/60 // Hm
        )
    }

#end // macro HSL2_Function


#macro HSL1_Function(Fn)

    HSL2_Function(
        function(l_, c_, hm_) {
            Fn(
                hm_, // Hm
                c_, // C
                c_*(1 - abs(mod(hm_, 2) - 1)) // X
            )
            + l_ - c_/2 // m
        }
    )

#end // macro HSL1_Function


#macro HSL_Rd_Function()

    HSL1_Function(
        function(hm_, c_, x_) {
            0
            + select(hm_ - 0, c_, select(hm_ - 1, c_,  0))
            + select(hm_ - 1,  0, select(hm_ - 2, x_,  0))
            + select(hm_ - 2,  0, select(hm_ - 3,  0,  0))
            + select(hm_ - 3,  0, select(hm_ - 4,  0,  0))
            + select(hm_ - 4,  0, select(hm_ - 5, x_,  0))
            + select(hm_ - 5,  0, select(hm_ - 6, c_, c_))
        }
    )

#end // macro HSL_Rd_Function


#macro HSL_Gn_Function()

    HSL1_Function(
        function(hm_, c_, x_) {
            0
            + select(hm_ - 0,  0, select(hm_ - 1, x_,  0))
            + select(hm_ - 1,  0, select(hm_ - 2, c_,  0))
            + select(hm_ - 2,  0, select(hm_ - 3, c_,  0))
            + select(hm_ - 3,  0, select(hm_ - 4, x_,  0))
            + select(hm_ - 4,  0, select(hm_ - 5,  0,  0))
            + select(hm_ - 5,  0, select(hm_ - 6,  0, x_))
        }
    )

#end // macro HSL_Gn_Function


#macro HSL_Bu_Function()

    HSL1_Function(
        function(hm_, c_, x_) {
            0
            + select(hm_ - 0, x_, select(hm_ - 1,  0,  0))
            + select(hm_ - 1,  0, select(hm_ - 2,  0,  0))
            + select(hm_ - 2,  0, select(hm_ - 3, x_,  0))
            + select(hm_ - 3,  0, select(hm_ - 4, c_,  0))
            + select(hm_ - 4,  0, select(hm_ - 5, c_,  0))
            + select(hm_ - 5,  0, select(hm_ - 6, x_,  0))
        }
    )

#end // macro HSL_Bu_Function


#declare HSL_RD_FN = HSL_Rd_Function();
#declare HSL_GN_FN = HSL_Gn_Function();
#declare HSL_BU_FN = HSL_Bu_Function();

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
