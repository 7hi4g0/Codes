function drawBspline(P, T, k, steps)
	n = length(P);
	m = length(T);

	if (nargin < 3)
		k = m - n;
	endif

	if (nargin < 4)
		steps = 1;
	endif

	step = (T(k + steps) - T(k)) / (150 * steps);

	t = [T(k) : step : T(k + steps)];
	X = zeros(1, length(t));
	Y = zeros(1, length(t));

	for i = 1:n
		F(i, :) = bs(i, 4, t);
		X += F(i, :) .* P(i, 1);
		Y += F(i, :) .* P(i, 2);
	endfor

	subplot(2, 2, 1);
	plot(t, Y);

	subplot(2, 2, 4);
	plot(X, t);

	subplot(2, 2, 2);
	plot(X, Y, "-b", P(:,1), P(:,2), "-+k");
endfunction
