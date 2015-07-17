#include <SDL/SDL.h>

#include "window.h"

int
main(int argc, char *argv[]) {
    Window win = Window();
    
    win.run();
    
    return 0;
}
