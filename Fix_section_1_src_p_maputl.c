 	INT32 flags, traverser_t trav)
 {
 	fixed_t xt1, yt1, xt2, yt2;
	fixed_t xstep, ystep, partialx, partialy, xintercept, yintercept;
 	INT32 mapx, mapy, mapxstep, mapystep, count;
 
 	earlyout = flags & PT_EARLYOUT;
 
 	validcount++;
 	intercept_p = intercepts;
	
 	if (((px1 - bmaporgx) & (MAPBLOCKSIZE-1)) == 0)
 		px1 += FRACUNIT; // Don't side exactly on a line.
 
 	trace.dx = px2 - px1;
 	trace.dy = py2 - py1;
 
	xt1 = px1>>MAPBLOCKSHIFT;
	yt1 = py1>>MAPBLOCKSHIFT;
	px1 = (unsigned)(px1 - bmaporgx);
	py1 = (unsigned)(py1 - bmaporgy);
 
	xt2 = px2>>MAPBLOCKSHIFT;
	yt2 = py2>>MAPBLOCKSHIFT;
	px2 = (unsigned)(px2 - bmaporgx);
	py2 = (unsigned)(py2 - bmaporgy);
 
 	if (xt2 > xt1)
 	{
 		mapxstep = 1;
		partialx = FRACUNIT - (((unsigned)px1>>MAPBTOFRAC) & FRACMASK);
 		ystep = FixedDiv(py2 - py1, abs(px2 - px1));
 	}
 	else if (xt2 < xt1)
 	{
 		mapxstep = -1;
		partialx = ((unsigned)px1>>MAPBTOFRAC) & FRACMASK;
 		ystep = FixedDiv(py2 - py1, abs(px2 - px1));
 	}
 	else
 	{
 		mapxstep = 0;
		partialx = FRACUNIT;
 		ystep = 256*FRACUNIT;
 	}
 
	yintercept = ((unsigned)py1>>MAPBTOFRAC) + FixedMul(partialx, ystep);
 
 	if (yt2 > yt1)
 	{
 		mapystep = 1;
		partialy = FRACUNIT - (((unsigned)py1>>MAPBTOFRAC) & FRACMASK);
 		xstep = FixedDiv(px2 - px1, abs(py2 - py1));
 	}
 	else if (yt2 < yt1)
 	{
 		mapystep = -1;
		partialy = ((unsigned)py1>>MAPBTOFRAC) & FRACMASK;
 		xstep = FixedDiv(px2 - px1, abs(py2 - py1));
 	}
 	else
 	{
 		mapystep = 0;
		partialy = FRACUNIT;
 		xstep = 256*FRACUNIT;
 	}
	xintercept = ((unsigned)px1>>MAPBTOFRAC) + FixedMul(partialy, xstep);
	
	// [RH] Fix for traces that pass only through blockmap corners. In that case,
	// xintercept and yintercept can both be set ahead of mapx and mapy, so the
	// for loop would never advance anywhere.
	
	if (abs(xstep) == 1 && abs(ystep) == 1)
	{
		if (ystep < 0)
		{
			partialx = FRACUNIT - partialx;
		}
		if (xstep < 0)
		{
			partialy = FRACUNIT - partialy;
		}
		if (partialx == partialy)
		{
			xintercept = xt1;
			yintercept = yt1;
		}
	}
	
	xt1 = (unsigned)px1>>MAPBLOCKSHIFT;
	yt1 = (unsigned)py1>>MAPBLOCKSHIFT;
	xt2 = (unsigned)px2>>MAPBLOCKSHIFT;
	yt2 = (unsigned)py2>>MAPBLOCKSHIFT;
 
 	// Step through map blocks.
 	// Count is present to prevent a round off error
 		if (flags & PT_ADDTHINGS)
 			if (!P_BlockThingsIterator(mapx, mapy, PIT_AddThingIntercepts))
 				return false; // early out
		
		// both coordinates reached the end, so end the traversing.
		if ((mapxstep | mapystep) == 0)
 			break;
		
		
		// [RH] Handle corner cases properly instead of pretending they don't exist.
		switch ((((yintercept >> FRACBITS) == mapy) << 1) | ((xintercept >> FRACBITS) == mapx))
 		{
			case 0: // neither xintercept nor yintercept match!
				count = 64; // Stop traversing, because somebody screwed up.
				break;
			
			case 1: // xintercept matches
				xintercept += xstep;
				mapy += mapystep;
				if (mapy == yt2)
					mapystep = 0;
				break;
			
			case 2: // yintercept matches
				yintercept += ystep;
				mapx += mapxstep;
				if (mapx == xt2)
					mapxstep = 0;
				break;
			
			case 3: // xintercept and yintercept both match
				// The trace is exiting a block through its corner. Not only does the block
				// being entered need to be checked (which will happen when this loop
				// continues), but the other two blocks adjacent to the corner also need to
				// be checked.
				if (flags & PT_ADDLINES)
				{
					if (!P_BlockLinesIterator(mapx + mapxstep, mapy, PIT_AddLineIntercepts))
						return false; // early out
					if (!P_BlockLinesIterator(mapx, mapy + mapystep, PIT_AddLineIntercepts))
						return false; // early out
				}
				
				if (flags & PT_ADDTHINGS)
				{
					if (!P_BlockThingsIterator(mapx + mapxstep, mapy, PIT_AddThingIntercepts))
						return false; // early out
					if (!P_BlockThingsIterator(mapx, mapy + mapystep, PIT_AddThingIntercepts))
						return false; // early out
				}
				
				xintercept += xstep;
				yintercept += ystep;
				mapx += mapxstep;
				mapy += mapystep;
				if (mapx == xt2)
					mapxstep = 0;
				if (mapy == yt2)
					mapystep = 0;
				break;
 		}
 	}
	
 	// Go through the sorted list
 	return P_TraverseIntercepts(trav, FRACUNIT);
 }