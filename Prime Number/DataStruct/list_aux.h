#ifndef DATASTRUCT
#define DATASTRUCT

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <fstream> 
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
*/
using namespace std;

namespace dataStruct {

	typedef int Elem;
	struct node;
	typedef node* list;
	typedef node* Node;
	struct List;
	const int FINEINPUT = -1000000;
	const Elem EMPRYELEM = -1;
	const Node EMPTYNODE = nullptr;
	const list ENDLIST = nullptr;

	void clear(List&);							/* "smantella" la lista (usata esclusivamente nel main)*/
	inline bool hasNext(List&);				/* restituisce FALSE se il nodo passato è l'ultimo della lista*/
	inline Elem getNext(List&);				/* restituisce il prossimo elemento */
	void add(const Elem, List&);				/* inserisce l'elemento alla fine della lista ACCESSO CONCORRENTE*/
	bool isEmpty(const List&);					/* restituisce TRUE se la lista e' vuota */
	int  size(const List&);						/* restituisce la dimensione della lista */
	void createEmpty(List&);					/* inizializza una lista vuoto (usata esclusivamente nel main)*/
}


void readFromFile(string, dataStruct::List&);		/* legge il contenuto di una lista da file (usata esclusivamente nel main)*/
void printOnFile(const dataStruct::List&);          /* stampa la lista (usata esclusivamente nel main)*/


#endif // !DATASTRUCT