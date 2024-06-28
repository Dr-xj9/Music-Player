#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <thread>
#include <windows.h>
#include"MMSystem.h"
using namespace std;
bool stopFlag=false;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void progressbar(int tiempo_actual, int tiempo_total)
{
    //system("cls");
    int porcentaje = (tiempo_actual * 100) / tiempo_total;
    int barra = porcentaje / 2;
    gotoxy(0, 15);
    cout << "Progreso: [";
    for (int i = 0; i < 50; i++) {
        if (i < barra) {
            cout << "|";
        } else {
            cout << " ";
        }
    }
    cout << "] " << porcentaje << "%";
    gotoxy(13, 16);
    cout << "Tiempo: " << tiempo_actual << "s / " << tiempo_total << "s";
}
void Menu()
{
    gotoxy(55,0);
    cout<<" -- Menu -- "<<endl;
    gotoxy(55,1);
    cout<<" 1. Registrar Cancion "<<endl;
    gotoxy(55,2);
    cout<<" 2. Buscar "<<endl;
    gotoxy(55,3);
    cout<<" 3. Ordenar "<<endl;
    gotoxy(55,4);
    cout<<" 4. Invertir Lista "<<endl;
    gotoxy(55,5);
    cout<<" 5. Editar Registro "<<endl;
    gotoxy(55,6);
    cout<<" 6. Remover Registro "<<endl;
    gotoxy(55,7);
    cout<<" 7. Vaciar Lista "<<endl;
    gotoxy(55,8);
    cout<<" 8. Reproducir Cancion "<<endl;
    gotoxy(55,9);
    cout<<" 9. Detener Cancion "<<endl;
    gotoxy(55,10);
    cout<<" 0. Salir "<<endl;
}

class Node
{
  public:
	int index;
	char name[30];
	char time[10];
	char artista[20];
	Node *next;
	Node *back;
};

class Song
{
	private:
		int index;
		char name[30];
		char time[10];
		char artista[20];
	public:
	    void setArt(char*);
	    char* getArt();
		void setIndex(int);
		int getIndex();
		void setName(char*);
		char* getName();
		void setTime(char*);
		char* getTime();
};

class CircularList
{
	private:
		Node *ptrHead;
	public:
		CircularList();
		void insert_First(Song);
		bool empty();
		void print();
		void moveTo(int);
		void BuscarID(int);
		void BuscarNombre(char*);
		void BuscarArtista(char*);
		void Invertir();
		void Ordenar(int);
		void Remover(int);
		void Editar(int);
		void Vaciar();
		char* getCancion();
		char* getTiempo();
		//void progressbar();
};

//FUNCIONES CLASE SONG //
void Song::setArt(char* artista)
{
    strcpy(this->artista, artista);
}
char* Song::getArt()
{
    return this->artista;
}

void Song::setIndex(int index)
{
	this->index=index;
}

int Song::getIndex()
{
	return this->index;
}

void Song::setName(char* name)
{
	strcpy(this->name,name);
}

char* Song::getName()
{
	return this->name;
}

void Song::setTime(char* time)
{
	strcpy(this->time,time);
}

char* Song::getTime()
{
	return this->time;
}
//FUNCIONES DE LA LISTA CIRCULAR //
CircularList::CircularList()
{
	ptrHead = NULL;
}

void CircularList::Vaciar()
{
    while(!empty())
    {
        Remover(ptrHead->index);
    }
}

char* CircularList::getTiempo()
{
    return this->ptrHead->time;
}

void CircularList::Editar(int id)
{
    Node *temp = ptrHead;
    do
    {
        if(id == temp->index)
        {
            gotoxy(50,15);
        cout<<"Index: ";
        cin>>temp->index;
        gotoxy(50,16);
        cout<<"Cancion: ";
        cin>>temp->name;
        gotoxy(50,17);
        cout<<"Duracion: ";
        cin>>temp->time;
        gotoxy(50,18);
        cout<<"Artista: ";
        cin>>temp->artista;
        }
        temp=temp->next;
    }
    while(temp != ptrHead);
}

void CircularList::Invertir()
{
    Node *temp = ptrHead;
    do {
        Node *aux = temp->next;
        temp->next = temp->back;
        temp->back = aux;
        temp = aux;
    } while(temp != ptrHead);

    // Actualizar el puntero ptrHead para que apunte al nuevo primer nodo
    ptrHead = ptrHead->back;
}

