#include "FiveCpp.h"

//----------------------------------------------------------------------------//

int MsgInfo( char * szMsg, char * szTitle )
{
   return MessageBox( GetActiveWindow(), szMsg, szTitle, MB_ICONINFORMATION );
}

//----------------------------------------------------------------------------//