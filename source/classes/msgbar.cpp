#include "FiveCpp.h"

//----------------------------------------------------------------------------//

TMsgBar::TMsgBar( LPSTR szMsg, TObject * oWnd )
{
   static BOOL bInit = FALSE;
   
   this->oWnd = ( TWindow * ) oWnd; 

   if( ! bInit )
   {	
      bInit = TRUE; 
      InitCommonControls();
   }   

   Create( szMsg, ( TWindow * ) oWnd );
   
   ( ( TWindow * ) oWnd )->oMsgBar = this; 
}

//----------------------------------------------------------------------------//

void TMsgBar::AdjustBottom( void )
{
   RECT rctParent;
   RECT rct;
   
   GetClientRect( oWnd->hWnd, &rctParent );
   GetWindowRect( hWnd, &rct );
   
   rct.top   = rctParent.bottom - ( rct.bottom - rct.top );
   rct.right = rctParent.right;
   
   MoveWindow( hWnd, rct.left, rct.top, rct.right - rct.left, rct.bottom - rct.top, TRUE );		
}

//----------------------------------------------------------------------------//

void TMsgBar::Create( LPSTR szMsg, TWindow * oWnd )
{
   hWnd = CreateWindow( "msctls_statusbar32", szMsg, WS_CHILD | WS_VISIBLE,
                        0, oWnd->GetHeight() - 40, oWnd->GetWidth(), 40,
                        oWnd->hWnd, NULL, GetModuleHandle( NULL ), 0 );
}

//----------------------------------------------------------------------------//

TMsgBar * DefineMsgBar( LPSTR szMsg, local &oWnd )
{
   return new TMsgBar( szMsg, oWnd.pObj );
}

//----------------------------------------------------------------------------//