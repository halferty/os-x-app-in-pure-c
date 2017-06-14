#include <objc/runtime.h>
#include <objc/message.h>
#include <CoreGraphics/CoreGraphics.h>
#include <opengl/gl.h>
#include "objc_helpers.h"

extern id NSApp;

typedef struct {
    Class isa;
    id window;
} AppDelegateStruct;

NSOpenGLPixelFormatAttribute attrs[] = { NSOpenGLPFADoubleBuffer, 0 };

void prepareOpenGL() {
    printf("prepareOpenGL called\n");
    glClearColor(0.7490196078431373f, 0.3568627450980392f, 0.3568627450980392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glSwapAPPLE();
}

void reshape() {
    printf("reshape called\n");
    glClearColor(0.7490196078431373f, 0.3568627450980392f, 0.3568627450980392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glSwapAPPLE();
}

void drawRect(CGRect rect) {
    printf("drawRect called\n");
    glClearColor(0.7490196078431373f, 0.3568627450980392f, 0.3568627450980392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glSwapAPPLE();
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
    printf("%p\n", (void *)ViewClass);
    objc_registerClassPair(ViewClass);
    id pixelFormat = send(alloc("NSOpenGLPixelFormat"), "initWithAttributes:", attrs);
    id context = send(alloc("NSOpenGLContext"), "initWithFormat:shareContext:", pixelFormat, (void *)0);
    sendNoArgs(context, "makeCurrentContext");
    id view = initAlloc(viewClassName);
    send(view, "setPixelFormat:", pixelFormat);
    send(view, "setOpenGLContext:", context);
    send(self->window, "setContentView:", view);
    send(self->window, "makeKeyAndOrderFront:", self);
    return YES;
}

int main(int argc, char **argv) {
    const char *appDelegateClassName = "AppDelegate";
    Class AppDelegateClass = allocateClassPairNoExtra("NSObject", appDelegateClassName);
    addMethod(AppDelegateClass, "applicationDidFinishLaunching:", (IMP)didFinishLaunching, "i@:@");
    objc_registerClassPair(AppDelegateClass);
    sendClassNoArgs("NSApplication", "sharedApplication");
    id appDelegate = initAlloc(appDelegateClassName);
    send(NSApp, "setDelegate:", appDelegate);
    sendNoArgs(NSApp, "run");
    return EXIT_SUCCESS;
}
