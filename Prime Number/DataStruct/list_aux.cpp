#include "list_aux.h"

using namespace dataStruct;

/*********************************************************/
/*		Dichiarazione delle strutture dati della lista		*/
/*********************************************************/

volatile int size_ = 0;

struct dataStruct::node {
	Elem info;
	node *next;
};

struct dataStruct::List {
	list ls;							// Puntatore al 1° nodo della lista
	node* lastNode;				// Puntatore all'ultimo nodo della lista
	node* currNode;
	volatile int* size;			// #elemnti nella lista
};



/*************************************************/
/*		Dichiarazione funzioni ausiliarie		 	 */
/*************************************************/

void add_aux(node* ,const Elem);
node* newNode(const Elem );
void freeList(list& );
inline bool isEmpty_node(const node* );



/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

void dataStruct::clear(List& l)
{
	*(l.size) = 0;
	l.lastNode = EMPTYNODE;
	l.currNode = EMPTYNODE;
	freeList(l.ls);
}

inline bool dataStruct::hasNext(List& l)
{
	return (l.currNode == EMPTYNODE);
}

inline Elem dataStruct::getNext(List& l)
{
	if (isEmpty_node(l.currNode))	//forse sbagliato no deve contrllare il prossimo // forse è giusto
		return EMPRYELEM;
	l.currNode = l.currNode->next;
	return l.currNode->info;
}

void dataStruct::add(const Elem e, List& l)
{
	add_aux(l.lastNode, e);
	l.lastNode = l.lastNode->next;
	++*(l.size);
}


bool dataStruct::isEmpty(const List& l)
{
	return (*(l.size) == 0);
}

int dataStruct::size(const List& l)
{
	return *(l.size);
}

void dataStruct::createEmpty(List& l)
{
	l.currNode = EMPTYNODE;
	l.lastNode = EMPTYNODE;
	l.ls = ENDLIST;
	l.size = &size_;
}



/*************************************************/
/*		Implementazione funzioni ausiliarie		 */
/*************************************************/

node* newNode(Elem e)
{
	node* _newCell_ = new node;
	_newCell_->info = e;
	_newCell_->next = ENDLIST;
	return _newCell_;
}

void add_aux(node* n, const Elem e)
{
	node* tmp = newNode(e);
	n->next = tmp;
}

void freeList(list& l)
{
	node* aux;
	while (!isEmpty_node(l))
	{
		aux = l;
		l = l->next;
		delete aux;
	}
}

inline bool isEmpty_node(const node* n)
{
	return (n == EMPTYNODE);
}





/***********************************************/
/* Implementazione delle operazioni di utilità */
/***********************************************/


void readFromFile(char* nome_file, List& l) 
{
	
}


void printOnFile(const List& l)       
{
	
}