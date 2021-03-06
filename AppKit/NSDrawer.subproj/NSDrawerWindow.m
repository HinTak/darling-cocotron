/* Copyright (c) 2006-2007 Christopher J. W. Lloyd

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

// Original - David Young <daver@geeks.org>
#import <AppKit/AppKitExport.h>
#import <AppKit/NSDrawer.h>
#import <AppKit/NSDrawerWindow.h>
#import <CoreGraphics/CGWindow.h>

@implementation NSDrawerWindow

- (NSDrawer *) drawer {
    return _drawer;
}

- (void) setDrawer: (NSDrawer *) drawer {
    _drawer = drawer;
}

- (BOOL) canBecomeMainWindow {
    return NO;
}

- (BOOL) canBecomeKeyWindow {
    return YES;
}

- (void) platformWindowActivated: (CGWindow *) window
                 displayIfNeeded: (BOOL) displayIfNeeded
{
    [_drawer drawerWindowDidActivate: self];

    [super platformWindowActivated: window displayIfNeeded: displayIfNeeded];
}

// constrain resize size.
- (NSSize) platformWindow: (CGWindow *) window
        frameSizeWillChange: (NSSize) size
{
    size = [super platformWindow: window frameSizeWillChange: size];

    return [_drawer drawerWindow: self
                   constrainSize: size
                            edge: [_drawer edge]];
}

// if new size < threshold, close drawer....
- (void) platformWindowDidEndSizing: (CGWindow *) window {
    [super platformWindowDidEndSizing: window];

    [_drawer drawerWindowDidResize: self];
}

@end
