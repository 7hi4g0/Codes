#! /usr/bin/env ruby

filename = ARGV[0]
string = ARGV[1]

File.open(filename, 'r') do |f|
	line_num = 1
	f.each do |line|
		if line
			puts "#{line_num}: #{line}" if line.include? string
		end
		line_num += 1
	end
end
