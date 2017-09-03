//
// Created by Michal Ziobro on 14/09/2016.
//

#ifndef AUTOMATION_SCRIPTS_EVENTS_H
#define AUTOMATION_SCRIPTS_EVENTS_H

// functions send specific Apple events to the loginwindow process
// i.e. kAERestart, kAEShutDown, kAEReallyLogOut or kAESleep events.
// more: https://developer.apple.com/library/mac/qa/qa1134/_index.html
void system_shutdown(void);
void system_restart(void);
void system_sleep(void);
void system_logout(void);

#endif //AUTOMATION_SCRIPTS_EVENTS_H