void CircularList::Remover(int id)
{
    bool encontrado = false;
	if (!empty())
	{
		Node *temp = ptrHead;
		Node *ultimo = ptrHead->back;
		do
		{
		  if(id == temp->index)
		  {
		  	 encontrado = true;
		  	if(ptrHead->back == ptrHead && ptrHead->next == ptrHead) // Si es el unico en la lista //
		  	{
		  		//cout<<" Es el unico ... "<<endl;
		  		ptrHead = NULL;
                ultimo->next = NULL;
                delete temp;
		  		break;
			}
			if(temp == ptrHead) 			//  Si es el primero //
			{
				//cout<<" Es el primero ... "<<endl;
				temp->back->next = temp->next;
				temp->next->back = temp->back;
				ptrHead = temp->next;
				ultimo->next = ptrHead;
				delete temp;
				break;
			}
			else
			{
				//cout<<" Es intermedio o ultimo ..."<<endl;
				temp->back->next = temp->next;
				temp->next->back = temp->back;
				delete temp;
				break;
			}
		  }
		   temp=temp->next;
		}
		while(temp!=ptrHead);
		if (encontrado == false)
		{
			cout<<" No existe :c "<<endl;
		}
	}
}


void CircularList::Ordenar(int opc)
{
    switch(opc)
    {
    case 1: //Ordenar por ID Ascendente //
    {
        int temp;
        char Cancion[20];
        char Artista[20];
        char Duracion[20];
	Node *ptrNode;
	bool cambio;
	do
	{
      cambio = false;
      ptrNode = ptrHead;
      while (ptrNode->next != ptrHead)
	  {
        if (ptrNode->index > ptrNode->next->index)
		  {
             // intercambiar valores
             temp = ptrNode->index;
             strcpy(Cancion,ptrNode->name);
             strcpy(Artista,ptrNode->artista);
             strcpy(Duracion, ptrNode->time);

             ptrNode->index = ptrNode->next->index;
             strcpy(ptrNode->name,ptrNode->next->name);
             strcpy(ptrNode->artista,ptrNode->next->artista);
             strcpy(ptrNode->time,ptrNode->next->time);

             ptrNode->next->index= temp;
             strcpy(ptrNode->next->name, Cancion);
             strcpy(ptrNode->next->artista, Artista);
             strcpy(ptrNode->next->time, Duracion);
             cambio = true;
          }
           ptrNode = ptrNode->next;
        }
    }
	while (cambio);
    }
    break;
    case 2: //Ordenar Descendente //
    {
        int temp;
        char Cancion[20];
        char Artista[20];
        char Duracion[20];
	Node *ptrNode;
	bool cambio;
	do
	{
      cambio = false;
      ptrNode = ptrHead;
      while (ptrNode->next != ptrHead)
	  {
        if (ptrNode->index < ptrNode->next->index)
		  {
             // intercambiar valores
             temp = ptrNode->index;
             strcpy(Cancion,ptrNode->name);
             strcpy(Artista,ptrNode->artista);
             strcpy(Duracion, ptrNode->time);

             ptrNode->index = ptrNode->next->index;
             strcpy(ptrNode->name,ptrNode->next->name);
             strcpy(ptrNode->artista,ptrNode->next->artista);
             strcpy(ptrNode->time,ptrNode->next->time);

             ptrNode->next->index= temp;
             strcpy(ptrNode->next->name, Cancion);
             strcpy(ptrNode->next->artista, Artista);
             strcpy(ptrNode->next->time, Duracion);
             cambio = true;
          }
           ptrNode = ptrNode->next;
        }
    }
	while (cambio);
    }
    break;
    case 3: //Ordenar Nombre Cancion //
    {
    int temp;
        char Cancion[20];
        char Artista[20];
        char Duracion[20];
	Node *ptrNode;
	bool cambio;
	do
	{
      cambio = false;
      ptrNode = ptrHead;
      while (ptrNode->next != ptrHead)
	  {
        if (strcmp(ptrNode->name, ptrNode->next->name) > 0)
		  {
             // intercambiar valores
             temp = ptrNode->index;
             strcpy(Cancion,ptrNode->name);
             strcpy(Artista,ptrNode->artista);
             strcpy(Duracion, ptrNode->time);

             ptrNode->index = ptrNode->next->index;
             strcpy(ptrNode->name,ptrNode->next->name);
             strcpy(ptrNode->artista,ptrNode->next->artista);
             strcpy(ptrNode->time,ptrNode->next->time);

             ptrNode->next->index= temp;
             strcpy(ptrNode->next->name, Cancion);
             strcpy(ptrNode->next->artista, Artista);
             strcpy(ptrNode->next->time, Duracion);
             cambio = true;
          }
           ptrNode = ptrNode->next;
        }
    }
	while (cambio);
    }
    break;
    case 4: //Ordenar Artista //
    {
        int temp;
        char Cancion[20];
        char Artista[20];
        char Duracion[20];
        Node *ptrNode;
        bool cambio;
	do
	{
      cambio = false;
      ptrNode = ptrHead;
      while (ptrNode->next != ptrHead)
	  {
        if (strcmp(ptrNode->artista, ptrNode->next->artista) > 0)
		  {
             // intercambiar valores
             temp = ptrNode->index;
             strcpy(Cancion,ptrNode->name);
             strcpy(Artista,ptrNode->artista);
             strcpy(Duracion, ptrNode->time);

             ptrNode->index = ptrNode->next->index;
             strcpy(ptrNode->name,ptrNode->next->name);
             strcpy(ptrNode->artista,ptrNode->next->artista);
             strcpy(ptrNode->time,ptrNode->next->time);

             ptrNode->next->index= temp;
             strcpy(ptrNode->next->name, Cancion);
             strcpy(ptrNode->next->artista, Artista);
             strcpy(ptrNode->next->time, Duracion);
             cambio = true;
          }
           ptrNode = ptrNode->next;
        }
    }
	while (cambio);
    }
    break;
    }

}

