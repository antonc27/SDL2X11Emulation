/* 
	Remember to compile try:
		1) gcc hi.c -o hi -lX11
		2) gcc hi.c -I /usr/include/X11 -L /usr/X11/lib -lX11
		3) gcc hi.c -I /where/ever -L /who/knows/where -l X11

	Brian Hammond 2/9/96.    Feel free to do with this as you will!
*/


/* include the X library headers */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

/* include some silly stuff */
#include <stdio.h>
#include <stdlib.h>

/* here are our X variables */
Display *dis;
int screen;
Window win;
GC gc;

/* here are our X routines declared! */
void init_x();
void close_x();
void redraw();

int main () {
	XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[255];		/* a char buffer for KeyPress Events */

	init_x();

    long i = 0;

	/* look for events forever... */
	while(1) {
        i++;
        if (i % 1000000 != 0) continue;

		/* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/
		//XNextEvent(dis, &event);
	
		//if (event.type==Expose && event.xexpose.count==0)
        {
		/* the window was exposed redraw it! */
			redraw();
		}
//		if (event.type==KeyPress&&
//		    XLookupString(&event.xkey,text,255,&key,0)==1)
        {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
			if (text[0]=='q') {
				close_x();
			}
			//printf("You pressed the %c key!\n",text[0]);

			int x = rand()%300, y = rand()%300;

			strcpy(text,"X is FUN!");
			XSetForeground(dis,gc, (rand()%255) << 8);
			XDrawString(dis,win,gc,x,y, text, strlen(text));
			//XDrawRectangle(dis, win, gc, x, y, 40, 20);

            //sleep(1);
		}
		// if (event.type==ButtonPress) {
		// /* tell where the mouse Button was Pressed */
		// 	int x=event.xbutton.x,
		// 	    y=event.xbutton.y;

		// 	strcpy(text,"X is FUN!");
		// 	XSetForeground(dis,gc,rand()%event.xbutton.x%255);
		// 	XDrawString(dis,win,gc,x,y, text, strlen(text));
		// }
	}

	return 0;
}

void init_x() {
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
    //win=XCreateSimpleWindow(dis,DefaultRootWindow(dis), 0, 0, 320, 240, 5, black, white);

//    XVisualInfo vinfo = {0};
//    if (!XMatchVisualInfo(dis, screen, 32, TrueColor, &vinfo)) {
//        /* TODO(djr): Logging */
//        fputs("X11: Unable to find supported visual info", stderr);
//        //return -1;
//        exit(-1);
//    }

   	win=XCreateWindow(dis,DefaultRootWindow(dis),0,0,
		320, 240, 5, CopyFromParent, CopyFromParent, CopyFromParent, 0, NULL);

	//XSetStandardProperties(dis,win,"Howdy","Hi",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
    gc=XCreateGC(dis, win, 0,0);
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);				
};

void redraw() {
	XClearWindow(dis, win);
};
