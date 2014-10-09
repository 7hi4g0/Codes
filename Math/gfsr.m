function [ ret ] = gfsr ( p, q, delay, bits )

	state.primitive = zeros ( p );
	state.primitive ( 2 : end, 1 : end - 1 ) = eye ( p - 1 );
	state.primitive ( 1, end ) = 1;
	state.primitive ( q + 1, end ) = 1;

	state.values = zeros ( bits, p );
	state.values ( 1, : ) = ones ( 1, p );

	delay = pow ( state.primitive, delay );

	for i = 2:bits
		state.values ( i, : ) = mod ( state.values ( i - 1, : ) * delay, 2 );
	end

	delay = pow ( state.primitive, ( p * 5000 ) );
	state.values = mod ( state.values * delay, 2 );

	ret = @() ( state = next ( state ) ).val;

end

function [ new ] = next ( s )

	s.values = mod ( s.values * s.primitive, 2 );

	s.val = polyval ( s.values ( :, 1 ), 2 );

	new = s;

end

function [ r ] = pow( m, power )
	r = eye ( size ( m ) );
	while ( power > 0 )
		if ( mod ( power, 2 ) == 1 )
			r = mod ( r * m, 2 );
			power = power - 1;
		end

		m = mod ( m * m, 2 );
		power = power / 2;
	end
end
