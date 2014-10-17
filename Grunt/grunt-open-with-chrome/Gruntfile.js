'use strict';

module.exports = function (grunt) {
	grunt.loadTasks('tasks');

	grunt.loadNpmTasks('grunt-contrib-jshint');
	grunt.config('jshint', {
		all: [
			'Gruntfile.js',
			'tasks/**/*.js'
		],
		options: {
			jshintrc: '.jshintrc'
		}
	});
};
