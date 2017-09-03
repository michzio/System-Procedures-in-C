//
// Created by Michal Ziobro on 14/09/2016.
//

#include <MacTypes.h>
#include <Carbon/Carbon.h>
#include <stdio.h>
#include "system/events.h"

static OSStatus SendAppleEventToSystemProcess(AEEventID EventToSend)
{
    AEAddressDesc targetDesc;
    static const ProcessSerialNumber kPSNOfSystemProcess = { 0, kSystemProcess };
    AppleEvent eventReply = {typeNull, NULL};
    AppleEvent appleEventToSend = {typeNull, NULL};

    OSStatus error = noErr;

    error = AECreateDesc(typeProcessSerialNumber, &kPSNOfSystemProcess,
                         sizeof(kPSNOfSystemProcess), &targetDesc);

    if (error != noErr)
    {
        return(error);
    }

    error = AECreateAppleEvent(kCoreEventClass, EventToSend, &targetDesc,
                               kAutoGenerateReturnID, kAnyTransactionID, &appleEventToSend);

    AEDisposeDesc(&targetDesc);
    if (error != noErr)
    {
        return(error);
    }

    error = AESend(&appleEventToSend, &eventReply, kAENoReply,
                   kAENormalPriority, kAEDefaultTimeout, NULL, NULL);

    AEDisposeDesc(&appleEventToSend);
    if (error != noErr)
    {
        return(error);
    }

    AEDisposeDesc(&eventReply);

    return(error);
}

void system_shutdown(void) {
    //sending shutdown event to system
    OSStatus error = SendAppleEventToSystemProcess(kAEShutDown);
    if (error == noErr) {
        printf("%s: Computer is going to shutdown!\n", __func__);
    } else {
        fprintf(stderr, "%s: Computer wouldn't shutdown\n", __func__);
    }
}
void system_restart(void) {
    //sending restart event to system
    OSStatus error = SendAppleEventToSystemProcess(kAERestart);
    if (error == noErr) {
        printf("%s: Computer is going to restart!\n", __func__);
    } else {
        fprintf(stderr, "%s: Computer wouldn't restart\n", __func__);
    }
}
void system_sleep(void) {
    //sending sleep event to system
    OSStatus error = SendAppleEventToSystemProcess(kAESleep);
    if (error == noErr) {
        printf("%s: Computer is going to sleep!\n", __func__);
    } else {
        fprintf(stderr, "%s: Computer wouldn't sleep.\n", __func__);
    }
}
void system_logout(void) {
    //sending logout event to system
    OSStatus error = SendAppleEventToSystemProcess(kAEReallyLogOut);
    if (error == noErr) {
        printf("%s: Computer is going to logout!\n", __func__);
    } else {
        fprintf(stderr, "%s: Computer wouldn't logout.\n", __func__);
    }
}