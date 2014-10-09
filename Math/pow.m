function [ r ] = pow(p, power, m, base)
	
	if ( nargin < 4 )
		base = 0;
	end

	r = 1;

	while ( power > 0 )
		if ( mod (power, 2) == 1 )
			r = conv (r, p);
			r = norm (r, m, base);
			power = power - 1;
		end
		
		p = conv (p, p);
		p = norm (p, m, base);
		power = power / 2;
	end
end

function [ v ] = norm(p, m, base)
	l = length(m);

	[ ~, v ] = deconv(p, m);

	if ( length(v) > l )
		v = v(end - l + 2:end);
	end
	
	if ( base > 1 )
		v = mod(v, base);
	end
end
