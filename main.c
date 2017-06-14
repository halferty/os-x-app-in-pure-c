//#include <stdio.h>
//
//int main() {
//    printf("Hello, World!\n");
//    return 0;
//}
//


#include <objc/runtime.h>
#include <objc/message.h>
#include <CoreGraphics/CoreGraphics.h>
//#include <AppKit/NSOpenGL.h>
//#include <Foundation/NSGeometry.h>
//#include <cocoa/cocoa.h>
//#import <Cocoa/Cocoa.h>
//#import <OpenGL/gl.h>
//#import <GLKit/GLKit.h>
#include <opengl/gl.h>

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

//NSOpenGLPFADoubleBuffer

#define sendNoArgs(i, f) objc_msgSend(i, sel_registerName(f))
#define send(i, f, ...) objc_msgSend(i, sel_registerName(f), __VA_ARGS__)
#define sendClass(c, f, ...)\
    objc_msgSend((id)objc_getClass(c), sel_registerName(f), ...)
#define sendClassNoArgs(c, f)\
    objc_msgSend((id)objc_getClass(c), sel_registerName(f))
#define alloc(c) sendClassNoArgs(c, "alloc")
#define init(i) sendNoArgs(i, "init")
#define addMethod(c, m, ...)\
    class_addMethod(c, sel_registerName(m), __VA_ARGS__)
#define allocateClassPair(s, n, e)\
    objc_allocateClassPair((Class)objc_getClass(s), n, e)

extern id NSApp;

Class AppDelegateClass;

typedef struct {
    Class isa;
    id window;
} AppDelegateStruct;

NSOpenGLPixelFormatAttribute attrs[] =
{
        NSOpenGLPFADoubleBuffer,
        0
};

bool didFinishLaunching(AppDelegateStruct *self, SEL _cmd, id notification) {
    self->window = alloc("NSWindow");
    CGRect windowRect = {0, 0, 640, 480}, viewRect = {0, 0, 320, 240};
    int windowStyle = NSTitledWindowMask | NSClosableWindowMask |
                      NSResizableWindowMask | NSMiniaturizableWindowMask;
    self->window = send(self->window,
                        "initWithContentRect:styleMask:backing:defer:",
                        windowRect, windowStyle, NSBackingStoreRetained, NO);
    id view = send(alloc("NSView"), "initWithFrame:", viewRect);
    send(self->window, "setContentView:", view);
    sendNoArgs(self->window, "becomeFirstResponder");
    id pixelFormat = send(alloc("NSOpenGLPixelFormat"), "initWithAttributes:", attrs);
//    NSRect viewRect = NSMakeRect(0.0, 0.0, 1920, 1080);
//    id viewRect = send("NSMa")
    //MyOpenGLView *fullScreenView = [[MyOpenGLView alloc] initWithFrame:viewRect pixelFormat: pixelFormat];
    id glView = send(alloc("NSOpenGLView"), "initWithFrame:pixelFormat:", viewRect, pixelFormat);
    printf("TEst\n");
    printf("%p\n", (void *)view);
    printf("%p\n", (void *)pixelFormat);
    printf("%p\n", (void *)glView);
    send(self->window, "makeKeyAndOrderFront:", self);
//    glClear(0.7490196078431373, 0.3568627450980392, 0.3568627450980392, 1.0);
//    GLclampf ii;
    glClearColor(0.7490196078431373f, 0.3568627450980392f, 0.3568627450980392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glFlush();

    int top = 0, left = 0, bottom = 100, right = 100;
//    GLbyte r = +191, g = 19, b = 19;

    glColor3f(0.7490196078431373, 0.3568627450980392, 0.3568627450980392);

    // Draw the top line
    glVertex2i(left, top);
    glVertex2i(right + 1, top);
    glVertex2i(right + 1, top + 1);
    glVertex2i(left, top + 1);

    // Draw the right line
    glVertex2i(right, top);
    glVertex2i(right + 1, top);
    glVertex2i(right + 1, bottom + 1);
    glVertex2i(right, bottom);

    // Draw the bottom line
    glVertex2i(left, bottom);
    glVertex2i(right + 1, bottom);
    glVertex2i(right + 1, bottom + 1);
    glVertex2i(left, bottom + 1);

    // Draw the left line
    glVertex2i(left, top);
    glVertex2i(left + 1, top);
    glVertex2i(left + 1, bottom + 1);
    glVertex2i(left, bottom);

    glEnd();
//    GL_COLOR_BUFFER_BIT
    return YES;
}

//[0.7490196078431373, 0.3568627450980392, 0.3568627450980392]
//[3] pry(main)>


int main(int argc, char **argv) {
    AppDelegateClass = allocateClassPair("NSObject", "AppDelegate", 0);
    addMethod(AppDelegateClass, "applicationDidFinishLaunching:",
              (IMP)didFinishLaunching, "i@:@");
    objc_registerClassPair(AppDelegateClass);
    sendClassNoArgs("NSApplication", "sharedApplication");
    id appDelegate = alloc("AppDelegate");
    appDelegate = init(appDelegate);
    send(NSApp, "setDelegate:", appDelegate);
    sendNoArgs(NSApp, "run");
    return EXIT_SUCCESS;
}
