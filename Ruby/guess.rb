#! /usr/bin/env ruby

magic_number = rand(100)
right = false

puts "Guess the magic number:"

while not right do
	guess = gets.to_i
	if guess > magic_number
		puts "Too high"
	elsif guess < magic_number
		puts "Too low"
	else
		puts "Right!"
		right = true
	end
end
