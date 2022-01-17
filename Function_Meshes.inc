// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
/*

https://github.com/t-o-k/POV-Ray-complex-functions

Copyright (c) 2021-2022 Tor Olav Kristensen, http://subcube.com

Use of this source code is governed by the GNU Lesser General Public License version 3,
which can be found in the LICENSE file.

*/
// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#version 3.7;

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro ClampFunction(Fn, Min, Max)

    function(re, im) { min(max(Min, Fn(re, im)), Max) }

#end // macro ClampFunction

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro FunctionSpheres(Fn, MinX, MaxX, MinZ, MaxZ, NoOfIntervalsX, NoOfIntervalsZ, Radius)

    #local DX = (MaxX - MinX)/NoOfIntervalsX;
    #local DZ = (MaxZ - MinZ)/NoOfIntervalsZ;

    union {
        #local X = MinX;
        #for (CntX, 0, NoOfIntervalsX)
            #local Z = MinZ;
            #for (CntZ, 0, NoOfIntervalsZ)
                sphere { <X, Fn(X, Z), Z>, Radius }
                #local Z = Z + DZ;
            #end // for
            #local X = X + DX;
        #end // for
    }

#end // macro FunctionSpheres


#macro ClampedFunctionSpheres(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ, Radius)

    FunctionSpheres(
        ClampFunction(Fn, pMin.y, pMax.y),
        pMin.x, pMax.x,
        pMin.z, pMax.z,
        NoOfIntervalsX, NoOfIntervalsZ,
        Radius
    )

#end // macro ClampedFunctionSpheres


#macro ClippedFunctionSpheres(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ, Radius)

    #local MinX = pMin.x;
    #local MinY = pMin.y;
    #local MinZ = pMin.z;
    #local MaxX = pMax.x;
    #local MaxY = pMax.y;
    #local MaxZ = pMax.z;
    #local DX = (MaxX - MinX)/NoOfIntervalsX;
    #local DZ = (MaxZ - MinZ)/NoOfIntervalsZ;

    union {
        #local X = MinX;
        #for (CntX, 0, NoOfIntervalsX)
            #local Z = MinZ;
            #for (CntZ, 0, NoOfIntervalsZ)
                #local Y = Fn(X, Z);
                #if ((MinY < Y) & (Y < MaxY))
                    sphere { <X, Y, Z>, Radius }
                #end // if
                #local Z = Z + DZ;
            #end // for
            #local X = X + DX;
        #end // for
    }

#end // macro ClippedFunctionSpheres

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro FunctionMesh(Fn, MinX, MaxX, MinZ, MaxZ, NoOfIntervalsX, NoOfIntervalsZ)

    #local DX = (MaxX - MinX)/NoOfIntervalsX;
    #local DZ = (MaxZ - MinZ)/NoOfIntervalsZ;

    mesh {
        #local X0 = MinX;
        #for (CntX, 0, NoOfIntervalsX-1)
            #local X1 = X0 + DX;
            #local Z0 = MinZ;
            #for (CntZ, 0, NoOfIntervalsZ-1)
                #local Z1 = Z0 + DZ;
                #local Y00 = Fn(X0, Z0);
                #local Y10 = Fn(X1, Z0);
                #local Y11 = Fn(X1, Z1);
                #local Y01 = Fn(X0, Z1);
                triangle { <X0, Y00, Z0>, <X1, Y11, Z1>, <X1, Y10, Z0> }
                triangle { <X1, Y11, Z1>, <X0, Y00, Z0>, <X0, Y01, Z1> }
                #local Z0 = Z1;
            #end // for
            #local X0 = X1;
        #end // for
    }                        

#end // macro FunctionMesh


#macro ClampedFunctionMesh(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)

    FunctionMesh(
        ClampFunction(Fn, pMin.y, pMax.y),
        pMin.x, pMax.x,
        pMin.z, pMax.z,
        NoOfIntervalsX, NoOfIntervalsZ
    )

#end // macro ClampedFunctionMesh


#macro ClippedFunctionMesh(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)

    object {
        FunctionMesh(
            Fn,
            pMin.x, pMax.x,
            pMin.z, pMax.z,
            NoOfIntervalsX, NoOfIntervalsZ
        )
        clipped_by {
            box { pMin, pMax }
        }
    }

#end // macro ClippedFunctionMesh

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro AltFunctionMesh(Fn, MinX, MaxX, MinZ, MaxZ, NoOfIntervalsX, NoOfIntervalsZ)

    #local DX = (MaxX - MinX)/NoOfIntervalsX;
    #local DZ = (MaxZ - MinZ)/NoOfIntervalsZ;
    #local SizeX = NoOfIntervalsX + 1;
    #local SizeZ = NoOfIntervalsZ + 1;
    #local PP = array[SizeX][SizeZ];
    #local X = MinX;
    #for (CntX, 0, NoOfIntervalsX)
        #local Z = MinZ;
        #for (CntZ, 0, NoOfIntervalsZ)
            #local PP[CntX][CntZ] = <X, Fn(X, Z), Z>;
            #local Z = Z + DZ;
        #end // for
        #local X = X + DX;
    #end // for

    mesh {
        #local CntX0 = 0;
        #while (CntX0 < NoOfIntervalsX)
            #local CntX1 = CntX0 + 1;
            #local CntZ0 = 0;
            #while (CntZ0 < NoOfIntervalsZ)
                #local CntZ1 = CntZ0 + 1;
                triangle { PP[CntX0][CntZ0], PP[CntX1][CntZ1], PP[CntX1][CntZ0] }
                triangle { PP[CntX1][CntZ1], PP[CntX0][CntZ0], PP[CntX0][CntZ1] }
                #local CntZ0 = CntZ1;
            #end // for
            #local CntX0 = CntX1;
        #end // for
    }                        

