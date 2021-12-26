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
                function { RdFn(x, y, z) }
                color_map {
                    [ 0 red 0 ]
                    [ 1 red 3 ]
                }
            ]
            [
                function { GnFn(x, y, z) }
                color_map {
                    [ 0 green 0 ]
                    [ 1 green 3 ]
                }
            ]
            [
                function { BuFn(x, y, z) }
                color_map {
                    [ 0 blue 0 ]
                    [ 1 blue 3 ]
                }
            ]
        }
    }

#end // macro FunctionsPigmentRGB

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

// https://en.wikipedia.org/wiki/HSL_and_HSV

#declare HSL_RD1_FN =
    function(hm_, c_, x_) {
        0
        + select(hm_ - 0, c_, select(hm_ - 1, c_,  0))
        + select(hm_ - 1,  0, select(hm_ - 2, x_,  0))
        + select(hm_ - 2,  0, select(hm_ - 3,  0,  0))
        + select(hm_ - 3,  0, select(hm_ - 4,  0,  0))
        + select(hm_ - 4,  0, select(hm_ - 5, x_,  0))
        + select(hm_ - 5,  0, select(hm_ - 6, c_, c_))
    }
;
#declare HSL_GN1_FN =
    function(hm_, c_, x_) {
        0
        + select(hm_ - 0,  0, select(hm_ - 1, x_,  0))
        + select(hm_ - 1,  0, select(hm_ - 2, c_,  0))
        + select(hm_ - 2,  0, select(hm_ - 3, c_,  0))
        + select(hm_ - 3,  0, select(hm_ - 4, x_,  0))
        + select(hm_ - 4,  0, select(hm_ - 5,  0,  0))
        + select(hm_ - 5,  0, select(hm_ - 6,  0, x_))
    }
;
#declare HSL_BU1_FN =
    function(hm_, c_, x_) {
        0
        + select(hm_ - 0, x_, select(hm_ - 1,  0,  0))
        + select(hm_ - 1,  0, select(hm_ - 2,  0,  0))
        + select(hm_ - 2,  0, select(hm_ - 3, x_,  0))
        + select(hm_ - 3,  0, select(hm_ - 4, c_,  0))
        + select(hm_ - 4,  0, select(hm_ - 5, c_,  0))
        + select(hm_ - 5,  0, select(hm_ - 6, x_,  0))
    }
;

#declare HSL_RD2_FN =
    function(l_, c_, hm_) {
        HSL_RD1_FN(
            hm_,
            c_,
            c_*(1 - abs(mod(hm_, 2) - 1)) // X
        )
        + l_ - c_/2 // m
    }
;
#declare HSL_GN2_FN =
    function(l_, c_, hm_) {
        HSL_GN1_FN(
            hm_,
            c_,
            c_*(1 - abs(mod(hm_, 2) - 1)) // X
        )
         + l_ - c_/2 // m
    }
;
#declare HSL_BU2_FN =
    function(l_, c_, hm_) {
        HSL_BU1_FN(
            hm_,
            c_,
            c_*(1 - abs(mod(hm_, 2) - 1)) // X
        )
        + l_ - c_/2 // m
    }
;

#declare HSL_RD_FN =
    function(h_, sl_, l_) {
        HSL_RD2_FN(
            l_,
            (1 - abs(2*l_ - 1))*sl_, // C
            h_/60 // Hm
        )
    }
;
#declare HSL_GN_FN =
    function(h_, sl_, l_) {
        HSL_GN2_FN(
            l_,
            (1 - abs(2*l_ - 1))*sl_, // C
            h_/60 // Hm
        )
    }
;
#declare HSL_BU_FN =
    function(h_, sl_, l_) {
        HSL_BU2_FN(
            l_,
            (1 - abs(2*l_ - 1))*sl_, // C
            h_/60 // Hm
        )
    }
;

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
