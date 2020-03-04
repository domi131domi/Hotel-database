#ifndef FUNCTIONS_PROJ3
#define FUNCTIONS_PROJ3

#define MAX_NAME 15
#define MAX_SNAME 20
#define MAX_COMMAND 20

enum program { ON = 1, OFF = 0 };

struct Person {
    int id;
    char name[MAX_NAME];
    char sname[MAX_SNAME];
    struct Person* next;
};

struct Reservation {
    int from;
    int to;
    int id_person;
    struct Reservation* next;
};

struct Room {
    int number;
    struct Reservation* head;
    struct Room* next;
};

//funkcja typy add dodaje element do listy
//zwraca wskaznik na aktualna glowe listy
struct Reservation* addReservation( int from, int to, int id_person, struct Reservation* head );
struct Person* addClient( char* name, char* sname, struct Person* head );
struct Room* addRoom( int number, struct Room* head );


//funkcje typu nrOfElements zwracaja ilosc elemntow w swojej liscie
int nrOfElementsRes( struct Reservation* head );
int nrOfElementsRoom( struct Room* head );
int nrOfElementsPer( struct Person* head );


//funkcja zamienia wartosci dwoch elementow z listy rezerwacji
void swapR( struct Reservation* first, struct Reservation* second );


//funkcje typu sort sortuja liste (najwiekszy element to glowa)
void sortListRes( struct Reservation* head );
void sortListRoom( struct Reservation* head );

//funkcja typu delete usuwa dana liste
void deleteRoomList( struct Room* head );
void deletePersonList( struct Person* head );
void deleteResList( struct Reservation* head );

//funkcja zwraca wskaznik do pokoju/osoby/rezerwacji oddalonego o "nr" od glowy listy
//w przypadku gdy: nr = 0 zwraca glowe; nr < 0 lub nr > ilosci elemntow w liscie to zwraca NULL
struct Room* elementRoom( struct Room* head, int nr );
struct Person* elementPerson( struct Person* head, int nr );
struct Reservation* elementRes( struct Reservation* head, int nr );


//funkcja czysci buffor do pierwszego bialego znaku
void clearBuffor( void );

//funkcja pobiera tekst z klawiatury do zmiennej command i sprawdza czy spelnia zalozenia komendy
//zwraca 1 gdy zakonczy proces pomyslnie, w przeciwnym przypadku 0
int loadCommand( char* command, const char commands[][MAX_COMMAND], const int nrOfCommands );


//funkcje typu checkifExist sprawdzaja istnieje w liscie takiego samego obiektu
int checkifExistR( int nrOfRoom, struct Room* head );
int checkifExistP( char* name, char* sname, struct Person* head );


//funkcja usuwa wszystkie listy( pokoje, klienci, rezerwacje )
void close( struct Room* headR, struct Person* headP );


//funkcja typu syntax pobiera dane potrzebne do wykoania akcji, sprawdza ich poprawnosc i przypisuje ich wartosci do zmiennych pobranych
//zwraca 1 gdy sie powiedzie, 0 w przeciwnym przypadku
int syntaxRoom( int *nrOfRoom, struct Room* heap );
int syntaxPerson( char* name, char* sname, struct Person* head );
int syntaxReservation( char* name, char* sname, int* nrOfRoom, int* from, int* to, struct Room* headR, struct Person* headP );
int syntaxShowFree( int *from, int *to, struct Room* head );

//funkcja zwarca id klienta o danym imieniu i nazwisku
//zwraca -1 gdy nie znajdzie takiego klienta
int getClientId( char* name, char* sname, struct Person* head );

//funkcja sprawdza istnieje danej rezerwacji
//jesli juz istnieje zwraca 1, jesli nie zwarca 0
int checkifExistRes( int nrOfRoom, int from, int to, struct Room* headR, struct Person* headP );

//funkcja sprawdza czy 2 daty nachodza na siebie
//fukncja zwraca 1 gdy nachodza, w przeciwnym wypadku 0
int datesColiding( int from, int to, int from2, int to2 );
/*
Funkcja pobiera najwazniejsze dane do dzialania programu zadeklarowane w funkcji main.
Pobierane sa przez nie wskazniki do tych zmiennych z potrzeby zmiany ich wartosci w trakcie trwania dzialania programu.
Na podstawie wartosci zmiennej command podejmuje rozne dzialania. Po wykonaniu akcji lub stwierdzenia niepowodzenia fukncja zakancza dzialanie.
*/
void redirect( char* command, enum program *status, struct Room** headR, struct Person** headP );

//Funkcja wypisuje teksty pomocnicze dla uzytkownika
//Argumentem jest nazwa polecenia lub COMMANDS, aby uzyskac spis komend
void help(char* type);

//Funckja wypisuje tekst startowy oraz ustawia status programu na ON
void start( enum program* status );

//Funkcje typu rFunkcja zostaja wlaczone w zaleznosci od parametru command w funkjci redirect. Podejmuja glowne dzialania programu.
//W wiekszosci sprawdzaja poprawnosc pobranych danych i jesli bede one dobre, wykonuja dzialania.
void rAddRoom( struct Room** headR );
void rAddClient( struct Person** headP );
void rAddReservation( struct Person** headP, struct Room** headR );
void rHelp();
void rShowRooms( struct Room** headR );
void rShowClients( struct Person** headP );
void rShowFreeRooms( struct Room** headR );

#endif
