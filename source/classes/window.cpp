#include "FiveCpp.h"

//----------------------------------------------------------------------------//

void WinRun( void )
{
   MSG msg;

   while( GetMessage( &msg, 0, 0, 0 ) )
   {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
   }
}

//----------------------------------------------------------------------------//

#pragma argsused

int CALLBACK WinMain( HINSTANCE hInst, HINSTANCE hPrev, char * szCmd, int iMode )
{
   Main();

   return 0;
}

//----------------------------------------------------------------------------//

LRESULT CALLBACK WndProc( HWND hWnd, WORD wMsg, WORD wParam, LONG lParam )
{
   TWindow * oWnd = ( TWindow * ) GetWindowLong( hWnd, GWL_USERDATA );
	
   switch( wMsg )
   {
   	  case WM_ERASEBKGND:
   	  	   if( oWnd )
   	  	      return oWnd->EraseBkGnd( ( HDC ) wParam );
   	  	   break;
   	  	      	
   	  case WM_LBUTTONDOWN:
   	  	   if( oWnd )
   	  	      oWnd->LButtonDown( LOWORD( lParam ), HIWORD( lParam ), wParam );	
   	  	   break;
   	  	   
      case WM_SIZE:
      	   if( oWnd && oWnd->oMsgBar )
      	   {
      	      oWnd->oMsgBar->AdjustBottom();
      	   }
      	   break;
      	   	
      case WM_DESTROY:
           PostQuitMessage( 0 );
           break;
   }
   
   return DefWindowProc( hWnd, wMsg, wParam, lParam );
}

//----------------------------------------------------------------------------//

BOOL TWindow::Register( void )
{
   static BOOL bRegistered;

   WNDCLASS cls;

   if( ! bRegistered )
   {
      cls.lpszClassName = "FWCPPTWindow";
      cls.style         = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
      cls.cbClsExtra    = 0;
      cls.cbWndExtra    = 0;
      cls.hInstance     = GetModuleHandle( NULL );
      cls.hIcon         = NULL;
      cls.hCursor       = NULL;
      cls.hbrBackground = CreateSolidBrush( GetSysColor( COLOR_WINDOW ) ); // GetStockObject( WHITE_BRUSH );
      cls.lpszMenuName  = 0;
      cls.lpfnWndProc   = ( WNDPROC ) WndProc;

      bRegistered = RegisterClass( &cls );
   }
   
   return bRegistered;
}

//----------------------------------------------------------------------------//

void TWindow::Create( LPSTR szTitle, TWindow * oWnd )
{
   if( oWnd == NULL )	
      hWnd = CreateWindow( szClsName, szTitle, WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                           CW_USEDEFAULT, 0, 0, GetModuleHandle( NULL ), 0 );
                           
   SetWindowLong( hWnd, GWL_USERDATA, ( LONG ) this );                        
}

//----------------------------------------------------------------------------//

TWindow::TWindow( LPSTR szTitle )
{
   hWnd = 0;
   szClsName = "FWCPPTWindow";
   
   if( szTitle == NULL )
      szTitle = "FiveCpp"; 

   if( Register() )
      Create( szTitle, NULL );
}

//----------------------------------------------------------------------------//

void TWindow::Activate( void )
{
   ShowWindow( hWnd, SW_NORMAL );
   UpdateWindow( hWnd );

   if( hWnd )
      WinRun();
}

//----------------------------------------------------------------------------//

TWindow * DefineWindow( LPSTR szTitle )
{
   return new TWindow( szTitle );
}

//----------------------------------------------------------------------------//

#pragma argsused

int TWindow::EraseBkGnd( HDC hDc )
{
   RECT rct;
   HDC hDC = GetDC( hWnd ); // it is working fine, creating a new hDC
   	  	      
   GetClientRect( hWnd, &rct );
   FillRect( hDC, &rct, ( HBRUSH ) GetClassLong( hWnd, GCL_HBRBACKGROUND ) ); // GetStockObject( WHITE_BRUSH ) );
   ReleaseDC( hWnd, hDC );

   return 1;
}

//----------------------------------------------------------------------------//

#pragma argsused 

void TWindow::LButtonDown( int iTop, int iLeft, WORD wFlags )
{	
   if( bOnClick )
      bOnClick->Eval();
}

//----------------------------------------------------------------------------//
	
void TWindow::Refresh( void )
{
   InvalidateRect( hWnd, NULL, TRUE );
}   		

//----------------------------------------------------------------------------//

void TWindow::SetTop( LONG lNewTop )
{
   RECT rct;
      
   GetWindowRect( hWnd, &rct );
   MoveWindow( hWnd, rct.left, lNewTop, rct.right - rct.left, rct.bottom - rct.top, TRUE );
}		
	
//----------------------------------------------------------------------------//	

void TWindow::SetWidth( LONG lNewWidth )
{
   RECT rct;
      
   GetWindowRect( hWnd, &rct );
   MoveWindow( hWnd, rct.left, rct.top, lNewWidth, rct.bottom - rct.top, FALSE );
}   

//----------------------------------------------------------------------------//		

LONG TWindow::GetHeight( void )
{
   RECT rct;
      
   GetWindowRect( hWnd, &rct );

   return rct.bottom - rct.top;
}   

//----------------------------------------------------------------------------//		

LONG TWindow::GetTop( void )
{
   RECT rct;
      
   GetWindowRect( hWnd, &rct );

   return rct.top;
}   

//----------------------------------------------------------------------------//		

LONG TWindow::GetWidth( void )
{
   RECT rct;
      
   GetWindowRect( hWnd, &rct );

   return rct.right - rct.left;
}   

//----------------------------------------------------------------------------//		