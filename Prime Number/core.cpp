#include "core.h"

using namespace dataStruct;

int main(int argc, char **argv)//"core.cpp" NumFork NumMassimo FileOutput FileInput
{
	//lo standard output sarà chiuso e utilizzata per comunicare con il processo "main" 

	int nFork;				//numero di fork
	int ID=0;
	int outF, inF;
	int status[2];			//utilizzato per la comunicazione con i vari cloni
	pid_t pid = getpid();
	bool p_flag = true;
	List ls;
	Elem e, maxNum;
	createEmpty(ls);
	nFork = DEFAULTFORK; maxNum = MAXNUM; outF = 1; inF = -1;
	if (argc>1)
		sscanf(argv[1], "%d", &nFork);
	if (argc>2)
		sscanf(argv[2], "%d", &maxNum);
	if (argc>3)
		sscanf(argv[3], "%d", &outF);
	if (argc>4)
		sscanf(argv[4], "%d", &inF);
	if (nFork > MAXFORK)
		nFork = MAXFORK;

	//-possibile caricamento di numeri primi da un file input
	//-creare una pipe con status
	//-definire un canale di comunicazione tra i processi "care" e il processo "main"

	while (nFork > 0)
	{
		if ((pid = fork()) < 0)		//fork non riuscito
		{
			perror("Bad fork!");
			//UCCIDI TUTTI I FILGI GRAZIE ALLA LISTA DEI FIGLI INVIANDO UNA KILL A TUTTO IL GRUPPO DI PROCESSI
			exit(5);
		}
		if (pid == 0)           /***** Child *****/
			break;
		nFork--;
	}
	if (pid!=0)					/***** Parent ****/
	{
		//invia il segnale al tutti i figli che sono tìriusciti tutti i fork
		//wirite(.....) oppure invia un segnale
	}
	else           /***** Child *****/
	{
		//inizializare con il numero del filgio dire quanti salti deve fare
		ID = nFork;
		//aspetta segnale di successo dal figlio 0
		//int sig = pause();	metodo più sicuro e usare sigsuspend(2)  guarda https://www.gnu.org/software/libc/manual/html_node/Sigsuspend.html#Sigsuspend
		//read(...) oppure un pause() con un segnale guarda SIGNAL(7)
	}
	//segnalare che è tutto pronto per partire


	for (Elem N = 2; N < manNum; N++)
	{
		while ((e = getNext(ls)) != -1 && e < (N / 2))
		{
			//ogni un tot di calcoli bisogna controllare se gli altri hanno trovato qualcosa
			if (e % N == 0)
			{
				p_flag = false;
				break:			//numero NON PRIMO
			}
		}
		if (p_flag)
		{
			//numero non primo
			//segnalare agli altri che non è primo
		}
		else
		{
			//numero primo
		}
	}
	return 0;
}