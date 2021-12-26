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

#declare Tau = 2*pi;


#macro IndexOfString(Str, Strings)

    #local NoOfStrings = dimension_size(Strings, 1);
    #local Found = false;
    #local Idx = 0;
    #while ((! Found) & (Idx < NoOfStrings))
        #if (strcmp(Str, Strings[Idx]) = 0)
            #local Found = true;
        #else
            #local Idx = Idx + 1;
        #end // if 
    #end // while 
    #if (! Found)
        #local Idx = -1;
    #end // if 

    Idx

#end // macro IndexOfString

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro HandleZerosFunction(PowFn)

    function(re1, im1, re2, im2) {
        select(
            im1,
            PowFn(re1, im1, re2, im2),              // (re1 + im1*j)^(re2 + im2*j)
            select(
                re1,
                PowFn(re1, im1, re2, im2),          // re1^(re2 + im2*j)
                select(
                    im2,
                    0,                              // 0^(re2 + im2*j) = 0
                    select(
                        re2,
                        0,                          // 0^re2 = 0
                        PowFn(re1, im1, re2, im2),  // 0^0 = ?
                        0                           // 0^re2 = 0
                    ),
                    0                               // 0^(re2 + im2*j) = 0
                ),
                PowFn(re1, im1, re2, im2)           // re1^(re2 + im2*j)
            ),
            PowFn(re1, im1, re2, im2)               // (re1 + im1*j)^(re2 + im2*j)
        )
    }

#end // macro HandleZerosFunction


// j = sqrt(-1)
// Z = re + im*j

#declare NoOfOperators = 29;

#declare OperatorTypes =
    array[NoOfOperators] {

        // Re(Z) = re
        "Re",

        // Im(Z) = im
        "Im",

        // Pos(Z) = +Z
        "Pos",

        // Neg(Z) = -Z
        "Neg",

        // Conj(Z) = re - im*j
        "Conj",

        // Abs(Z) = |Z| = sqrt(Z*conj(Z))
        "Abs",

        // Phase(Z) = atan2(im, re)
        "Phase",

        // Ln(Z) = ln(abs(Z)) + phase(Z)*j
        "Ln",

        // Exp(Z) = e^Z
        "Exp",

        // Sqr(Z) = Z^2
        "Sqr",

        // Sqrt(Z) = Z^0.5
        "Sqrt",

        // Inv(Z) = 1/Z
        "Inv",

        // Cos(Z) = (e^(-Z*j) + e^(+Z*j))/2
        "Cos",

        // Acos(Z) = -ln(Z + sqrt(1 - Z^2)*j)*j
        "Acos",

        // Sin(Z) = (e^(-Z*j) - e^(+Z*j))/2*j
        "Sin",

        // Asin(Z) = -ln(sqrt(1 - Z^2) + Z*j)*j
        "Asin",

        // Tan(Z) = sin(Z)/cos(Z)
        "Tan",

        // Atan(Z) = (ln(1 - Z*j) - ln(1 + Z*j))/2*j
        "Atan",

        // Cosh(Z) = +(e^(+Z) + e^(-Z))/2
        "Cosh",

        // Acosh(Z) = +2*ln(+sqrt((Z + 1)/2) +sqrt((Z - 1)/2))
        "Acosh",

        // Sinh(Z) = +(e^(+Z) - e^(-Z))/2
        "Sinh",

        // Asinh(Z) = +ln(Z + sqrt(+Z^2 +1))
        "Asinh",

        // Tanh(Z) = sinh(Z)/cosh(Z)
        "Tanh",

        // Atanh(Z) = (ln(1 + Z) - ln(1 - Z))/2
        "Atanh",

        // Add(Z1, Z2) = Z1 + Z2
        "Add", 

        // Sub(Z1, Z2) = Z1 - Z2
        "Sub",

        // Mul(Z1, Z2) = Z1*Z2
        "Mul",

        // Div(Z1, Z2) = Z1/Z2
        "Div",

        // Pow(Z1, Z2) = Z1^Z2
        "Pow"
    }
