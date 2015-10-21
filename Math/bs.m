function [ret] = bs(i, k, t)
	global T;
	if (k == 1)
		ret = arrayfun(@inRange, T(i), T(i + 1), t);
	else
		ret = ((t - T(i)) / (T(i + k - 1) - T(i))) .* bs(i, k - 1, t) + ((T(i + k) - t) / (T(i + k) - T(i + 1))) .* bs(i + 1, k - 1, t);
	endif
endfunction

function [ret] = inRange(t1, t2, t)
	if (t >= t1 && t < t2)
		ret = 1;
	else
		ret = 0;
	endif
endfunction
