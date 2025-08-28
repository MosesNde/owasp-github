 {
 	if ( !( sys ps = CreateCompatibleDC( NULL )))
 		return false;
 	return true;
 }
 
 void
 apc_font_end_query( Handle self )
 {
 	DeleteDC( sys ps );
 	sys ps = 0;
 }