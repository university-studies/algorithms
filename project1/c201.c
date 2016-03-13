
/* c201.c *********************************************************************}
{* Téma: Jednosmìrný lineární seznam
**
**                     Návrh a referenèní implementace: Petr Pøikryl, øíjen 1994
**                                          Úpravy: Andrea Nìmcová listopad 1996
**                                                   Petr Pøikryl, listopad 1997
**                                Pøepracované zadání: Petr Pøikryl, bøezen 1998
**                                  Pøepis do jazyka C: Martin Tuèek, øíjen 2004
**	                                          Úpravy: Bohuslav Køena, øíjen 2010
**
** Implementujte abstraktní datový typ jednosmìrný lineární seznam.
** U¾iteèným obsahem prvku seznamu je celé èíslo typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou typu tList.
** Definici konstant a typù naleznete v hlavièkovém souboru c201.h.
** 
** Va¹ím úkolem je implementovat následující operace, které spolu s vý¹e
** uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DisposeList ... zru¹ení v¹ech prvkù seznamu,
**      InsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zru¹í první prvek seznamu,
**      PostDelete .... ru¹í prvek za aktivním prvkem,
**      PostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal¹í prvek seznamu,
**      Active ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci funkcí nevolejte ¾ádnou z funkcí implementovaných v rámci
** tohoto pøíkladu, není-li u funkce explicitnì uvedeno nìco jiného.
**
** Nemusíte o¹etøovat situaci, kdy místo legálního ukazatele na seznam 
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error()	{
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/	
    printf ("*ERROR* Chyba pøi práci se seznamem.\n");
    errflg = TRUE;                      /* globální promìnná -- pøíznak chyby */
}

void InitList (tList *L)	{
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/

	//inicializuje ukazatel na aktualny prvok na NULL
	L->Act = NULL;
	//inicializuje ukazatel na prvy prvok na NULL
	L->First = NULL;
}

void DisposeList (tList *L)	{
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. V¹echny prvky seznamu L budou korektnì uvolnìny voláním
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
** Vlo¾í prvek s hodnotou val na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci Error().
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
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný pøíkaz, ani¾ byste testovali,
** zda je seznam L prázdný.
**/

	L->Act = L->First;
}

void CopyFirst (tList *L, int *val)	{
/*
** Vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
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
** Ru¹í první prvek seznamu L. Pokud byl ru¹ený prvek aktivní, aktivita seznamu
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje!
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
** Ru¹í prvek seznamu L za aktivním prvkem. Pokud není seznam L aktivní
** nebo pokud je aktivní poslední prvek seznamu L, nic se nedìje!
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
** Vlo¾í prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje!
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** zavolá funkci Error().
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
** Vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
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
** Pøepí¹e data aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic!
**/
	
	//ak zoznam je aktivny pokracuj
	if (L->Act != NULL)
		L->Act->data = val;
}

void Succ (tList *L)	{
/*
** Posune aktivitu na následující prvek seznamu L.
** V¹imnìte si, ¾e touto operací se mù¾e aktivní seznam stát neaktivním.
** Pokud seznam L není aktivní, nedìlá nic!
**/
	
	//ak zoznam je aktivnny pokracuj
	if (L->Act != NULL)
		L->Act = L->Act->ptr;
}

int Active (tList *L) 	{		
/*
** Je-li seznam L aktivní, vrací True. V opaèném pøípadì vrací false.
** Tuto funkci implementujte jako jediný pøíkaz return. 
**/
	
	return ((L->Act != NULL) ? TRUE : FALSE);
}

/* Konec c201.c */
