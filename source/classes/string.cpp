#include "FiveCpp.h"

//----------------------------------------------------------------------------//

TString::TString( char * szString )
{
   pszString = new char[ strlen( szString ) + 1 ];
   
   strcpy( pszString, szString );
}

//----------------------------------------------------------------------------//

unsigned long TString::Len( void )
{
   return strlen( pszString );
}

//----------------------------------------------------------------------------//   		