     SDL_Rect dest = { x, y, w, h };
     SDL_RenderCopy(active_rend, tex, NULL, &dest);
     SDL_RenderPresent(active_rend);
   }
   return true;
 }