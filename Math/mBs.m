function [ret] = mBs(i, k)
	global T;

	if (k == 1)
		if (i == 4)
			ret = [0 0 0 1];
		else
			ret = [0 0 0 0];
		endif
	else
		ret = conv([0 0 1 -T(i)] / (T(i + k - 1) - T(i)), mBs(i, k - 1)) + conv([0 0 -1 T(i + k)] / (T(i + k) - T(i + 1)), mBs(i + 1, k - 1));
	endif
endfunction
