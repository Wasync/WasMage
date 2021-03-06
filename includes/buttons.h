#ifndef BUTTONS_H
# define BUTTONS_H

// Menu
int MenuEnterHover(SDLX_GUIElem *elem);
int MenuExitHover(SDLX_GUIElem *elem);
int StartClick(SDLX_GUIElem *elem);
int ExitClick(SDLX_GUIElem *elem);

int DrawButtonTrigger(SDLX_GUIElem *elem);
int DrawButtonHover(SDLX_GUIElem *elem);
int isHoverDraw(SDLX_GUIElem *elem);



#endif
