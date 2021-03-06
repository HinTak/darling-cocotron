/* Copyright (c) 2007 Christopher J. W. Lloyd

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#import <CoreGraphics/CGColorSpace.h>
#import <CoreGraphics/CGFunction.h>
#import <CoreGraphics/CGGeometry.h>
#import <CoreGraphics/CoreGraphicsExport.h>

typedef struct CF_BRIDGED_TYPE(id) O2Shading *CGShadingRef;

CF_IMPLICIT_BRIDGING_ENABLED

COREGRAPHICS_EXPORT CGShadingRef CGShadingRetain(CGShadingRef self);
COREGRAPHICS_EXPORT void CGShadingRelease(CGShadingRef self);

COREGRAPHICS_EXPORT CGShadingRef CGShadingCreateAxial(
        CGColorSpaceRef colorSpace, CGPoint startPoint, CGPoint endPoint,
        CGFunctionRef function, bool extendStart, bool extendEnd);
COREGRAPHICS_EXPORT CGShadingRef
CGShadingCreateRadial(CGColorSpaceRef colorSpace, CGPoint startPoint,
                      CGFloat startRadius, CGPoint endPoint, CGFloat endRadius,
                      CGFunctionRef function, bool extendStart, bool extendEnd);

CF_IMPLICIT_BRIDGING_DISABLED
