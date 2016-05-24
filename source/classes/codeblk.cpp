#include "FiveCpp.h"

typedef void ( * PCODE )( void ); 

//----------------------------------------------------------------------------//

TCodeBlock::TCodeBlock( void * pNewCode )
{
   pCode = pNewCode;
}

//----------------------------------------------------------------------------//

void TCodeBlock::Eval( void )
{
   if( pCode )
      ( ( PCODE ) pCode )();
}

//----------------------------------------------------------------------------//      			