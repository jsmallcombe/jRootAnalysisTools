#include "j_X11paste.h"

#if defined __APPLE__
#elif defined __linux__

#include <X11/Xatom.h>
#include <X11/Xlib.h>

//// Used this source as a basis https://www.uninformativ.de/blog/postings/2017-04-02/0/POSTING-en.html Nov 2019

bool j_X11_debug=false;

int TestType(Display *dpy, Window &target_window,Atom targettype, bool clip=true);
int TestType(Display *dpy, Window &target_window,Atom targettype, bool clip){
        Atom sel= XInternAtom(dpy, "PRIMARY", False);
        if(clip) sel=XInternAtom(dpy, "CLIPBOARD", False);
        
        //Register an arbitrary property with our window
        Atom arbproperty = XInternAtom(dpy, "ARBPROPFILL", False);
        
        Atom targets= XInternAtom(dpy, "TARGETS", False);
        XConvertSelection(dpy, sel, targets, arbproperty, target_window, CurrentTime);
        //Ask whatever is on selection sel to be returned as list of possible target types
        
        for (;;){ // Wait for response
            XEvent ev;
            XNextEvent(dpy, &ev);
            if(ev.type==SelectionNotify){// Get a response
                    XSelectionEvent *sev = (XSelectionEvent*)&ev.xselection;
                    if (sev->property == None){
                        // Either no owner of selection sel or some other error
                        if(j_X11_debug)printf("Conversion could not be performed.\n");
                        return 1;
                    }else{       
                        //The list has been returned to our window, so do something with it
                        
                        int ret=3;
                        Atom type, *targets;
                        int di;
                        unsigned long i, nitems, dul;
                        unsigned char *prop_ret = NULL;

                        /* Read the first 1024 atoms from this list of atoms. should be Enough */
                        XGetWindowProperty(dpy, target_window, arbproperty, 0, 1024 * sizeof (Atom), False, XA_ATOM,&type, &di, &nitems, &dul, &prop_ret);

                        targets = (Atom *)prop_ret;
                        for (i = 0; i < nitems; i++){
                            if(j_X11_debug)cout<<XGetAtomName(dpy, targets[i])<<endl;
                            if(targets[i]==targettype){
                                ret=0;
                                if(j_X11_debug){cout<<" MATCH! "<<endl;}
                                else{break;}
                            }
                        }
                        XFree(prop_ret);
                        XDeleteProperty(dpy, target_window, arbproperty);
                        return ret;
                    }
            }
        }
        
        return 2;
}


int Test_uf8(Display *dpy, Window &target_window, bool clip=true);
int Test_uf8(Display *dpy, Window &target_window, bool clip){
    Atom utf8= XInternAtom(dpy, "UTF8_STRING", False);
    return TestType(dpy,target_window,utf8,clip);
}


int ReadCopyBufferAsText(stringstream &ss,Display *dpy, Window &target_window, bool clip=true);
int ReadCopyBufferAsText(stringstream &ss,Display *dpy, Window &target_window, bool clip){
    
    int status=Test_uf8(dpy,target_window,false);   
    if(status==0){
        Atom sel= XInternAtom(dpy, "PRIMARY", False);
        if(clip) sel=XInternAtom(dpy, "CLIPBOARD", False);
        Atom arbproperty = XInternAtom(dpy, "ARBPROPFILL", False);
        Atom utf8= XInternAtom(dpy, "UTF8_STRING", False);
        XConvertSelection(dpy, sel, utf8, arbproperty, target_window, CurrentTime);
        for (;;){ // Wait for response
            XEvent ev;XNextEvent(dpy, &ev);
            if(ev.type==SelectionNotify){
                    XSelectionEvent *sev = (XSelectionEvent*)&ev.xselection;
                    if (sev->property != None){       
                            Atom type;
                            int di;
                            unsigned long size, dul;
                            unsigned char *prop_ret = NULL;

                            // In this call we read 0, but total size is copied to "size"
                            XGetWindowProperty(dpy, target_window, arbproperty, 0,    0, False, utf8, &type, &di, &dul, &size, &prop_ret);
                            XFree(prop_ret);

                            if(j_X11_debug)printf("Property size: %lu\n", size);
                            Atom incr = XInternAtom(dpy, "INCR", False);
                            if (type == incr){
                                if(j_X11_debug)printf("Data too large and INCR mechanism not implemented\n");
                                return 11;
                            }

                            // In this call we read "size" amount of data, which we set to all
                            XGetWindowProperty(dpy, target_window, arbproperty, 0, size, False, utf8, &type, &di, &dul, &size, &prop_ret);
                            
                            ss<<prop_ret;
                            XFree(prop_ret);
                            XDeleteProperty(dpy, target_window, arbproperty);

                            return 0;
                    }
            }
        }
        return 12;
    }
    return 13;
}
    
int ReadX11CopyBufferAsText(stringstream &ss, bool clip){
    // "Open" a "window" object not one with actual graphics
    // in order to use the x-windows copy system, which actually just brokers between windows
    Display *dpy;
    dpy = XOpenDisplay(NULL);
    if (!dpy)
    {
        fprintf(stderr, "Could not open X display\n");
        return 1;
    }
    Window root = RootWindow(dpy, DefaultScreen(dpy));
    Window target_window = XCreateSimpleWindow(dpy, root, -10, -10, 1, 1, 0, 0, 0);
    
    return ReadCopyBufferAsText(ss,dpy,target_window,clip);
}

#else

int ReadX11CopyBufferAsText(stringstream &ss, bool clip){
    clip=false;
    ss<<"NA";
    return 42;
}

#endif
