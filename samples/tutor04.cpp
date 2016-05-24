#include "FiveCpp.h"

local * BuildMenu( void );
function Click( void );

//----------------------------------------------------------------------------//

function Main()
{
   local oWnd  = DefineWindow( "Hello world!" );
   local oBar  = DefineMsgBar( "Main message", oWnd );

   oWnd.SetMenu( BuildMenu() );

   oWnd.OnClick( Click );

   oWnd.Activate();
}

//----------------------------------------------------------------------------//

function Click( void )
{
   MsgInfo( "Click" );
}

//----------------------------------------------------------------------------//   	

local * BuildMenu( void )
{
	 local * oMenu = new local;
	 
	 MENU( oMenu );
	    MENUITEM( "First" );
	    MENU();
	       MENUITEM( "one" );
	       MENUITEM( "two" );
	       MENUITEM( "third" );
	    ENDMENU();
	    
	    MENUITEM( "Second" );
	    MENU();    
	       MENUITEM( "one" );
	       MENUITEM( "two" );
	       MENUITEM( "third" );
	    ENDMENU();

	    MENUITEM( "Third" );    
   ENDMENU();
   
   return oMenu;
}   	

//----------------------------------------------------------------------------//   	