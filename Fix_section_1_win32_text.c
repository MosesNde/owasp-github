 {
 	if ( !( sys ps = CreateCompatibleDC( NULL )))
 		return false;
	sys stock_font = GetCurrentObject( sys ps, OBJ_FONT);
 	return true;
 }
 
 void
 apc_font_end_query( Handle self )
 {
	SelectObject( sys ps, sys stock_font);
 	DeleteDC( sys ps );
 	sys ps = 0;
 }