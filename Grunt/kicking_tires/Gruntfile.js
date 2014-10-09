"use strict";

module.exports = function (grunt) {
	grunt.registerTask('default',
			'Prints a welcome message.', function () {
		grunt.log.writeln('Hello from Grunt.');
	});

	grunt.registerTask('greet',
			'Greets the user.', function (name) {
		grunt.log.writeln('Hi there, ' + name + '.');
	});

	grunt.registerTask('addNumbers',
			'Adds two numbers.', function (first, second) {
		var sum,
			_first,
			_second;

		_first = Number(first);
		_second = Number(second);

		if (isNaN(_first)) {
			grunt.warn('The first argument must be a number.');
		}

		if (isNaN(_second)) {
			grunt.warn('The second argument must be a number.');
		}

		sum = _first + _second;
		grunt.log.writeln(first + ' + ' + second + ' is ' + sum);
	});

	grunt.registerTask('multiplyNumbers',
			'Multiply two numbers.', function (first, second) {
		var product,
			_first,
			_second;
		
		_first = Number(first);
		_second = Number(second);

		if (isNaN(_first)) {
			grunt.warn('The first argument must be a number.');
		}

		if (isNaN(_second)) {
			grunt.warn('The second argument must be a number.');
		}

		product = _first * _second;
		grunt.log.writeln(first + ' * ' + _second + ' is ' + product);
	});

	grunt.registerTask('all',
			'Shows all of my new tricks.',
			['default', 'greet:Thiago', 'addNumbers:2:3', 'multiplyNumbers:3:4', 'praise']);

	grunt.registerTask('praise',
			'Have Grunt say nice things about you.', function () {
		var praise,
			pick;
		
		praise = [
			"You're awesome.",
			"You're the best developer ever!",
			"You are extremely attractive.",
			"Everyone loves you!"
		];

		pick = praise[Math.floor(Math.random() * praise.length)];

		grunt.log.writeln(pick);
	});
};
