#include "FiveCpp.h"

function Click( void );

//----------------------------------------------------------------------------//

function Main()
{
   local oWnd = DefineWindow( "Hello world!" );
   local oBar = DefineMsgBar( "Main message", oWnd );

   oWnd.OnClick( Click );

   oWnd.Activate();
}

//----------------------------------------------------------------------------//

function Click( void )
{
   MsgInfo( "Click" );
}

//----------------------------------------------------------------------------//   	