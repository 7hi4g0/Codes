## Copyright (C) 2014 Thiago Dourado de Andrade
## 
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

## gfsr

## Author: Thiago Dourado de Andrade <thiago@thiago-Inspiron-5537>
## Created: 2014-01-29

function [ ret ] = gfsr (p, bits)

	if (nargin == 1)
		bits = 32;
	end

	state.base = p;
	state.length = length(p);
	%state.remainder = fliplr(eye(1, state.length));
	state.remainder = ones(1, state.length);
	state.bits = eye (1, bits + 1);
	
	ret = @() (state = next(state));
	
endfunction

function [ st ] = next(state)

	state.remainder = conv (state.remainder, [ 1 0 ]);
	[ ~, state.remainder ] = deconv (state.remainder, state.base);
	state.remainder = mod(state.remainder, 2)(end - state.length + 2:end);
	[ ~, state.val ] = deconv(state.remainder, state.bits);
	state.val = mod(state.val, 2);
	
	state.val = polyval(state.val, 2);

	st = state;

endfunction