#end // macro AltFunctionMesh


#macro ClampedAltFunctionMesh(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)

    AltFunctionMesh(
        ClampFunction(Fn, pMin.y, pMax.y),
        pMin.x, pMax.x,
        pMin.z, pMax.z,
        NoOfIntervalsX, NoOfIntervalsZ
    )

#end // macro ClampedAltFunctionMesh


#macro ClippedAltFunctionMesh(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)

    object {
        AltFunctionMesh(
            Fn,
            pMin.x, pMax.x,
            pMin.z, pMax.z,
            NoOfIntervalsX, NoOfIntervalsZ
        )
        clipped_by {
            box { pMin, pMax }
        }
    }

#end // macro ClippedAltFunctionMesh

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro FunctionMesh2(Fn, MinX, MaxX, MinZ, MaxZ, NoOfIntervalsX, NoOfIntervalsZ)

    #local H = 1e-3;
    #local DX = (MaxX - MinX)/NoOfIntervalsX;
    #local DZ = (MaxZ - MinZ)/NoOfIntervalsZ;
    #local HDX = H*DX;
    #local HDZ = H*DZ;
    #local TwoHDX = 2*HDX;
    #local TwoHDZ = 2*HDZ;
    #local SizeX = NoOfIntervalsX + 1;
    #local SizeZ = NoOfIntervalsZ + 1;
    #local NoOfVertices = SizeX*SizeZ;
    #local NoOfFaces = 2*NoOfIntervalsX*NoOfIntervalsZ;

    mesh2 {
        vertex_vectors {
            NoOfVertices,
            #local X = MinX;
            #for (CntX, 0, NoOfIntervalsX)
                #local Z = MinZ;
                #for (CntZ, 0, NoOfIntervalsZ)
                    <X, Fn(X, Z), Z>,
                    #local Z = Z + DZ;
                #end // for
                #local X = X + DX;
            #end // for
        }
        normal_vectors {
            NoOfVertices,
            #local X0 = MinX;
            #for (CntX, 0, NoOfIntervalsX)
                #local Xm = X0 - HDX;
                #local Xp = X0 + HDX;
                #local Z0 = MinZ;
                #for (CntZ, 0, NoOfIntervalsZ)
                    #local Zm = Z0 - HDZ;
                    #local Zp = Z0 + HDZ;
                    vnormalize(
                        <
                            (Fn(Xm, Z0) - Fn(Xp, Z0))/TwoHDX,
                            1,
                            (Fn(X0, Zm) - Fn(X0, Zp))/TwoHDZ
                        >
                    )
                    #local Z0 = Z0 + DZ;
                #end // for
                #local X0 = X0 + DX;
            #end // for
        }
        uv_vectors {
            NoOfVertices,
            #for (CntX, 0, NoOfIntervalsX)
                #for (CntZ, 0, NoOfIntervalsZ)
                    <CntX/NoOfIntervalsX, CntZ/NoOfIntervalsZ>,
                #end // for
            #end // for
        }
        face_indices {
            NoOfFaces,
            #local CntX0 = 0;
            #while (CntX0 < NoOfIntervalsX)
                #local CntX1 = CntX0 + 1;
                #local CntZ0 = 0;
                #while (CntZ0 < NoOfIntervalsZ)
                    #local CntZ1 = CntZ0 + 1;
                    <CntX0, CntX1, CntX1> + <CntZ0, CntZ1, CntZ0>*SizeX,
                    <CntX1, CntX0, CntX0> + <CntZ1, CntZ0, CntZ1>*SizeX
                    #local CntZ0 = CntZ1;
                #end // for
                #local CntX0 = CntX1;
            #end // for
        }
    }

#end // macro FunctionMesh2


#macro ClampedFunctionMesh2(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)

    FunctionMesh2(
        ClampFunction(Fn, pMin.y, pMax.y),
        pMin.x, pMax.x,
        pMin.z, pMax.z,
        NoOfIntervalsX, NoOfIntervalsZ
    )

#end // macro ClampedFunctionMesh2


#macro ClippedFunctionMesh2(Fn, pMin, pMax, NoOfIntervalsX, NoOfIntervalsZ)

    object {
        FunctionMesh2(
            Fn,
            pMin.x, pMax.x,
            pMin.z, pMax.z,
            NoOfIntervalsX, NoOfIntervalsZ
        )
        clipped_by {
            box { pMin, pMax }
        }
    }

#end // macro ClippedFunctionMesh2

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
