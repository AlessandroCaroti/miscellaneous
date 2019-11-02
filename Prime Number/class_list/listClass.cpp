#include <stdio.h>
#include "list_aux.h"
#include "../utils.h"

using namespace dataStruct;


/***************************************************/
/*		Dichiarazione della struttura dati node		*/
/***************************************************/

struct dataStruct::node {
	Elem info;
	node *next;
};


/*****************************************************/
/* Definizione dei metodi pubblic della classe List  */
/*****************************************************/

List::List()
{
   size = (int*)my_malloc(sizeof(int));
   *size = 0;
   lastNode = EMPTYNODE;
   currNode = EMPTYNODE;
   ls = ENDLIST;
}

List::List(const List* l)
{
   ls = l->ls;
   lastNode = l->lastNode;
   currNode = ls;
   size = l->size;
}

List::~List()
{
   free((void*)size);
   freeLinkedList();
}

inline bool List::hasNext()
{
   return (currNode != EMPTYNODE);
}

inline Elem List::getNext()
{
   if(!hasNext())
      return EMPRYELEM;
   currNode = currNode->next;
   return currNode->info;
}

void List::add(const Elem e)
{
   //da gestire in maniera concorrente
   node* toAdd = newNode(e);
   //Inizo Sezione Critica
      //trova la posizione dove aggiungerlo
      //aggiungi il nodo aggiustano i puntatori
      //cerca la fine della lista
   //Fine Sezione Critica
   #ifndef MY_OPTIMIZATION
   //altra sezione critica(INCREMENTA LA SIZE)
   #endif
}

bool List::isEmpty()
{
   return (*size == 0);
}
int List::getSize()
{
   #ifndef MY_OPTIMIZATION
      return *size;
   #else
      int s=0;
      node* aux = ls;
      while (!isEmpty_node(aux))
      {
         s++
         aux = aux->next;
      }
      return s;
   #endif
}	


/*****************************************************/
/* Definizione dei metodi privati della classe List  */
/*****************************************************/

node* List::newNode(const Elem e)
{
   node* _newCell_ = my_malloc(sizeof(node));
	_newCell_->info = e;
	return _newCell_;
}

void List::freeLinkedList()
{
   node* aux;
	while (!isEmpty_node(ls))
	{
		aux = ls;
		ls = ls->next;
		free(ls);
	}
}

inline bool List::isEmpty_node(const node* n)
{
   return (n == EMPTYNODE);
}



void List::readFromFile(char* fileName,List& l)
{
   printf("NON ANCORA IMPLEMENTATA\n");
}

void List::printOnFile(const List& l)
{
   printf("NON ANCORA IMPLEMENTATA\n");
}


