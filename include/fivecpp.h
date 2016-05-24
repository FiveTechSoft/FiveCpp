#include <windows.h>
#include <CommCtrl.h>

#define FWCPP_VERSION   "FiveCpp 1.0"

#define function void

void Main( void );

int MsgInfo( char * szMsg, char * szTitle = "Information" );

//----------------------------------------------------------------------------//

class TString
{
   public:
   char * pszString;
   
   TString( char * szString ); 
    
   unsigned long Len( void ); 	
};

//----------------------------------------------------------------------------//

class TCodeBlock;

class TObject
{
   public:
   TCodeBlock * bOnClick;

   virtual void Activate( void ) {}
};

//----------------------------------------------------------------------------//

class TCodeBlock
{
   public:
   void * pCode;
   
   TCodeBlock( void * pNewCode );	
   
   void Eval( void );
};

//----------------------------------------------------------------------------//

class TArray;

class TArrayItem : public TObject
{
   public:
   TArray * pArray;
   
   TArrayItem * pPrev;
   TArrayItem * pNext;
   TObject * pObj;
};   			

class TArray : public TObject
{
	 public:
	 TArray( void );
	 
	 TArrayItem * pFirst;
	 TArrayItem * pLast;
	 
	 unsigned long ulItems;
	 
   void Add( TObject * pObj );
   unsigned long Len( void ) { return ulItems; }
   TObject * GetItem( unsigned long ulItem );
   TObject * operator[] ( unsigned long ulItem );
   TObject * Last( void ) { return pLast ? pLast->pObj : NULL; }	
   	
   TObject * Pop( void );	
};		

//----------------------------------------------------------------------------//

class TMenu;
class local;

class TMenuItem : public TObject
{
   public:
   TString * szPrompt;
   TMenu * oMenu;
   
   TMenuItem();
   TMenuItem( LPSTR szPrompt );
};   	

class TMenu : public TObject
{
   public:
   HMENU hMenu;
   TArray * aItems;

   TMenu();
   TMenu( BOOL bPopup );
   TMenu( LPSTR szResName );
   
   TMenuItem * Add( LPSTR szPrompt );
};         

local * MENU( void );
local * MENU( local * oVar );
local * MENU( LPSTR szPrompt );
local * MENUITEM( LPSTR szPrompt );
void ENDMENU( void );   		

//----------------------------------------------------------------------------//

class TMsgBar;

class TWindow : public TObject
{
   public:
   HWND hWnd;
   LPSTR szClsName;
   TMsgBar * oMsgBar;
   TCodeBlock * bOnClick;
   TMenu * oMenu;

   TWindow() {}
   TWindow( LPSTR szTitle );

   void Activate( void );
   BOOL Register( void );
   virtual void Create( LPSTR szTitle, TWindow * oWnd );

   virtual int EraseBkGnd( HDC hDC ); 
   
   virtual void LButtonDown( int iTop, int iLeft, WORD wFlags );

   LONG SendMsg( WORD wMsg, WORD wParam, LONG lParam )
   {
      return SendMessage( hWnd, wMsg, wParam, lParam );
   }

   void Refresh( void );

   void SetMenu( local * oMenu );
   // void SetMenu( local oMenu ) { this->oMenu = ( TMenu * ) &oMenu.pObj; ::SetMenu( hWnd, ( ( TMenu * ) &oMenu.pObj )->hMenu ); }
   	
   // void SetMenu( local * oVar ) { SetMenu( ( TMenu * ) oVar->pObj ); } 	
   	
   void SetTop( LONG lNewTop ); 
   
   LONG GetHeight( void );
   
   LONG GetTop( void );

   LONG GetWidth( void );

   void SetWidth( LONG lNewWidth );       	 	
};

TWindow * DefineWindow( LPSTR szTitle );

//----------------------------------------------------------------------------//

class local : public TObject
{
   public:
   TObject * pObj;
   char type[ 2 ];

   local( void ) { pObj = 0; }

   local( TObject * pObject ) { pObj = pObject; }

   void operator=( TObject * pObject ) { pObj = pObject; }

   void Activate( void ) { pObj->Activate(); }
   
   void OnClick( TCodeBlock * oAction ) { ( ( TObject * ) pObj )->bOnClick = oAction; }
   
   void OnClick( void * pCode ) { ( ( TWindow * ) pObj )->bOnClick = new TCodeBlock( pCode ); }
   
   void SetMenu( local * oMenu ) { ( ( TWindow * ) pObj )->SetMenu( oMenu ); }
};

//----------------------------------------------------------------------------//

class TMsgBar : public TWindow
{
   public:
   TWindow * oWnd;	
   	
   TMsgBar( LPSTR szMsg, TObject * oWnd );
   	
   virtual void Create( LPSTR szMsg, TWindow  * oWnd );
   void AdjustBottom( void );
};

TMsgBar * DefineMsgBar( LPSTR szMsg, local &oWnd );

//----------------------------------------------------------------------------//