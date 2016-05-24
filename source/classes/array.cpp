#include "FiveCpp.h"

//----------------------------------------------------------------------------//   		

TArray::TArray( void )
{
   pFirst  = NULL;
   pLast   = NULL;
   ulItems = 0;
}

//----------------------------------------------------------------------------//   		

void TArray::Add( TObject * pObj )
{
	 TArrayItem * pItem;
	
   if( ulItems == 0 )
   {
      pFirst = new TArrayItem;	
      pFirst->pObj = pObj;
      pFirst->pNext = NULL;
      pFirst->pPrev = NULL;
      pFirst->pArray = this;
      pLast = pFirst;
   }		
   else
   {
      pItem = pLast;
      pLast = new TArrayItem;
      pLast->pObj = pObj;
      pLast->pNext = NULL;
      pLast->pPrev = pItem;
      pLast->pArray = this;
      pItem->pNext = pLast;
   }
   
   ulItems++;      		
}	

//----------------------------------------------------------------------------//   		

TObject * TArray::GetItem( unsigned long ulItem )
{
   unsigned long ul = 0;
   TArrayItem * pItem = pFirst;
 
   if( ulItem > ulItems - 1 )
      return NULL;	 
   
   while( ul < ulItem && pItem->pNext )
   {		
      pItem = pItem->pNext;
      ul++;
   }   

   return pItem->pObj;
}	

//----------------------------------------------------------------------------//   		

TObject * TArray::operator[]( unsigned long ulItem )
{
   return GetItem( ulItem );
}  

//----------------------------------------------------------------------------//   		

TObject * TArray::Pop( void )
{
	 TArrayItem * pItem;
	
   if( ulItems > 0 )
   {
      pItem = pLast;
      pLast = pLast->pPrev;   			
   }
   
   if( --ulItems == 0 )
   {
      pFirst = NULL;
      pLast  = NULL;
   }
   
   return pItem->pObj;   		   
}

//----------------------------------------------------------------------------//   				       	