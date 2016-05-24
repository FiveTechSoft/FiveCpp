#include "FiveCpp.h"

static TArray * aMenus = NULL;

//----------------------------------------------------------------------------//   	

TMenuItem::TMenuItem( LPSTR szPrompt )
{
   this->szPrompt = new TString( szPrompt );
}

//----------------------------------------------------------------------------//   	

TMenu::TMenu( void )
{
   hMenu = CreateMenu();
   
   aItems = new TArray;
}

//----------------------------------------------------------------------------//   	

TMenu::TMenu( BOOL bPopup )
{
   if( bPopup )
      hMenu = CreatePopupMenu();
   else
      hMenu = CreateMenu();
      
   aItems = new TArray;    	   
}

//----------------------------------------------------------------------------//   	

TMenuItem * TMenu::Add( LPSTR szPrompt )
{
   TMenuItem * oMenuItem = new TMenuItem( szPrompt );
   
   oMenuItem->oMenu = this;
   
   aItems->Add( oMenuItem );
   
   return oMenuItem;
}  

//----------------------------------------------------------------------------//   	

void TWindow::SetMenu( local * oMenu )
{ 
   this->oMenu = ( TMenu * ) oMenu->pObj; 
   
   ::SetMenu( hWnd, this->oMenu->hMenu ); 
}

//----------------------------------------------------------------------------//   	
   	
local * MENU( void )
{
   local * oMenu = new local;
   
   return MENU( oMenu );
}	

//----------------------------------------------------------------------------//   	

local * MENU( local * oMenu )
{
   oMenu->pObj = new TMenu();	 

   if( aMenus == NULL )
      aMenus = new TArray;
      	
   aMenus->Add( oMenu->pObj );
   
   return oMenu;
}

//----------------------------------------------------------------------------//   	

local * MENU( LPSTR szPrompt )
{
   TMenu * oMenu = new TMenu( TRUE );
   
   oMenu->Add( szPrompt );	
   
   if( aMenus == NULL )
      aMenus = new TArray;
      	
   aMenus->Add( oMenu );
   
   return new local( oMenu );
}   

//----------------------------------------------------------------------------//   	

local * MENUITEM( LPSTR szPrompt )
{
   TMenu * oMenu = ( TMenu * ) aMenus->Last();

   if( oMenu )
      return new local( oMenu->Add( szPrompt ) );
   else
   	  return NULL;   			
}		

//----------------------------------------------------------------------------//   	

void ENDMENU( void )
{
   // if( aMenus->Len() > 1 )
   // {	
      TMenu * oMenu = ( TMenu * ) aMenus->Pop();	   	
      int id = 100;   
      
      for( unsigned long ul = 0; ul < oMenu->aItems->Len(); ul++ )
      {
         TMenuItem * pItem = ( TMenuItem * ) oMenu->aItems->GetItem( ul );

         AppendMenu( oMenu->hMenu, MF_ENABLED, id += 10, pItem->szPrompt->pszString );	
      }
   // }   

   /*
   TMenu * oParent = ( TMenu * ) aMenus->Last();
   TMenuItem * oItem = ( TMenuItem * ) oMenu->aItems->Last();   		   
      
   AppendMenu( oParent->hMenu, MF_ENABLED | MF_POPUP, ( UINT_PTR ) oMenu->hMenu, 
               oItem->szPrompt->pszString );	
   */            
}	      

//----------------------------------------------------------------------------//   	        		 		