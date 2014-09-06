function rndPlot(rnd, length)
	
	if (nargin == 1)
		length = 3000;
	end

	x = zeros(1, length);
	y = zeros(1, length);
	z = zeros(1, length);
	
	for i = 1:length
		x(i) = rnd();
		y(i) = rnd();
		z(i) = rnd();
	end

	plot3(x, y, z, 's');

endfunction