char* CircularList::getCancion()
{
    return this->ptrHead->name;
}

void CircularList::BuscarArtista(char* artista)
{
    Node *temp = ptrHead;
    do
    {
        if(strcmpi(artista,temp->artista) == 0)
        {
            gotoxy(50,16);
        cout<<"Index: [ "<<temp->index<<" ]"<<endl;
        gotoxy(50,17);
            cout<<"Cancion: [ "<<temp->name<<" ]"<<endl;
            gotoxy(50,18);
        cout<<"Duracion: [ "<<temp->time<<" ]"<<endl;
        gotoxy(50,19);
            cout<<"Artista: [ "<<temp->artista<<" ]";
        }
        temp=temp->next;
    }
    while(temp != ptrHead);
}
void CircularList::BuscarNombre(char* cancion)
{
    Node *temp = ptrHead;
    do
    {
        if(strcmpi(cancion,temp->name) == 0)
        {
            gotoxy(50,16);
            cout<<"Index: [ "<<temp->index<<" ]"<<endl;
            gotoxy(50,17);
            cout<<"Cancion: [ "<<temp->name<<" ]"<<endl;
            gotoxy(50,18);
            cout<<"Duracion: [ "<<temp->time<<" ]"<<endl;
            gotoxy(50,19);
            cout<<"Artista: [ "<<temp->artista<<" ]";
        }
        temp=temp->next;
    }
    while(temp != ptrHead);
}
void CircularList::BuscarID(int id)
{
    Node *temp = ptrHead;
    do
    {
        if(id == temp->index)
        {
            gotoxy(50,16);
            cout<<"Index: [ "<<temp->index<<" ]"<<endl;
            gotoxy(50,17);
            cout<<"Cancion: [ "<<temp->name<<" ]"<<endl;
            gotoxy(50,18);
            cout<<"Duracion: [ "<<temp->time<<" ]"<<endl;
            gotoxy(50,19);
            cout<<"Artista: [ "<<temp->artista<<" ]";
        }
        temp=temp->next;
    }
    while(temp != ptrHead);
}
void CircularList::insert_First(Song song)
{
	Node *new_node = new Node();
	new_node->index =song.getIndex();
	strcpy(new_node->name, song.getName());
	strcpy(new_node->time ,song.getTime());
	strcpy(new_node->artista, song.getArt());
	if (ptrHead == NULL)
	{
		new_node->next = new_node;
		new_node->back = new_node;
		ptrHead = new_node;
	}
	else
	{
		Node *last_node = ptrHead->back;
		new_node->next = ptrHead;
		new_node->back = last_node;
		ptrHead->back = new_node;
		last_node->next = new_node;
		ptrHead = new_node;
	}
}

bool CircularList::empty()
{
	if (ptrHead == NULL)
	return true;
	else
	return false;
}

void CircularList::print()
{
	if (!empty())
	{
	    Node *temp = ptrHead;
		gotoxy(0,0);
                cout<<"|  Index   |"<<"  Nombre         |"<<"  Duracion |"<<"  Artista       "<<endl;
                gotoxy(0,1);
                cout<<"|          |"<<"                 |"<<"           |"<<"                "<<endl;
		do
		{
		    int cont=2;
		    if(temp == ptrHead)
            {
                //gotoxy(0,cont);
                cout<<"| --> "<<temp->index <<"    | "<<temp->name <<"   | "<<temp->time<<"       |  "<<temp->artista<<endl;
            }
            else
            {
                //gotoxy(0,cont+1);
                 cout<<"|     "<<temp->index <<"    | "<<temp->name <<"   | "<<temp->time<<"       |  "<<temp->artista<<endl;
			}
			temp = temp->next;
			cont++;
		}
		while (temp != ptrHead);
	}
}

