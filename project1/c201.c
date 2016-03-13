
/* c201.c *********************************************************************}
{* T�ma: Jednosm�rn� line�rn� seznam
**
**                     N�vrh a referen�n� implementace: Petr P�ikryl, ��jen 1994
**                                          �pravy: Andrea N�mcov� listopad 1996
**                                                   Petr P�ikryl, listopad 1997
**                                P�epracovan� zad�n�: Petr P�ikryl, b�ezen 1998
**                                  P�epis do jazyka C: Martin Tu�ek, ��jen 2004
**	                                          �pravy: Bohuslav K�ena, ��jen 2010
**
** Implementujte abstraktn� datov� typ jednosm�rn� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je cel� ��slo typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou typu tList.
** Definici konstant a typ� naleznete v hlavi�kov�m souboru c201.h.
** 
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu s v��e
** uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ tList:
**
**      InitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DisposeList ... zru�en� v�ech prvk� seznamu,
**      InsertFirst ... vlo�en� prvku na za��tek seznamu,
**      First ......... nastaven� aktivity na prvn� prvek,
**      CopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DeleteFirst ... zru�� prvn� prvek seznamu,
**      PostDelete .... ru�� prvek za aktivn�m prvkem,
**      PostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      Copy .......... vrac� hodnotu aktivn�ho prvku,
**      Actualize ..... p�ep�e obsah aktivn�ho prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal�� prvek seznamu,
**      Active ........ zji��uje aktivitu seznamu.
**
** P�i implementaci funkc� nevolejte ��dnou z funkc� implementovan�ch v r�mci
** tohoto p��kladu, nen�-li u funkce explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam 
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error()	{
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* Chyba p�i pr�ci se seznamem.\n");
    errflg = TRUE;                      /* glob�ln� prom�nn� -- p��znak chyby */
}

void InitList (tList *L)	{
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/

	//inicializuje ukazatel na aktualny prvok na NULL
	L->Act = NULL;
	//inicializuje ukazatel na prvy prvok na NULL
	L->First = NULL;
}

void DisposeList (tList *L)	{
/*
** Zru�� v�echny prvky seznamu L a uvede seznam L do stavu, v jak�m se nach�zel
** po inicializaci. V�echny prvky seznamu L budou korektn� uvoln�ny vol�n�m
** operace free.
***/

	//prejdem vsetky prky zoznamu L->Act ukazatelom
	for (L->Act = L->First; L->Act != NULL; L->Act = L->First)
	{
		//aby prvy ukazoval na dalsi
		L->First = L->First->ptr;
		//uvolnenie polozky
		free(L->Act);
	}
	
	//inicializacia na NULL
	L->Act = NULL;
	L->First = NULL;
}

void InsertFirst (tList *L, int val)	{
/*
** Vlo�� prvek s hodnotou val na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci Error().
**/

	tElemPtr item = malloc(sizeof(struct tElem));
	if (item == NULL)
	{
		Error();
		return;
	}
	
	//val ulozi do prvku
	item->data = val;
	//prvok bude ukazovat na prvok co bol na zaciatku zoznamu
	item->ptr = L->First;
	//zaciatok zoznamu bude ukazovat na prvok - bol prydany na zaciatok
	L->First = item;
}

void First (tList *L)		{
/*
** Nastav� aktivitu seznamu L na jeho prvn� prvek.
** Funkci implementujte jako jedin� p��kaz, ani� byste testovali,
** zda je seznam L pr�zdn�.
**/

	L->Act = L->First;
}

void CopyFirst (tList *L, int *val)	{
/*
** Vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci Error().
**/

	//kontrola ci nieje zoznam prazdny
	if (L->First == NULL)
	{
		Error();
		return;
	}
	else
		//nastavenie hodnoty
		*val = L->First->data;
}

void DeleteFirst (tList *L)	{
/*
** Ru�� prvn� prvek seznamu L. Pokud byl ru�en� prvek aktivn�, aktivita seznamu
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je!
**/
	
	//ak je zoznam prazdny nic sa nedeje
	if (L->First == NULL)
		return;
	
	//ak bol aktivny tak ho deaktivuje
	if (L->First == L->Act)
		L->Act = NULL;
	
	//pomocny ukazatel sa nastavy na druhy prvok zoznamu
	tElemPtr item = L->First->ptr;
	//uvolni sa prvy
	free(L->First);
	//prvy sa nastavy na pomocny
	L->First = item;
}

void PostDelete (tList *L)			{
/* 
** Ru�� prvek seznamu L za aktivn�m prvkem. Pokud nen� seznam L aktivn�
** nebo pokud je aktivn� posledn� prvek seznamu L, nic se ned�je!
**/
	
	//skonci ak zoznam nie je Aktivny alebo ak je posledny v zozname
	if (L->Act == NULL || L->Act->ptr == NULL)
		return;
	
	//pomocny bude ukazovat na prvok za aktualnym ktory idem odstranit
	tElemPtr item = L->Act->ptr;
	//ukazatel v aktualnom bude ukazovat na prvok za odstranenym
	L->Act->ptr = item->ptr;
	//uvolnil som polozku za aktualnym
	free(item);
}

void PostInsert (tList *L, int val)	{
/*
** Vlo�� prvek s hodnotou val za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je!
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** zavol� funkci Error().
**/

	//ak zoznam nebol aktivny nic sa nespravi
	if(L->Act == NULL)
		return;
	
	//vytvori novy prvok a prideli mu pamet
	tElemPtr item = malloc(sizeof(struct tElem));
	//ak nema dostatok pameti zavola sa Error()
	if(item == NULL)
	{
		Error();
		return;
	}
	
	item->data = val;
	//ukazatel na dalsi prvok bude ukazovat kde ukazoval dalsi prvok po act
	item->ptr = L->Act->ptr;
	//ukazatel na dalsi prvok po aktualnom bude ukazovat na novy
	L->Act->ptr = item;
}

void Copy (tList *L, int *val)		{
/*
** Vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam nen� aktivn�, zavol� funkci Error().
**/
	
	if (L->Act == NULL)
	{
		Error();
		return;
	}
	else
		*val = L->Act->data;
}

void Actualize (tList *L, int val)	{
/*
** P�ep�e data aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic!
**/
	
	//ak zoznam je aktivny pokracuj
	if (L->Act != NULL)
		L->Act->data = val;
}

void Succ (tList *L)	{
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** V�imn�te si, �e touto operac� se m��e aktivn� seznam st�t neaktivn�m.
** Pokud seznam L nen� aktivn�, ned�l� nic!
**/
	
	//ak zoznam je aktivnny pokracuj
	if (L->Act != NULL)
		L->Act = L->Act->ptr;
}

int Active (tList *L) 	{		
/*
** Je-li seznam L aktivn�, vrac� True. V opa�n�m p��pad� vrac� false.
** Tuto funkci implementujte jako jedin� p��kaz return. 
**/
	
	return ((L->Act != NULL) ? TRUE : FALSE);
}

/* Konec c201.c */
