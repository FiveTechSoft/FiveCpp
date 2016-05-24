#include "FiveCpp.h"

//----------------------------------------------------------------------------//

void local::operator=( TObject * pObject )
{
   pObj = pObject;
   
   strcpy( type, "O" );
}

//----------------------------------------------------------------------------//

void local::operator=( char * szString )
{
   pString = new TString( szString );
   
   strcpy( type, "C" );
}

//----------------------------------------------------------------------------//