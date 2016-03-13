
/* c016.c: **********************************************************}
{* T�ma:  Tabulka s Rozpt�len�mi Polo�kami
**                      Prvn� implementace: Petr P�ikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      �pravy: Karel Masa��k, ��jen 2011
**
** Vytvo�ete abstraktn� datov� typ
** TRP (Tabulka s Rozpt�len�mi Polo�kami = Hash table)
** s explicitn� �et�zen�mi synonymy. Tabulka je implementov�na polem
** line�rn�ch seznam� synonym.
**
** Implementujte n�sleduj�c� procedury a funkce.
**
**  HTInit ....... inicializuje tabulku p�ed prvn�m pou�it�m
**  HTInsert ..... vlo�en� prvku
**  HTSearch ..... zji�t�n� p��tomnosti prvku v tabulce
**  HTDelete ..... zru�en� prvku
**  HTRead ....... p�e�ten� hodnoty prvku
**  HTClearAll ... zru�en� obsahu cel� tabulky (inicializace tabulky
**                 pot�, co ji� byla pou�ita)
**
** Definici typ� naleznete v souboru c016.h.
**
** Tabulka je reprezentov�na datovou strukturou typu tHTable,
** kter� se skl�d� z ukazatel� na polo�ky, je� obsahuj� slo�ky
** kl��e 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na dal�� synonymum 'ptrnext'. P�i implementaci funkc�
** uva�ujte maxim�ln� rozm�r pole HTSIZE.
**
**
** U v�ech procedur vyu��vejte rozptylovou funkci hashCode.  Pov�imn�te si
** zp�sobu p�ed�v�n� parametr� a zamyslete se nad t�m, zda je mo�n� parametry
** p�ed�vat jin�m zp�sobem (hodnotou/odkazem) a v p��pad�, �e jsou ob�
** mo�nosti funk�n� p��pustn�, jak� jsou v�hody �i nev�hody toho �i onoho
** zp�sobu.
**
** V p��kladech jsou pou�ity polo�ky, kde kl��em je �et�zec, ke kter�mu
** je p�id�n obsah - re�ln� ��slo.
*/

#include "c016.h"

#include <string.h>
#include <stdlib.h>

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** Rozptylovac� funkce - jej�m �kolem je zpracovat zadan� kl�� a p�id�lit
** mu index v rozmez� 0..HTSize-1.  V ide�ln�m p��pad� by m�lo doj�t
** k rovnom�rn�mu rozpt�len� t�chto kl��� po cel� tabulce.  V r�mci
** pokus� se m��ete zamyslet nad kvalitou t�to funkce.  (Funkce nebyla
** volena s ohledem na maxim�ln� kvalitu v�sledku). }
*/

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitn� z�et�zen�mi synonymy.  Tato procedura
** se vol� pouze p�ed prvn�m pou�it�m tabulky.
*/

void htInit ( tHTable* ptrht ) {
    
    if (ptrht == NULL)
        return;
    
    //inicializacia ukazatelov na NULL
    for (int i = 0; i < HTSIZE; i++)
        (*ptrht)[i] = NULL;
}

