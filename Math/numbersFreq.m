function [ f ] = numbersFreq ( freqs, xs )
	f = zeros (1, length (xs));
	for freq = freqs
		f = f + (2 * sin(xs * pi / freq) / freq);
	end
	f = f / freqs(end);
end
