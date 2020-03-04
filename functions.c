#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

struct Reservation* addReservation( int from, int to, int id_person, struct Reservation* head ) {
    struct Reservation* newReservation = malloc( sizeof( struct Reservation ) );
    if( newReservation == NULL ) {
        puts("Nie udalo sie dodac rezerwacji. Sprobuj ponownie");
        return head;
    }
    newReservation->from = from;
    newReservation->to = to;
    newReservation->id_person = id_person;
    newReservation->next = head;
    return newReservation;
}

void deleteResList( struct Reservation* head ) {
    struct Reservation* temporary;
    while( head != NULL ) {
        temporary = head;
        head = head->next;
        free( temporary );
        temporary = NULL;
    }
}

struct Reservation* elementRes( struct Reservation* head, int nr ) {
    struct Reservation* temporary = head;
    if( nr < 0 )
        return NULL;
    while( nr > 0 ) {
        if( temporary->next == NULL ) {
                return NULL;
            }
        temporary = temporary->next;
        --nr;
    }
    return temporary;
}

int nrOfElementsRes( struct Reservation* head ) {
    int i = 0;
    while( head != NULL ) {
        i++;
        head = head->next;
    }
    return i;
}

void swapR( struct Reservation* first, struct Reservation* second ) {
    struct Reservation temporary;
    temporary.from = first->from;
    temporary.to = first->to;
    temporary.id_person = first->id_person;
    first->from = second->from;
    first->to = second->to;
    first->id_person = second->id_person;
    second->from = temporary.from;
    second->to = temporary.to;
    second->id_person = temporary.id_person;
}

void sortListRes( struct Reservation* head ) {
    for(int i = 0; i < nrOfElementsRes( head ) ; i++) {
        int place = i;
        for(int e = i; e < nrOfElementsRes( head ); e++) {
            if( elementRes(head, place )->to < elementRes(head, e )->to ) {
                place = e;
            }
        }
        swapR( elementRes( head, i ), elementRes( head, place ) );
    }
}

struct Room* addRoom( int number, struct Room* head ) {
    struct Room* newRoom = malloc( sizeof( struct Room ) );
    if( newRoom == NULL ) {
        puts("Nie udalo sie dodac pokoju. Sprobuj ponownie.");
        return head;
    }
    newRoom->number = number;
    newRoom->next = head;
    newRoom->head = NULL;
    return newRoom;
}

void deleteRoomList( struct Room* head ) {
    struct Room* temporary;
    while( head != NULL ) {
        temporary = head;
        head = head->next;
        deleteResList( temporary->head );
        free( temporary );
        temporary = NULL;
    }
}

struct Room* elementRoom( struct Room* head, int nr ) {
    if( nr < 0 )
        return NULL;
    while( nr > 0 ) {
        if( head->next == NULL )
            return NULL;
        head = head->next;
        --nr;
    }
    return head;
}

int nrOfElementsRoom( struct Room* head ) {
    int i = 0;
    while( head != NULL ) {
        i++;
        head = head->next;
    }
    return i;
}

int nrOfElementsPer( struct Person* head ) {
    int i = 0;
    while( head != NULL ) {
        i++;
        head = head->next;
    }
    return i;
}

void deletePersonList( struct Person* head ) {
    struct Person* temporary;
    while( head != NULL ) {
        temporary = head;
        head = head->next;
        free( temporary );
        temporary = NULL;
    }
}

struct Person* addClient( char* name, char* sname, struct Person* head ) {
    struct Person* newPerson = malloc( sizeof( struct Person ) );
    if( newPerson == NULL ) {
        puts("Nie udalo sie dodac klienta. Sprobuj ponownie.");
        return head;
    }
    strcpy( newPerson->name, name );
    strcpy( newPerson->sname, sname );
    if( head == NULL )
        newPerson->id = 0;
    else
    newPerson->id = head->id + 1;
    newPerson->next = head;
    return newPerson;
}

void clearBuffor( void ) {
    char c ;
    do
        c = getchar ();
    while ( c != '\n' && c != EOF );
}

