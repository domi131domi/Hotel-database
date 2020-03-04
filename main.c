#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int main() {
    enum program status;
    const char COMMANDS[][MAX_COMMAND] = { {"ADDROOM"} , {"ADDCLIENT"}, {"EXIT"}, {"HELP"}, {"ADDRESERVATION"}, {"SHOWROOMS"}, {"SHOWCLIENTS"}, {"SHOWFREEROOMS"} };
    const int NROFCOMMANDS = sizeof( COMMANDS ) / sizeof( COMMANDS[0] );
    char command[MAX_COMMAND];
    struct Room* headR = NULL;
    struct Person* headP = NULL;

    start( &status );
    while( status ) {
    if( loadCommand( command, COMMANDS, NROFCOMMANDS ) )
    redirect( command, &status, &headR, &headP );
    }

    close( headR, headP );
    return 0;
}