void CircularList::moveTo(int opc)
{
 int i=0;
	if (!empty())
	{
		Node *temp = ptrHead;
		if(opc==1)
		{
			//cout<<"-> [ "<<temp->index <<" ]"<<endl;
			temp = temp->next;
			ptrHead=temp;
		}
		else if(opc==2)
		{
			//cout<<"[ "<<temp->index <<" ]"<<endl;
			temp = temp->back;
			ptrHead=temp;
		}
	}
}

int main(int argc, char** argv)
{
    system("Title Reproductor de Musica ");
	int opc=0,opc2=0, tiempo=0;
	char Cancion[20];
	char Artista[25];
	char Duracion[20];
	int index;
	bool salir;
	bool reproduciendo;
	CircularList *obj = new CircularList();
	Song song;
	do
    {
        system("cls");
        gotoxy(0,0);
        obj->print();
        gotoxy(50,0);
        Menu();
        char opc = getch();
        switch(opc)
        {
         case 48: salir=true; break;
         case 49:
             gotoxy(50,11);
            cout<<"Nombre de la cancion: ";
            gotoxy(50,12);
            cin>>Cancion;
            song.setName(Cancion);
            gotoxy(50,13);
            cout<<"Duracion [En segundos]: ";
            gotoxy(50,14);
            cin>>Duracion;
            song.setTime(Duracion);
            gotoxy(50,15);
            cout<<"Artista: ";
            gotoxy(50,16);
            cin>>Artista;
            song.setArt(Artista);
            gotoxy(50,17);
            cout<<"Index: ";
            gotoxy(50,18);
            cin>>index;
            song.setIndex(index);
            obj->insert_First(song);
        break;
         case 50:
             {
                int op, id;
                char nombre[25];
                gotoxy(50,11);
                cout<<" Selecciona "<<endl;
                gotoxy(50,12);
                cout<<" 1. Buscar Por Index "<<endl;
                gotoxy(50,13);
                cout<<" 2. Buscar Cancion "<<endl;
                gotoxy(50,14);
                cout<<" 3. Buscar Artista "<<endl;
                gotoxy(50,15);
                cout<<" Opcion: [1-3]: ";
                cin>>op;
                switch(op)
                {
                case 1:
                    gotoxy(50,16);
                    cout<<" Index: ";
                    cin>>id;
                    obj->BuscarID(id);
                    system("pause>>cls");
                break;
                case 2:
                    gotoxy(50,17);
                    cout<<" Cancion: ";
                    cin>>nombre;
                    obj->BuscarNombre(nombre);
                    system("pause>>cls");
                break;
                case 3:
                    gotoxy(50,18);
                    cout<<" Artista: ";
                    cin>>nombre;
                    obj->BuscarArtista(nombre);
                    system("pause>>cls");
                break;
                }
             }
            break;
        case 51:
            {
                int opcion;
                gotoxy(50,11);
                cout<<"1. Ascendente "<<endl;
                gotoxy(50,12);
                cout<<"2. Descendente "<<endl;
                gotoxy(50,13);
                cout<<"3. Nombre de la Cancion "<<endl;
                gotoxy(50,14);
                cout<<"4. Nombre del Artista "<<endl;
                gotoxy(50,15);
                cin>>opcion;
                obj->Ordenar(opcion);
            }
        break;
        case 52:
            {
                obj->Invertir();
            }
        break;
        case 53:
            {
                int id;
                gotoxy(50,11);
                cout<<"Index a editar: ";
                cin>>id;
                obj->Editar(id);
            }
            break;
        case 54:
            {
                int index;
                gotoxy(50,11);
                cout<<"Remover (index): ";
                cin>>index;
                obj->Remover(index);
            }
            break;
        case 55:
            {
                obj->Vaciar();
            }
            break;
        case 56:
        {
            // Obtener el nombre y tiempo de la canción
            string cancionname = obj->getCancion();
            string extencion = ".wav";
            string concatenacion = cancionname + extencion;
            const char* filename = concatenacion.c_str();
            int tiempo_total = atoi(obj->getTiempo());
            int tiempo_actual=0;
            // Iniciar la reproducción de la canción y la actualización del tiempo actual
            system("Title Reproduciendo (...) ");
            PlaySound(TEXT(filename), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            reproduciendo = true;
            thread t([&](){
                while (reproduciendo && tiempo_actual < tiempo_total)
                {
                    tiempo_actual++;
                    progressbar(tiempo_actual,tiempo_total);
                    Sleep(1000);
                }
                PlaySound(NULL, NULL, 0);
            });
            t.detach();
        }
        break;
        break;
        case 57:
        {
            PlaySound(NULL, NULL, 0);
            reproduciendo=false;
        }
        break;
        case 72: // flecha hacia arriba
            obj->moveTo(2);
        break;
        case 80: // flecha hacia abajo
            obj->moveTo(1);
        break;
        }
    }
    while(salir==false);
  return 0;
}
