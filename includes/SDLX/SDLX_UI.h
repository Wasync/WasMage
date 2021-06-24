#ifndef SDLX_UI_H
# define SDLX_UI_H
# include "SDLX/SDLX_structs.h"


SDLX_GUIElem *SDLX_GUIElem_Create(SDLX_Animator *animator, const char *name, SDLX_UIFunc OnSelectEnterFn,	SDLX_UIFunc OnSelectExitFn,
							SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickHeldFn, SDLX_UIFunc OnClickFn,	SDLX_UIFunc OnClickReleaseFn);
void			SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive);
void SDLX_GUIUpdate(void);

#endif
