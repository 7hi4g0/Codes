function [ r ] = pow(p, power, m)
	r = 1;

	while ( power > 0 )
		if ( mod (power, 2) == 1 )
			r = conv (r, p);
			r = norm (r, m);
			power = power - 1;
		end
		
		p = conv (p, p);
		p = norm (p, m);
		power = power / 2;
	end
end

function [ v ] = norm(p, m)
	l = length(m);

	[ ~, v ] = deconv(p, m);

	if ( length(v) > l )
		v = v(end - l + 2:end);
	end

	v = mod(v,2);
end
