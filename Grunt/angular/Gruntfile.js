'use strict';

module.exports = function (grunt) {
	grunt.config.init({
		build: {
			angular: {
				src: [
					'bower_components/angular/angular.js',
					'bower_components/angular-resource/angular-resource.js'
				],
				dest: 'dist/angular.js'
			},
			angularWithJQuery: {
				src: [
					'bower_components/jquery/dist/jquery.js',
					'bower_components/angular/angular.js',
					'bower_components/angular-resource/angular-resource.js'
				],
				dest: 'dist/jquery-angular.js'
			},
			options: {
				separator: '\n;;\n'
			}
		}
	});

	grunt.registerMultiTask('build',
			'Concatenate files.', function () {
		var output = '';

		this.requiresConfig(this.name + '.options.separator');

		var separator = this.options().separator;
		var filegroup = this.data;

		grunt.log.writeln('Concatenating:');
		var sources = filegroup.src.map(function (file) {
			if (!grunt.file.exists(file)) {
				grunt.fatal('File ' + file + ' not found');
			}
			grunt.log.writeln('\t' + file);
			return grunt.file.read(file);
		});

		output = sources.join(separator);
		grunt.file.write(filegroup.dest, output);

		grunt.log.writeln('Output:');
		grunt.log.writeln('\t' + filegroup.dest);
	});
};