int loadCommand( char* command, const char commands[][MAX_COMMAND], const int nrOfCommands ) {
    if( scanf( "%s", command ) != 1 ) {
        clearBuffor();
        return 0;
    }
    clearBuffor();
    for( int i = 0; i < nrOfCommands; i++ ) {
            if( strcmp( command, commands[i] ) == 0 ) {
                return 1;
            }
    }
    printf("Nie rozpoznano komendy: %s ! Wpisz komende HELP, aby uzyskac pomoc.\n\n",command);
    return 0;
}

int checkifExistR( int nrOfRoom, struct Room* head ) {
        struct Room* temporary = head;
    for( int i = 0; i < nrOfElementsRoom( head ); i++ ) {
        if( nrOfRoom ==  temporary->number )
            return 1;
        temporary = temporary->next;
    }
    return 0;
}

int checkifExistP( char* name, char* sname, struct Person* head ) {
        struct Person* temporary = head;
    for( int i = 0; i < nrOfElementsPer( head ); i++ ) {
        if( strcmp( name, temporary->name ) == 0 && strcmp( sname, temporary->sname ) == 0 )
            return 1;
        temporary = temporary->next;
    }
    return 0;
}

void close( struct Room* headR, struct Person* headP ) {
    deleteRoomList( headR );
    deletePersonList( headP );
    return;
}

int syntaxRoom( int *nrOfRoom, struct Room* heap ) {
        if( scanf( "%d" , nrOfRoom ) != 1 || *nrOfRoom <= 0 ) {
            puts("Zla skladnia polecenia ADDROOM ! Poprawna skladnia: \nADDROOM \nnrPokoju \n");
            clearBuffor();
            return 0;
        }
        if( checkifExistR( *nrOfRoom, heap ) ) {
            printf("Nie mozna utworzyc pokoju. Pokoj o numerze %d juz istnieje.\n\n",*nrOfRoom);
            return 0;
        }
        return 1;
}

int syntaxPerson( char* name, char* sname, struct Person* head ) {
    if( scanf( "%s" , name ) != 1 || scanf( "%s", sname ) != 1 ) {
            puts("Zla skladnia polecenia ADDCLIENT ! Poprawna skladnia: \nADDCLIENT \nimie nazwisko \n");
            clearBuffor();
            return 0;
    }
    clearBuffor();
    if( checkifExistP( name, sname, head ) ) {
            printf("Nie mozna utworzyc klienta o imieniu i nazwisku: %s %s. Podany klient juz istnieje.\n\n",name,sname);
            return 0;
    }
    return 1;
}

int getClientId( char* name, char* sname, struct Person* head ) {
    while( head != NULL ) {
        if( strcmp( name, head->name ) == 0 && strcmp( sname, head->sname ) == 0 )
            return head->id;
        head = head->next;
    }
    return -1;
}

int checkifExistRes( int nrOfRoom, int from, int to, struct Room* headR, struct Person* headP ) {
    for( int i = 0; i < nrOfElementsRoom( headR ); i++ ) {
        if( elementRoom( headR, i )->number == nrOfRoom ) {
            for( int e = 0; e < nrOfElementsRes( elementRoom( headR, i )->head ); e++ ) {
                if( datesColiding( elementRes( elementRoom( headR, i )->head, e )->from,
                    elementRes( elementRoom( headR, i )->head, e )->to,
                     from, to ) )
                    return 1;
            }
        }
    }
    return 0;
}

int datesColiding( int from, int to, int from2, int to2 ) {
    if( !( from < from2 && to <= from2 ) && !( from >= to2 && to > to2 ) )
        return 1;
    return 0;
}

