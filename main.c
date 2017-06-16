#include <objc/runtime.h>
#include <objc/message.h>
#include <CoreGraphics/CoreGraphics.h>
#include <opengl/gl.h>
#include "objc_helpers.h"

//#include <AppKit/NSOpenGL.h>
//#include <Foundation/NSGeometry.h>
//#include <cocoa/cocoa.h>
//#import <Cocoa/Cocoa.h>
//#import <OpenGL/gl.h>
//#import <GLKit/GLKit.h>
//#include <AppKit/NSRunningApplication.h>



extern id NSApp;

typedef struct {
    Class isa;
    id window;
} AppDelegateStruct;

NSOpenGLPixelFormatAttribute attrs[] = { NSOpenGLPFADoubleBuffer, 0 };

void prepareOpenGL() {
    glClearColor(0.7490196078431373f, 0.3568627450980392f, 0.3568627450980392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glSwapAPPLE();
}

void reshape() {
}

void drawRect(CGRect rect) {
}

bool didFinishLaunching(AppDelegateStruct *self, SEL _cmd, id notification) {
    self->window = alloc("NSWindow");
    CGRect windowRect = {0, 0, 640, 480};
    CGRect viewRect = {0, 0, 320, 240};
    int windowStyle = NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask | NSMiniaturizableWindowMask;
    self->window = send(self->window, "initWithContentRect:styleMask:backing:defer:", windowRect, windowStyle, NSBackingStoreRetained, NO);
    const char *viewClassName = "ViewClass";
    Class ViewClass = allocateClassPairNoExtra("NSOpenGLView", viewClassName);
    addMethod(ViewClass, "prepareOpenGL", (IMP)prepareOpenGL, "v@");
    addMethod(ViewClass, "reshape", (IMP)reshape, "v@");
    addMethod(ViewClass, "drawRect:", (IMP)drawRect, "v@:@");
    objc_registerClassPair(ViewClass);
    id pixelFormat = send(alloc("NSOpenGLPixelFormat"), "initWithAttributes:", attrs);
    id context = send(alloc("NSOpenGLContext"), "initWithFormat:shareContext:", pixelFormat, (void *)0);
    sendNoArgs(context, "makeCurrentContext");
    id view = initAlloc(viewClassName);
    send(view, "setPixelFormat:", pixelFormat);
    send(view, "setOpenGLContext:", context);
    send(self->window, "setContentView:", view);
    send(self->window, "makeKeyAndOrderFront:", NSApp);

//    id mainMenu = initAlloc("NSMenu");
//
////    newItem = [[NSMenuItem allocWithZone:[NSMenu menuZone]] initWithTitle:@"Flashy" action:NULL keyEquivalent:@""];
//    id newItem = send(sendClass("NSMenuItem", "allocWithZone:", sendClassNoArgs("NSMenu", "menuZone")), "initWithTitle:action:keyEquivalent:", makeNSString("Asdf"), NULL, emptyNSString());
//
////    newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"Flashy"];
//    id newMenu = send(sendClass("NSMenu", "allocWithZone:", sendClassNoArgs("NSMenu", "menuZone")), "initWithTitle:", makeNSString("Asdf"));
//
////    [newItem setSubmenu:newMenu];
//    send(newItem, "setSubmenu:", newMenu);
//
////    [newMenu release];
//    sendNoArgs(newMenu, "release");
//
////    [[NSApp mainMenu] addItem:newItem];
//    send(mainMenu, "addItem:", newItem);
//
////    [newItem release];
//    sendNoArgs(newItem, "release");
//
//    send(NSApp, "setMainMenu:", mainMenu);

    //[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    send(NSApp, "setActivationPolicy:", NSApplicationActivationPolicyRegular);

    //id menubar = [[NSMenu new] autorelease];
    id menuBar = sendNoArgs(sendClassNoArgs("NSMenu", "new"), "autorelease");

    //id appMenuItem = [[NSMenuItem new] autorelease];
    id appMenuItem = sendNoArgs(sendClassNoArgs("NSMenuItem", "new"), "autorelease");

    //[menubar addItem:appMenuItem];
    send(menuBar, "addItem:", appMenuItem);

    //[NSApp setMainMenu:menubar];
    send(NSApp, "setMainMenu:", menuBar);

    return YES;
}

bool shouldTerminateAfterLastWindowClosed(AppDelegateStruct *self, SEL _cmd, id notification) {
    return YES;
}

int main(int argc, char **argv) {
    const char *appDelegateClassName = "AppDelegate";
    Class AppDelegateClass = allocateClassPairNoExtra("NSObject", appDelegateClassName);
    addMethod(AppDelegateClass, "applicationDidFinishLaunching:", (IMP)didFinishLaunching, "i@:@");
    addMethod(AppDelegateClass, "applicationShouldTerminateAfterLastWindowClosed:", (IMP)shouldTerminateAfterLastWindowClosed, "i@:@");
    objc_registerClassPair(AppDelegateClass);
    sendClassNoArgs("NSApplication", "sharedApplication");
    id appDelegate = initAlloc(appDelegateClassName);
    send(NSApp, "setDelegate:", appDelegate);
    sendNoArgs(NSApp, "run");
    return EXIT_SUCCESS;
}