/* TRP s explicitn� z�et�zen�mi synonymy.
** Vyhled�n� prvku v TRP ptrht podle zadan�ho kl��e key.  Pokud je
** dan� prvek nalezen, vrac� se ukazatel na dan� prvek 
** Pokud prvek nalezen nen�, vrac� se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {
    //ak je tabulka alebo kluc NULL, vrati NULL TODO
    if (ptrht == NULL || key == NULL)
        return NULL;
    
    tHTItem * item = NULL;
    int index = hashCode(key);
    
    //prejdem dany linearny zoznam na danom indexe tabulky
    for (item = (*ptrht)[index]; item != NULL; item = item->ptrnext)
        if (strcmp(item->key, key) == 0)
            return item;
    
    //nenasiel som nic vratim NULL
    return NULL;
}

/* 
** TRP s explicitn� z�et�zen�mi synonymy.
** Tato procedura vkl�d� do tabulky ptrht polo�ku s kl��em key a s daty
** data.  Proto�e jde o vyhled�vac� tabulku, nem��e b�t prvek se stejn�m
** kl��em ulo�en v tabulce v�ce ne� jedenkr�t.  Pokud se vkl�d� prvek,
** jeho� kl�� se ji� v tabulce nach�z�, aktualizujte jeho datovou ��st.
**
** Vyu�ijte d��ve vytvo�enou funkci htSearch.  P�i vkl�d�n� nov�ho
** prvku do seznamu synonym pou�ijte co nejefektivn�j�� zp�sob,
** tedy prove�te.vlo�en� prvku na za��tek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {
    if (ptrht == NULL || key == NULL)
        return; //TODO
        
    tHTItem * item = htSearch(ptrht, key);
    
    //zaznam bol najdeny cize len aktualizuje hodnotu
    if (item != NULL)
        item->data = data;
    //zaznam nebol najdeny ideme vkladat
    else
    {
        tHTItem * new = (tHTItem *)malloc(sizeof(tHTItem));
        if (new == NULL)
            return; //TODO
        
        int key_len = strlen(key);
        new->key = (char *)calloc(key_len + 1, sizeof(char));
        if (new->key == NULL)
            return; //TODO
        
        //inicializacia
        new->data = data;
        strncpy(new->key, key, key_len);
        new->ptrnext = NULL;
        
        int index = hashCode(key);
        
        tHTItem *temp = (*ptrht)[index];
        (*ptrht)[index] = new;
        new->ptrnext = temp;        
    }
}

/*
** TRP s explicitn� z�et�zen�mi synonymy.
** Tato funkce zji��uje hodnotu datov� ��sti polo�ky zadan� kl��em.
** Pokud je polo�ka nalezena, vrac� funkce ukazatel na polo�ku
** Pokud polo�ka nalezena nebyla, vrac� se funk�n� hodnota NULL
**
** Vyu�ijte d��ve vytvo�enou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, tKey key ) {
    //ak tabulka alebo key je NULL TODO
    if (ptrht == NULL || key == NULL)
        return NULL;
    
    tHTItem * item = htSearch(ptrht, key);
    //ak sa polozka nenasla vrati NULL
    if (item == NULL)
        return NULL;
    else
    {
        //polozka bola najdena vratim ukzatel na data
        return &(item->data);
    }
}

/*
** TRP s explicitn� z�et�zen�mi synonymy.
** Tato procedura vyjme polo�ku s kl��em key z tabulky
** ptrht.  Uvoln�nou polo�ku korektn� zru�te.  Pokud polo�ka s uveden�m
** kl��em neexistuje, d�lejte, jako kdyby se nic nestalo (tj. ned�lejte
** nic).
**
** V tomto p��pad� NEVYU��VEJTE d��ve vytvo�enou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {
    //ak tabulka alebo key je NULL TODO
    if (ptrht == NULL || key == NULL)
        return;
    
    int index = hashCode(key);
    tHTItem * item = (*ptrht)[index];
    
    //ak polozka neexistuje neurobi nic
    if (item == NULL)
        return;
    
    tHTItem * old_item = item;
    
    for (; item != NULL; item = item->ptrnext)
    {        
        //ak som nasiel item s spravnym klucom, tak ho odstranim
        if (strcmp(item->key, key) == 0)
        {   
            //ak je iba jedna polozka
            if ((*ptrht)[index] == item && item->ptrnext == NULL)
                (*ptrht)[index] = NULL;
            else
                //ak su prave dve polozky a ma sa odstranit prva
                if ((*ptrht)[index] == item && item->ptrnext != NULL)
                    (*ptrht)[index] = item->ptrnext;
                else                    
                    old_item->ptrnext = item->ptrnext;
            
            free(item->key);
            free(item);
            return;
        }
        old_item = item;
    }        
}

/* TRP s explicitn� z�et�zen�mi synonymy.
** Tato procedura zru�� v�echny polo�ky tabulky, korektn� uvoln� prostor,
** kter� tyto polo�ky zab�raly, a uvede tabulku do po��te�n�ho stavu.
*/

void htClearAll ( tHTable* ptrht ) {
    //ak je tabulka NULL ukoncit TODO
    if (ptrht == NULL)
        return;
    
    for (int i = 0; i < HTSIZE; i++)
    {
        tHTItem * temp = NULL;
        for(tHTItem * item = (*ptrht)[i]; item != NULL; item = temp)
        {
            temp = item->ptrnext;
            
            free(item->key);
            free(item);            
        }
        (*ptrht)[i] = NULL;
    }
       
   // (*ptrht) = NULL;    //TODO
}
