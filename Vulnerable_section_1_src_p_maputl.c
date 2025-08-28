 	INT32 flags, traverser_t trav)
 {
 	fixed_t xt1, yt1, xt2, yt2;
	fixed_t xstep, ystep, partial, xintercept, yintercept;
 	INT32 mapx, mapy, mapxstep, mapystep, count;
 
 	earlyout = flags & PT_EARLYOUT;
 
 	validcount++;
 	intercept_p = intercepts;

 	if (((px1 - bmaporgx) & (MAPBLOCKSIZE-1)) == 0)
 		px1 += FRACUNIT; // Don't side exactly on a line.
 
 	trace.dx = px2 - px1;
 	trace.dy = py2 - py1;
 
	px1 -= bmaporgx;
	py1 -= bmaporgy;
	xt1 = (unsigned)px1>>MAPBLOCKSHIFT;
	yt1 = (unsigned)py1>>MAPBLOCKSHIFT;
 
	px2 -= bmaporgx;
	py2 -= bmaporgy;
	xt2 = (unsigned)px2>>MAPBLOCKSHIFT;
	yt2 = (unsigned)py2>>MAPBLOCKSHIFT;
 
 	if (xt2 > xt1)
 	{
 		mapxstep = 1;
		partial = FRACUNIT - ((px1>>MAPBTOFRAC) & FRACMASK);
 		ystep = FixedDiv(py2 - py1, abs(px2 - px1));
 	}
 	else if (xt2 < xt1)
 	{
 		mapxstep = -1;
		partial = (px1>>MAPBTOFRAC) & FRACMASK;
 		ystep = FixedDiv(py2 - py1, abs(px2 - px1));
 	}
 	else
 	{
 		mapxstep = 0;
		partial = FRACUNIT;
 		ystep = 256*FRACUNIT;
 	}
 
	yintercept = (py1>>MAPBTOFRAC) + FixedMul(partial, ystep);
 
 	if (yt2 > yt1)
 	{
 		mapystep = 1;
		partial = FRACUNIT - ((py1>>MAPBTOFRAC) & FRACMASK);
 		xstep = FixedDiv(px2 - px1, abs(py2 - py1));
 	}
 	else if (yt2 < yt1)
 	{
 		mapystep = -1;
		partial = (py1>>MAPBTOFRAC) & FRACMASK;
 		xstep = FixedDiv(px2 - px1, abs(py2 - py1));
 	}
 	else
 	{
 		mapystep = 0;
		partial = FRACUNIT;
 		xstep = 256*FRACUNIT;
 	}
	xintercept = (px1>>MAPBTOFRAC) + FixedMul(partial, xstep);
 
 	// Step through map blocks.
 	// Count is present to prevent a round off error
 		if (flags & PT_ADDTHINGS)
 			if (!P_BlockThingsIterator(mapx, mapy, PIT_AddThingIntercepts))
 				return false; // early out

		if (mapx == xt2 && mapy == yt2)
 			break;

		if ((yintercept >> FRACBITS) == mapy)
		{
			yintercept += ystep;
			mapx += mapxstep;
		}
		else if ((xintercept >> FRACBITS) == mapx)
 		{
			xintercept += xstep;
			mapy += mapystep;
 		}
 	}
 	// Go through the sorted list
 	return P_TraverseIntercepts(trav, FRACUNIT);
 }