#include <objc/runtime.h>
#include <objc/message.h>
#include <CoreGraphics/CoreGraphics.h>

#define Borderless               0
#define Titled                   1 << 0
#define Closable                 1 << 1
#define Miniaturizable           1 << 2
#define Resizable                1 << 3
#define TexturedBackground       1 << 8
#define UnifiedTitleAndToolbar   1 << 12
#define FullScreen               1 << 14
#define FullSizeContentView      1 << 15
#define NSBackingStoreRetained   0

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
#define C(z) CFSTR(z)

extern id NSApp;

Class AppDelegateClass;

typedef struct {
    Class isa;
    id window;
} AppDelegateStruct;

bool didFinishLaunching(AppDelegateStruct *self, SEL _cmd, id notification) {
    self->window = sendClassNoArgs("NSWindow", "alloc");
    CGRect windowRect = {0, 0, 640, 480}, viewRect = {0, 0, 320, 240};
    int windowStyle = Titled | Closable | Resizable | Miniaturizable;
    self->window = send(self->window,
                     "initWithContentRect:styleMask:backing:defer:",
                     windowRect, windowStyle, NSBackingStoreRetained, NO);
    id view = send(alloc("View"), "initWithFrame:", viewRect);
    send(self->window, "setContentView:", view);
    sendNoArgs(self->window, "becomeFirstResponder");
    send(self->window, "makeKeyAndOrderFront:", self);

    NSRunAlertPanel(C("Testing"), C("Hello, world!"), C("OK"), NULL, NULL);

    return YES;
}

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
