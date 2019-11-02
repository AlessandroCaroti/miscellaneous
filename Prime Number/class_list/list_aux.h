#ifndef DATASTRUCT
#define DATASTRUCT

#include <cstddef>
#include <stdexcept>
#include <pthread.h>

namespace dataStruct {

	typedef int Elem;
	struct node;
	typedef node* LinkedList;
	typedef node* Node;
	struct List;
	const int FINEINPUT = -314159265;
	const Elem EMPRYELEM = -1;
	const Node EMPTYNODE = nullptr;
	const LinkedList ENDLIST = nullptr;
	
	class List{  
		private:
																	// Una lista lincata di nodi può essere condivisa tra più classi List
			volatile LinkedList ls;							// Rappresenta la lista lincata ed essenzialmente è il puntatore al 1° nodo della lista
			volatile int* size;								// Numero di nodi nella lista ls
			node* lastNode;									// Puntatore all'ultimo nodo della lista
			node* currNode;

			node* newNode(const Elem );
			void freeLinkedList();
			inline bool isEmpty_node(const node* );

		public:
			List();									/*Costruttore List, inizializza a lista vuota*/
			List(const List*);					/*Costruttore List, inizializza la lista con la lista presente nell'oggetto List passato*/
			~List();
			inline bool hasNext();				/* Restituisce FALSE se il nodo puntato da 'currNode' è l'ultimo della lista*/
			inline Elem getNext();				/* Restituisce il prossimo elemento puntato da 'currNode'*/
			bool isEmpty();						/* Restituisce TRUE se la lista e' vuota */
			void add(const Elem);				/* Inserisce l'elemento alla fine nella posizione corretta*/
			int  getSize();						/* Restituisce la dimensione della lista*/
			void resetCurr();						/* Reimposta il puntatore 'currNode' all'inizio della lista*/

			static void readFromFile(char* ,List&);			/* legge il contenuto di una lista da file */
			static void printOnFile(const List&);          	/* Stampa la lista */

	};
}

#endif // !DATASTRUCT