int syntaxReservation( char* name, char* sname, int* nrOfRoom, int* from, int* to, struct Room* headR, struct Person* headP ) {
    int year1;
    int year2;
    int month1;
    int month2;
    int day1;
    int day2;
    if( scanf( "%d %d %d", &year1, &month1, &day1 ) != 3 || scanf( "%d %d %d", &year2, &month2, &day2 ) != 3 || year1 < 0 || month1 < 0 || day1 < 0 ||
        year2 < 0 || month2 < 0 || day2 < 0 || month1 > 12 || month2 > 12 || day1 > 31 || day2 > 31 ) {
        puts("Zla skladnia polecenia ADDRESERVATION ! Poprawna skladnia: \nADDRESERVATION\nRok Miesiac Dzien (rozpoczecie)\nRok Miesiac Dzien (zakonczenie)\nnrPokoju Imie Nazwisko\n");
        clearBuffor();
        return 0;
    }
    *from = year1 * 10000 + month1 * 100 + day1;
    *to = year2 * 10000 + month2 * 100 + day2;
    if( scanf( "%d %s %s", nrOfRoom, name, sname ) != 3 || *nrOfRoom <= 0 || *from > *to ) {
        puts("Zla skladnia polecenia ADDRESERVATION ! Poprawna skladnia: \nADDRESERVATION\nRok Miesiac Dzien (rozpoczecie)\nRok Miesiac Dzien (zakonczenie)\nnrPokoju Imie Nazwisko\n");
            clearBuffor();
            return 0;
    }
    clearBuffor();
    if( !checkifExistP( name, sname, headP ) || !checkifExistR( *nrOfRoom, headR ) ) {
        puts("Podana osoba lub numer pokoju nie isnieja! Sprawdz poprawnosc danych badz dodaj osobe lub pokoj.\n");
        return 0;
    }
    if( checkifExistRes( *nrOfRoom, *from, *to, headR, headP  ) ) {
        puts("Podana rezerwacja koliduje z juz isntiejaca. Zmien date lub pokoj.\n");
        return 0;
    }
    return 1;
}

struct Person* elementPerson( struct Person* head, int nr ) {
    if( nr < 0 )
        return NULL;
    while( nr > 0 ) {
        if( head->next == NULL )
            return NULL;
        head = head->next;
        --nr;
    }
    return head;
}

int syntaxShowFree( int *from, int *to, struct Room* head ) {
    int year1;
    int year2;
    int month1;
    int month2;
    int day1;
    int day2;
    if( scanf( "%d %d %d" ,&year1 , &month1, &day1 ) != 3 || scanf( "%d %d %d", &year2, &month2, &day2 ) != 3 || year1 < 0 || month1 < 0 || day1 < 0 ||
        year2 < 0 || month2 < 0 || day2 < 0 || month1 > 12 || month2 > 12 || day1 > 31 || day2 > 31 ) {
        puts("Zla skladnia polecenia SHOWFREEROOMS ! Poprawna skladnia: \nSHOWFREEROOMS\nRok Miesiac Dzien\nRok Miesiac Dzien\n");
        clearBuffor();
        return 0;
    }
    *from = year1 * 10000 + month1 * 100 + day1;
    *to = year2 * 10000 + month2 * 100 + day2;
    if( *from > *to ) {
        puts("Data rozpoczynajaca rezerwacje jest pozniejsza niz konczaca. Sprawdz wprowadzane dane.\n");
        return 0;
    }
    return 1;
}

void help( char* type ) {
    if( strcmp( "COMMANDS", type ) == 0 )
        puts("\nADDROOM - dodaj pokoj\nADDCLIENT - dodaj klienta\nADDRESERVATION - dodaj rezerwacje\nSHOWROOMS - pokaz istniejace juz pokoje\nSHOWCLIENTS - pokaz istniejacych juz klientow\nSHOWFREEROOMS - pokaz wolne pokoje w danym terminie\nEXIT - wyjdz z programu\n");
    else if( strcmp( "ADDROOM", type ) == 0 )
        puts("\nADDROOM\nNR Pokoju\n");
    else if( strcmp( "ADDCLIENT", type ) == 0 )
        puts("\nADDCLIENT\nImie Nazwisko\n");
    else if( strcmp( "ADDRESERVATION", type ) == 0 )
        puts("\nADDRESERVATION\nRok Miesiac Dzien\nRok Miesiac Dzien\nNR Pokoju Imie Nazwisko\n");
    else if( strcmp( "SHOWFREEROOMS", type ) == 0 )
        puts("\nSHOWFREEROOMS\nRok Dzien Miesiac\nRok Dzien Miesiac\n");
    else
        puts("Nie rozpoznano polecenia lub polecenie to nie posiada skladni\n");
}

