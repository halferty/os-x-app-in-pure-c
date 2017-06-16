//
// Created by Ed Halferty on 6/14/17.
//

#ifndef UML_VIEWER_01_OBJC_HELPERS_H
#define UML_VIEWER_01_OBJC_HELPERS_H

#include <objc/NSObjCRuntime.h>


// Copied from <AppKit/NSWindow.h>
enum {
    NSBorderlessWindowMask = 0,
    NSTitledWindowMask = 1 << 0,
    NSClosableWindowMask = 1 << 1,
    NSMiniaturizableWindowMask = 1 << 2,
    NSResizableWindowMask	= 1 << 3,
    NSTexturedBackgroundWindowMask = 1 << 8,
    NSUnifiedTitleAndToolbarWindowMask = 1 << 12,
    NSFullScreenWindowMask = 1 << 14,
    NSFullSizeContentViewWindowMask = 1 << 15
};


// Copied from <AppKit/NSGraphics.h>
typedef CF_ENUM(unsigned long, NSBackingStoreType) {
    NSBackingStoreRetained = 0,
    NSBackingStoreNonretained = 1,
    NSBackingStoreBuffered = 2
};


// Copied from <AppKit/NSOpenGL.h>
enum {
    NSOpenGLPFADoubleBuffer = 5
};
typedef uint32_t NSOpenGLPixelFormatAttribute;


// Copied from <AppKit/NSRunningApplication.h>
//typedef long NSInteger // Not actually c
#define NS_ENUM(...) CF_ENUM(__VA_ARGS__)
typedef NS_ENUM(NSInteger, NSApplicationActivationPolicy) {
    NSApplicationActivationPolicyRegular,
    NSApplicationActivationPolicyAccessory,
    NSApplicationActivationPolicyProhibited
};


// Copied from <Foundation/NSObjCRuntime.h>
#define FOUNDATION_EXTERN extern
#define FOUNDATION_EXPORT  FOUNDATION_EXTERN
typedef id NSString;
//FOUNDATION_EXPORT SEL NSSelectorFromString(NSString *aSelectorName);
FOUNDATION_EXPORT SEL NSSelectorFromString(id aSelectorName);

// Common objc_msgSend call patterns
#define sendNoArgs(i, f) objc_msgSend(i, sel_registerName(f))
#define send(i, f, ...) objc_msgSend(i, sel_registerName(f), __VA_ARGS__)
#define sendClass(c, f, ...)\
    objc_msgSend((id)objc_getClass(c), sel_registerName(f), __VA_ARGS__)
#define sendClassNoArgs(c, f)\
    objc_msgSend((id)objc_getClass(c), sel_registerName(f))
#define alloc(c) sendClassNoArgs(c, "alloc")
#define init(i) sendNoArgs(i, "init")
#define initAlloc(c) init(alloc(c))
#define addMethod(c, m, ...)\
    class_addMethod(c, sel_registerName(m), __VA_ARGS__)
#define allocateClassPair(s, n, e)\
    objc_allocateClassPair((Class)objc_getClass(s), n, e)
#define allocateClassPairNoExtra(s, n)\
    objc_allocateClassPair((Class)objc_getClass(s), n, 0)
#define makeNSString(c)\
    send(alloc("NSString"), "initWithUTF8String:", c)
#define emptyNSString()\
    makeNSString("")
#define new(c)\
    sendClassNoArgs(c, "new")
#define autorelease(i)\
    sendNoArgs(i, "autorelease")
#define autoreleaseNew(c)\
    autorelease(new(c))
#define selector(s)\
    sendClass("NSSelectorFromString")

#endif //UML_VIEWER_01_OBJC_HELPERS_H
