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

// Original - Christopher Lloyd <cjwl@objc.net>
#import <AppKit/NSFontMetric.h>
#import <AppKit/NSFontTypeface.h>

@implementation NSFontTypeface

- initWithName: (NSString *) name
        displayName: (NSString *) displayName
          traitName: (NSString *) traitName
             traits: (NSFontTraitMask) traits
{
    _name = [name copy];
    _displayName = [displayName copy];
    _traitName = [traitName copy];
    _traits = traits;
    _metrics = [NSMutableArray new];
    return self;
}

- initWithName: (NSString *) name
        traitName: (NSString *) traitName
           traits: (NSFontTraitMask) traits
{
    return [self initWithName: name
                  displayName: name
                    traitName: traitName
                       traits: traits];
}

- (void) dealloc {
    [_name release];
    [_displayName release];
    [_traitName release];
    [_metrics release];
    [super dealloc];
}

- (NSString *) name {
    return _name;
}

- (NSString *) displayName {
    return _displayName;
}

- (NSString *) traitName {
    return _traitName;
}

- (NSFontTraitMask) traits {
    return _traits;
}

- (void) addMetric: (NSFontMetric *) metric {
    [_metrics addObject: metric];
}

- (NSString *) description {
    return [NSString stringWithFormat: @"<%@ 0x%x %@ %@ %@>", [self class],
                                       self, _name, _displayName, _traitName];
}

@end