void redirect( char* command, enum program *status, struct Room** headR, struct Person** headP ) {
    if( strcmp( command, "ADDROOM" ) == 0 ) {
        rAddRoom( headR );
   } else if( strcmp( command, "ADDCLIENT" ) == 0 ) {
        rAddClient( headP );
   } else if( strcmp( command, "EXIT" ) == 0 ) {
        *status = OFF;
   }else if( strcmp( command, "ADDRESERVATION" ) == 0 ) {
        rAddReservation( headP, headR );
   } else if( strcmp( command, "HELP" ) == 0 ) {
        rHelp();
   } else if( strcmp( command, "SHOWROOMS" ) == 0 ) {
       rShowRooms( headR );
   }else if( strcmp( command, "SHOWCLIENTS" ) == 0 ) {
        rShowClients( headP );
   }else if( strcmp( command, "SHOWFREEROOMS" ) == 0 ) {
        rShowFreeRooms( headR );
   }
   return;
}

void rAddRoom( struct Room** headR ) {
    int nrOfRoom;
        if( !syntaxRoom( &nrOfRoom, *headR ) )
            return;
        *headR = addRoom( nrOfRoom, *headR );
        puts("Dodawnie pokoju zakonczono pomyslnie\n");
        return;
}

void rAddClient( struct Person** headP ) {
    char name[MAX_NAME];
    char sname[MAX_SNAME];
    if( !syntaxPerson( name, sname, *headP ) )
        return;
    *headP = addClient( name, sname, *headP );
    puts("Dodawanie klienta zakonczono pomyslnie.\n");
    return;
}

void rAddReservation( struct Person** headP, struct Room** headR ) {
    char name[MAX_NAME];
    char sname[MAX_SNAME];
    int nrOfRoom;
    int from;
    int to;
    if( !syntaxReservation( name, sname, &nrOfRoom, &from, &to, *headR, *headP ) )
        return;
    for( int i = 0; i < nrOfElementsRoom( *headR ); i++ ) {
    if( elementRoom( *headR, i )->number == nrOfRoom ) {
        elementRoom( *headR, i)->head = addReservation(from, to, getClientId( name, sname, *headP ) , elementRoom( *headR, i )->head );
        sortListRes( elementRoom( *headR, i )->head );
        puts("Dodawanie rezerwacji zakonczono pomyslnie.\n");
        return;
        }
    }
}

void rHelp() {
    char type[MAX_COMMAND];
    puts("Wpisz COMMANDS, aby uzyskac liste dostepnych komend lub podaj komende, aby uzyskac jej skladnie\n");
    if( scanf( "%s", type ) == 1 )
    help(type);
    else
    puts("Nie rozpoznano polecenia\n");
    return;
}

void rShowRooms( struct Room** headR ) {
    if( nrOfElementsRoom( *headR ) == 0 ) {
        puts("Nie dodano zadnego pokoju.\n\n");
        return;
    }
    for( int i = 0; i < nrOfElementsRoom( *headR ); i++ ) {
        printf( "Pokoj nr%d\n\n", elementRoom( *headR ,i )->number );
    }
    return;
}

void rShowClients( struct Person** headP ) {
    if( nrOfElementsPer( *headP ) == 0 ) {
        puts("Nie dodano zadnego klienta.\n");
    }
    for( int i = 0; i < nrOfElementsPer( *headP ); i++ ) {
        printf( "%s %s ID Klienta %d\n\n", elementPerson( *headP, i )->name, elementPerson( *headP, i )->sname , elementPerson( *headP, i )->id );
    }
    return;
}

void rShowFreeRooms( struct Room** headR ) {
    int from;
    int to;
    if( !syntaxShowFree( &from, &to, *headR ) )
        return;
    puts("Wolne pokoje w tym terminie:");
    int guard;
    int guard2 = 0;
    for( int i = 0; i < nrOfElementsRoom( *headR ); i++ ) {
        guard = 0;
        for( int e = 0; e < nrOfElementsRes( elementRoom( *headR, i )->head ); e++ ){
            if( datesColiding( elementRes( elementRoom( *headR, i )->head , e )->from, elementRes( elementRoom( *headR, i )->head , e )->to, from, to  ))
            guard = 1;
        }
        if( guard == 0 ) {
            printf( "Pokoj nr%d\n", elementRoom( *headR, i )->number );
            guard2 = 1;
        }
    }
    if( guard2 == 0 ) {
        puts("Nia ma wolnych pokoi w tym terminie.");
    }
        puts("\n");
   return;
}

void start( enum program* status ) {
    *status = ON;
    puts("Baza danych hotelu wlaczona pomyslnie. Wpisz HELP jesli chcesz uzyskac pomoc.");
}
