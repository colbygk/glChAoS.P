//------------------------------------------------------------------------------
//  Copyright (c) 2018-2019 Michele Morrone
//  All rights reserved.
//
//  https://michelemorrone.eu - https://BrutPitt.com
//
//  twitter: https://twitter.com/BrutPitt - github: https://github.com/BrutPitt
//
//  mailto:brutpitt@gmail.com - mailto:me@michelemorrone.eu
//  
//  This software is distributed under the terms of the BSD 2-Clause license
//------------------------------------------------------------------------------
#line 14    //#version dynamically inserted

void main()
{

    vec2 ptCoord = vec2(gl_PointCoord.x,1.0-gl_PointCoord.y); //upsideDown: revert point default
    outColor = mainFunc(ptCoord);

}