;
#declare NoOfArguments =
    array[NoOfOperators] {

        // Re
        1,

        // Im
        1,

        // Pos
        1,

        // Neg
        1,

        // Conj
        1,

        // Abs
        1,

        // Phase
        1,

        // Ln
        1,

        // Exp
        1,

        // Sqr
        1,

        // Sqrt
        1,

        // Inv
        1,

        // Cos
        1,

        // Acos
        1,

        // Sin
        1,

        // Asin
        1,

        // Tan
        1,

        // Atan
        1,

        // Cosh
        1,

        // Acosh
        1,

        // Sinh
        1,

        // Asinh
        1,

        // Tanh
        1,

        // Atanh
        1,

        // Add 
        2,

        // Sub 
        2,

        // Mul
        2,

        // Div
        2,

        // Pow
        2
    }
;
#declare ReOperatorFunctions =
    array[NoOfOperators] {

        // Re
        function(re, im) { +re },

        // Im
        function(re, im) { 0 },

        // Pos
        function(re, im) { +re },

        // Neg
        function(re, im) { -re },

        // Conj
        function(re, im) { +re },

        // Abs
        function(re, im) { +sqrt(+pow(re, 2) +pow(im, 2)) },

        // Phase
        function(re, im) { +atan2(im, re) },

        // Ln
        function(re, im) { +ln(+pow(re, 2) +pow(im, 2))/2 },

        // Exp
        function(re, im) { +exp(re)*cos(im) },

        // Sqr
        function(re, im) { +pow(re, 2) -pow(im, 2) },

        // Sqrt
        function(re, im) {
            +sqrt((sqrt(+pow(re, 2) +pow(im, 2)) +re)/2)
            // pow(+pow(re, 2) +pow(im, 2), 0.25)*cos(atan2(im, re)/2)
        },

        // Inv
        function(re, im) { +re/(+pow(re, 2) +pow(im, 2)) },

        // Cos
        function(re, im) { +cos(re)*cosh(im) },

        // Acos
        function(re, im) {
            +atan2(
                +im
                +pow(+pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                    *cos(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2),
                +re
                -pow(+pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                    *sin(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2)
            )
        },

        // Sin
        function(re, im) { +sin(re)*cosh(im) },

        // Asin
        function(re, im) {
            +atan2(
                +re
                +pow(+pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                    *sin(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2),
                -im
                +pow(+pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                    *cos(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2)
            )
        },

        // Tan
        function(re, im) { +sin(2*re)/(+cos(2*re) +cosh(2*im)) },

        // Atan
        function(re, im) {
            +(
                +atan2(+re, +1 -im)
                -atan2(-re, +1 +im)
            )/2
        },

        // Cosh
        function(re, im) { +cosh(re)*cos(im) },

        // Acosh
        function(re, im) {
            +ln(
                +pow(
                    +pow((+pow(re + 1, 2) +pow(im, 2))/4, 0.25)*cos(atan2(im/2, (re + 1)/2)/2)
                    +pow((+pow(re - 1, 2) +pow(im, 2))/4, 0.25)*cos(atan2(im/2, (re - 1)/2)/2),
                    2
                )
                +pow(
                    +pow((+pow(re + 1, 2) +pow(im, 2))/4, 0.25)*sin(atan2(im/2, (re + 1)/2)/2)
                    +pow((+pow(re - 1, 2) +pow(im, 2))/4, 0.25)*sin(atan2(im/2, (re - 1)/2)/2),
                    2
                )
            )
        },

        // Sinh
        function(re, im) { +sinh(re)*cos(im) },

        // Asinh
        function(re, im) {
            ln(
                +pow(
                    +re
                    +pow(+pow(+1 +pow(re, 2) -pow(im, 2), 2) +4*pow(re*im, 2), 0.25)
                        *cos(atan2(+2*re*im, +1 +pow(re, 2) -pow(im, 2))/2),
                    2
                )
                +pow(
                    +im
                    +pow(+pow(+1 +pow(re, 2) -pow(im, 2), 2) +4*pow(re*im, 2), 0.25)
                        *sin(atan2(+2*re*im, +1 +pow(re, 2) -pow(im, 2))/2),
                    2
                )
            )/2
        },

        // Tanh
        function(re, im) { +sinh(2*re)/(+cosh(2*re) +cos(2*im)) },

        // Atanh
        function(re, im) {
            (
                +ln(+pow(+1 +re, 2) +pow(+im, 2))
                -ln(+pow(+1 -re, 2) +pow(-im, 2))
            )/4
        },

        // Add
        function(re1, im1, re2, im2) { +re1 +re2 },

        // Sub
        function(re1, im1, re2, im2) { +re1 -re2 },

        // Mul
        function(re1, im1, re2, im2) { +re1*re2 -im1*im2 },

        // Div
        function(re1, im1, re2, im2) {
            (+re1*re2 +im1*im2)
            /
            (+re2*re2 +im2*im2)
        },

        // Pow
        function(re1, im1, re2, im2) {
            exp(+re2/2*ln(+pow(re1, 2) +pow(im1, 2)) -im2*atan2(im1, re1))
            *
            cos(+im2/2*ln(+pow(re1, 2) +pow(im1, 2)) +re2*atan2(im1, re1))
        }
    }
;
#declare ImOperatorFunctions =
    array[NoOfOperators] {

        // Re
        function(re, im) { 0 },

        // Im
        function(re, im) { +im },

        // Pos
        function(re, im) { +im },

        // Neg
        function(re, im) { -im },

        // Conj
        function(re, im) { -im },

        // Abs
        function(re, im) { 0 },

        // Phase
        function(re, im) { 0 },

        // Ln
        function(re, im) { +atan2(im, re) },

        // Exp
        function(re, im) { +exp(re)*sin(im) },

        // Sqr
        function(re, im) { +2*re*im },

        // Sqrt
        function(re, im) {
            +sqrt((sqrt(+pow(re, 2) +pow(im, 2)) -re)/2)*select(im, -1, +1)
            // pow(+pow(re, 2) +pow(im, 2), 0.25)*sin(atan2(im, re)/2)
        },

        // Inv
        function(re, im) { -im/(+pow(re, 2) +pow(im, 2)) },

        // Cos
        function(re, im) { -sin(re)*sinh(im) },

        // Acos
        function(re, im) {
            -ln(
                +pow(
                    +re
                    -pow(pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                        *sin(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2),
                    2
                )
                +pow(
                    +im
                    +pow(pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                        *cos(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2),
                    2
                )
            )/2
        },

        // Sin
        function(re, im) { +cos(re)*sinh(im) },

        // Asin
        function(re, im) {
            -ln(
                +pow(
                    -im
                    +pow(+pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                        *cos(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2),
                    2
                )
                +pow(
                    +re
                    +pow(+pow(+1 -pow(re, 2) +pow(im, 2), 2) +pow(-2*re*im, 2), 0.25)
                        *sin(atan2(-2*re*im, +1 -pow(re, 2) +pow(im, 2))/2),
                    2
                )
            )/2
        },

        // Tan
        function(re, im) { +sinh(2*im)/(+cos(2*re) +cosh(2*im)) },

        // Atan
        function(re, im) {
            -(
                +ln(+pow(+re, 2) +pow(+1 -im, 2))
                -ln(+pow(-re, 2) +pow(+1 +im, 2))
            )/4
        },

        // Cosh
        function(re, im) { +sinh(re)*sin(im) },

        // Acosh
        function(re, im) {
            atan2(
                +pow((+pow(+re +1, 2) +pow(im, 2))/4, 0.25)*sin(atan2(im/2, (+re +1)/2)/2)
                +pow((+pow(+re -1, 2) +pow(im, 2))/4, 0.25)*sin(atan2(im/2, (+re -1)/2)/2),
                +pow((+pow(+re +1, 2) +pow(im, 2))/4, 0.25)*cos(atan2(im/2, (+re +1)/2)/2)
                +pow((+pow(+re -1, 2) +pow(im, 2))/4, 0.25)*cos(atan2(im/2, (+re -1)/2)/2)
            )*2
        },

        // Sinh
        function(re, im) { +cosh(re)*sin(im) },

        // Asinh
        function(re, im) {
            +atan2(
                +im
                +pow(+pow(+1 +pow(re, 2) -pow(im, 2), 2) +4*pow(re*im, 2), 0.25)
                    *sin(atan2(+2*re*im, +1 +pow(re, 2) -pow(im, 2))/2),
                +re
                +pow(+pow(+1 +pow(re, 2) -pow(im, 2), 2) +4*pow(re*im, 2), 0.25)
                    *cos(atan2(+2*re*im, +1 +pow(re, 2) -pow(im, 2))/2)
            )
        },

        // Tanh
        function(re, im) { +sin(2*im)/(cosh(2*re) + cos(2*im)) },

        // Atanh
        function(re, im) {
            (
                +atan2(+im, +1 +re)
                -atan2(-im, +1 -re)
            )/2
        },

        // Add
        function(re1, im1, re2, im2) { +im1 +im2 },

        // Sub 
        function(re1, im1, re2, im2) { +im1 -im2 },

        // Mul
        function(re1, im1, re2, im2) { +re1*im2 +im1*re2 },

        // Div
        function(re1, im1, re2, im2) {
            (-re1*im2 +im1*re2)
            /
            (+re2*re2 +im2*im2)
        },

        // Pow
        function(re1, im1, re2, im2) {
            exp(+re2/2*ln(+pow(re1, 2) +pow(im1, 2)) -im2*atan2(im1, re1))
            *
            sin(+im2/2*ln(+pow(re1, 2) +pow(im1, 2)) +re2*atan2(im1, re1))
        }
    }
;
#undef NoOfOperators

#declare PowIdx = IndexOfString("Pow", OperatorTypes);
#undef ReOperatorFunctions[PowIdx]
#declare ReOperatorFunctions[PowIdx] =
    HandleZerosFunction(
        function(re1, im1, re2, im2) {
                exp(+re2/2*ln(+pow(re1, 2) +pow(im1, 2)) -im2*atan2(im1, re1))
            *
                cos(+im2/2*ln(+pow(re1, 2) +pow(im1, 2)) +re2*atan2(im1, re1))
        }
    )
;
#undef ImOperatorFunctions[PowIdx]
#declare ImOperatorFunctions[PowIdx] =
    HandleZerosFunction(
        function(re1, im1, re2, im2) {
                exp(+re2/2*ln(+pow(re1, 2) +pow(im1, 2)) -im2*atan2(im1, re1))
            *
                sin(+im2/2*ln(+pow(re1, 2) +pow(im1, 2)) +re2*atan2(im1, re1))
        }
    )
;
#undef PowIdx

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro ReZFunction()

    function(re, im) { re }

#end // macro ReZFunction


#macro ImZFunction()

    function(re, im) { im }

#end // macro ImZFunction


#macro ReConstFunction(ReVal)

    function(re, im) { ReVal }

#end // macro ReConstFunction


#macro ImConstFunction(ImVal)

    function(re, im) { ImVal }

#end // macro ImConstFunction


#macro Args1Function(OpFn, ReFns, ImFns, Arg)

    function(re, im) {
        OpFn(
            ReFns[Arg](re, im), ImFns[Arg](re, im)
        )
    }

#end // macro Args1Function


#macro Args2Function(OpFn, ReFns, ImFns, Arg1, Arg2)

    function(re, im) {
        OpFn(
            ReFns[Arg1](re, im), ImFns[Arg1](re, im),
            ReFns[Arg2](re, im), ImFns[Arg2](re, im)
        )
    }

#end // macro Args2Function


#macro GetOpFunction(OpTypes, NoOfArgs, OpFns, ReFns, ImFns, ExprType, ArgNoFn)
 
    #local Idx = IndexOfString(ExprType, OpTypes);
    #if (Idx < 0)
        #error "Unknown function type"
    #end // if
    #switch (NoOfArgs[Idx])
        #case (1)
            Args1Function(
                OpFns[Idx],
                ReFns,
                ImFns,
                ArgNoFn(1)
            )
            #break
        #case (2)
            Args2Function(
                OpFns[Idx],
                ReFns,
                ImFns,
                ArgNoFn(1),
                ArgNoFn(2)
            )
            #break
    #else
        #error "Uknown problem"
    #end // switch

#end // macro GetOpFunction


#macro ReChooseFunction(OpTypes, NoOfArgs, ReOpFns, ReFns, ImFns, ExprType, ArgNoFn)
 
    #if (strcmp(ExprType, "Z") = 0)
        ReZFunction()
    #else
        #if (strcmp(ExprType, "Const") = 0)
            #local ReVal = ArgNoFn(-1);
            ReConstFunction(ReVal)
        #else
            GetOpFunction(
                OpTypes,
                NoOfArgs,
                ReOpFns,
                ReFns,
                ImFns,
                ExprType,
                ArgNoFn
            )
        #end // if
    #end // if

#end // macro ReChooseFunction


#macro ImChooseFunction(OpTypes, NoOfArgs, ImOpFns, ReFns, ImFns, ExprType, ArgNoFn)

    #if (strcmp(ExprType, "Z") = 0)
        ImZFunction()
    #else
        #if (strcmp(ExprType, "Const") = 0)
            #local ImVal = ArgNoFn(-2);
            ImConstFunction(ImVal)
        #else
            GetOpFunction(
                OpTypes,
                NoOfArgs,
                ImOpFns,
                ReFns,
                ImFns,
                ExprType,
                ArgNoFn
            )
        #end // if
    #end // if

#end // macro ImChooseFunction


#macro AssembleFunctions(OpTypes, NoOfArgs, ReOpFns, ImOpFns, ExprTypes, ArgNoFns, ReFns, ImFns)

    #local No = dimension_size(ExprTypes, 1);
    #for (I, 0, No-1)
        #declare ExprType = ExprTypes[I];
        #declare ReFns[I] =
            ReChooseFunction(
                OpTypes,
                NoOfArgs,
                ReOpFns,
                ReFns,
                ImFns,
                ExprType,
                ArgNoFns[I]
             )
        #declare ImFns[I] =
            ImChooseFunction(
                OpTypes,
                NoOfArgs,
                ImOpFns,
                ReFns,
                ImFns,
                ExprType,
                ArgNoFns[I]
            )
    #end // for

#end // macro AssembleFunctions


#macro ZFn()

    function(s) { 0 + sqrt(-1) } // This function should never be called.

#end // macro ZFn


#macro RealConstFn(ReVal)

    function(s) { select(s + 1, 0, ReVal, 0) }

#end // macro RealConstFn


#macro ImagConstFn(ImVal)

    function(s) { select(s + 2, 0, ImVal, 0) }

#end // macro ImagConstFn


#macro ComplexConstFn(ReVal, ImVal)

    function(s) { select(s + 1, select(s + 2, 0, ImVal, 0), ReVal, 0) }

#end // macro ComplexConstFn


#macro Arg1Fn(Arg1)

    function(s) { select(s - 1, -1, Arg1, -1) }

#end // macro Arg1Fn


#macro Arg2Fn(Arg1, Arg2)

    function(s) { select(s - 1, -1, Arg1, select(s - 2, -1, Arg2, -1)) }

#end // macro Arg2Fn


#macro FinalFunction(Fns)

    #local NoOfFns = dimension_size(Fns, 1);

    function(re, im) { Fns[NoOfFns-1](re, im) }

#end // macro FinalFunction


#macro GetReOpFunction(OpName, OpTypes)

    #local Idx = IndexOfString(OpName, OpTypes);

    function(re, im) { ReOperatorFunctions[Idx](re, im) }

#end // macro GetReOpFunction


#macro GetImOpFunction(OpName, OpTypes)

    #local Idx = IndexOfString(OpName, OpTypes);

    function(re, im) { ImOperatorFunctions[Idx](re, im) }

#end // macro GetImOpFunction


#macro CompoundFunction(Fn, ReFn, ImFn)

    function(re, im) { Fn(ReFn(re, im), ImFn(re, im)) }

#end // macro CompoundFunction


#macro MagnitudeFunction(OpTypes, ReFn, ImFn)

    CompoundFunction(GetReOpFunction("Abs", OpTypes), ReFn, ImFn)

#end // macro MagnitudeFunction


#macro PhaseFunction(OpTypes, ReFn, ImFn)

    CompoundFunction(GetReOpFunction("Phase", OpTypes), ReFn, ImFn )

#end // macro PhaseFunction

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
