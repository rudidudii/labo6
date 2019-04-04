// Nei calcoli di complessita', n indica la dimensione del dizionario

#include "dictionary.h"

using namespace dict;

struct dict::treeNode {
    Elem elem;
    treeNode* firstChild;
    treeNode* nextSibling;
};

typedef treeNode* Tree;


/****************************************************************/
Error dict::deleteElem(const Key k, Dictionary& s)
{
    // Non implementata: potete implementarla voi per esercizio
    cout << "La deleteElem non e' ancora implementata... potete implementarla voi per esercizio!\n";
    return FAIL;
}


/****************************************************************/
Dictionary readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict();}  
    // cout << "\n[dict::readFromFile] Apertura file completata\n";
    return readFromStream(ifs);
}



/****************************************************************/
Dictionary readFromStdin()
{
    cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
    Dictionary d = readFromStream((std::cin));
// Questa serve per aggirare un bug di alcune versioni attuali di glibc.
    clearerr(stdin);
    return d;
}


/****************************************************************/
Dictionary readFromStream(istream& str)
{
    Dictionary d = createEmptyDict();      
    string key, kcopy;
    string value;
    getline (str, key, ':'); // cout << "\n[readFromStream] key: " << key;
    getline (str, value); // cout << "\n[readFromStream] value: " << value;
    while (!str.eof())  
        {         
        kcopy = key;
        removeBlanksAndLower(kcopy);
        insertElem(kcopy, value, d);
        getline (str, key, ':'); 
        getline (str, value); 
        }
    str.clear();
    return d;
}


/****************************************************************/
// Inizializzazione della lista con creazione del nodo sentinella; obbligatorio dopo la dichiarazione di una lista
Dictionary dict::createEmptyDict()
{
    // Crea radice
    Tree t = new treeNode;
    t->Elem.key = emptyKey;
    t->Elem.value = emptyValue;
    t->firstChild = emptyfirstChild;
    t->nextSibling = emptynextSibling;

    return t;
}


/****************************************************************/
// Inserimento di un record prima del nodo puntato da p 
void inserisci_prima(nodoPtr &p, Key k, Value v)
{
    nodoPtr q = new nodo;
    (q->elem).key = k;
    (q->elem).value = v;
    q->precedente = p->precedente;
    q->prossimo = p;
    p->precedente = q;
    q->precedente->prossimo=q;
}

/****************************************************************/
// Restituisce il puntatore al primo nodo nella lista che contiene una chiave >= k nella lista
nodoPtr maggiore_o_uguale(Key k, const Dictionary& s){
    // "salta la sentinella" e va alla testa della lista
    nodoPtr q = s->prossimo;
    // avanza finche' non finisce la lista o non trovi una chiave >= k
    while (q != s && (q->elem).key < k )
	q = q->prossimo;
    return q;
}

/****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Tree& s)
{
	
    nodoPtr magg_uguale = maggiore_o_uguale(k, s);
    // Lo inserisco
    inserisci_prima(magg_uguale, k, v);
    return OK;
}


/****************************************************************/
Value dict::binsearch(const Key k, const Dictionary& s)
{
    if (start==end)
   {
   if (d[start].key==k) return d[start].value;
   else return emptyValue;
   }
  
int mid = (start+end)/2;

if (d[mid].key==k) return d[mid].value;

if (k > d[mid].key) return binSearch(mid+1,end,d,k); 
else return binSearch(start,mid,d,k); 
}


/****************************************************************/
void print(const Dictionary& s)
{
    // "salta la sentinella" e va alla testa della lista
    nodoPtr q = s->prossimo;
    while (q != s) // avanza finche' non finisce la lista
    {
        cout << (q->elem).key << ": " << (q->elem).value << endl;
        q = q->prossimo;
    }
}
/****************************************************************/
Tree getNode(const Key l, const Tree& t)
{
	/* se t è vuoto o l'etichetta è vuota restituisco emptyTree */
	if (isEmpty(t))
	return emptyTree;
	/* se l'etichetta di t è quella cercata, restituisco t */
	if (t->Elem.key == l)
	return t;
	/* ...chiamata ricorsiva di getNode su ciascuno dei figli di t, finché
	una delle chiamate non restituisce un valore diverso da emptyTree....
	Rispetto alla visita esaustiva vista prima, la getNode non deve per forza
	esplorare tutto l'albero: quando una delle chiamate restituisce un
	albero != emptyTree, si deve fare return di tale albero non vuoto
	interrompendo la scansione dei fratelli */
	while(t==emptyTree){
	getNode(l,t->firstChild);
	getNode(l,t->nextSibling);
	}
	return t;
}
/****************************************************************/
bool isEmpty(Tree& t){
	return (t==emptyTree);
	}
