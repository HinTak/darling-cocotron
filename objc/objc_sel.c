/* Copyright (c) 2006-2007 Christopher J. W. Lloyd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */
#import "objc_sel.h"
#import "ObjCHashTable.h"
#import "objc_cache.h"
#import "objc_class.h"
#import "objc_log.h"
#import "objc_malloc.h"

#define INITIAL_SELECTOR_TABLE_SIZE 4096 // Big System has about 3700 selectors

static OBJCHashTable *nameToNumber = NULL;
static OBJCHashTable *nameToSelector = NULL;

const char *sel_registerNameNoCopy(const char *name) {
    const char *result;

    if(nameToNumber == NULL)
        nameToNumber = OBJCCreateHashTable(INITIAL_SELECTOR_TABLE_SIZE);

    result = OBJCHashValueForKey(nameToNumber, name);

    if(result == NULL) {
        result = OBJCHashInsertValueForKey(nameToNumber, name, name);
    }

    return result;
}

SEL sel_registerSelectorNoCopyName(const char *name) {
#ifndef OBJC_TYPED_SELECTORS
    return sel_registerNameNoCopy(name);
#else
    SEL result;

    if(nameToSelector == NULL)
        nameToSelector = OBJCCreateHashTable(INITIAL_SELECTOR_TABLE_SIZE);

    result = (SEL)OBJCHashValueForKey(nameToSelector, name);

    if(result == NULL) {
        objc_selector_internal *ughp;

        ughp = objc_malloc(sizeof(objc_selector_internal));
        ughp->name = sel_registerNameNoCopy(name);

        result = (SEL)OBJCHashInsertValueForKey(nameToSelector, (char *)name, ughp);
    }

    return result;
#endif
}

const char *sel_getName(SEL selector) {
    if(selector == NULL)
        return NULL;

    if(nameToNumber == NULL)
        return NULL;

    selector = sel_getSelector(selector);

    return (const char *)OBJCHashValueForKey(nameToNumber, selector);
}

SEL sel_getUid(const char *selectorName) {
    SEL result;

#ifndef OBJC_TYPED_SELECTORS
    if(nameToNumber == NULL)
        result = NULL;
    else
        result = (SEL)OBJCHashValueForKey(nameToNumber, selectorName);

    if(result == NULL) {
        char *copy = objc_malloc(sizeof(char) * (strlen(selectorName) + 1));

        strcpy(copy, selectorName);
        result = (SEL)sel_registerNameNoCopy(copy);
    }
#else
    if(nameToSelector == NULL)
        result = NULL;
    else
        result = (SEL)OBJCHashValueForKey(nameToSelector, selectorName);

    if(result == NULL) {
        char *copy = objc_malloc(sizeof(char) * (strlen(selectorName) + 1));

        strcpy(copy, selectorName);

        result = sel_registerSelectorNoCopyName(copy);
    }
#endif

    return result;
}

BOOL sel_isEqual(SEL selector, SEL other) {
    selector = sel_getSelector(selector);
    other = sel_getSelector(other);

    return (selector == other) ? YES : NO;
}

SEL sel_registerName(const char *cString) {
    return sel_getUid(cString);
}

BOOL sel_isMapped(SEL selector) {
    return (sel_getName(selector) != NULL) ? YES : NO;
}
