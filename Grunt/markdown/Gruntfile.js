'use strict';

module.exports = function (grunt) {
	var livereloadPort = 35729;

	grunt.loadNpmTasks('grunt-contrib-coffee');
	grunt.config('coffee', {
		app: {
			options: {
				bare: false
			},
			files: {
				'tmp/compiled.js': ['coffeescript/app.coffee',
									'coffeescript/factories/*.coffee',
									'coffeescript/controllers/*.coffee']
			}
		}
	});

	grunt.loadNpmTasks('grunt-contrib-concat');
	grunt.config('concat', {
		scripts: {
			src: [	'bower_components/angular/angular.js',
					'bower_components/angular-sanitize/angular-sanitize.js',
					'bower_components/markdown/dist/markdown.js',
					'tmp/compiled.js'],
			dest: 'tmp/app.js'
		}
	});

	grunt.loadNpmTasks('grunt-contrib-uglify');
	grunt.config('uglify', {
		script: {
			files: {
				'assets/app.js': 'tmp/app.js'
			}
		}
	});

	grunt.loadNpmTasks('grunt-contrib-sass');
	grunt.config('sass', {
		app: {
			files: {
				'tmp/app.css': ['sass/style.scss']
			}
		}
	});

	grunt.loadNpmTasks('grunt-contrib-cssmin');
	grunt.config('cssmin', {
		app: {
			files: {
				'assets/app.css': ['tmp/app.css']
			}
		}
	});

	grunt.loadNpmTasks('grunt-coffeelint');
	grunt.config('coffeelint', {
		app: ['coffeescript/**/*.coffee']
	});

	grunt.loadNpmTasks('grunt-contrib-connect');
	grunt.config('connect', {
		options: {
			port: 9000,
			hostname: 'localhost'
		},
		livereload: {
			options: {
				livereload: livereloadPort,
				open: true
			}
		}
	});

	grunt.loadNpmTasks('grunt-contrib-watch');
	grunt.config('watch', {
		scripts: {
			files: ['coffeescript/**/*.coffee'],
			tasks: ['coffee', 'concat', 'uglify'],
			options: {
				spawn: false
			}
		},
		styles: {
			files: ['sass/**/*.scss'],
			tasks: ['sass', 'cssmin'],
			options: {
				spawn: false
			}
		},
		interface: {
			files: ['index.html']
		},
		options: {
			livereload: true
		}
	});

	grunt.registerTask('build',
			'Builds application.',
			['coffeelint', 'coffee', 'concat:scripts', 'sass', 'cssmin', 'uglify']);

	grunt.registerTask('server',
			'Initiates a server for the application.',
			['build', 'connect:livereload', 'watch']);
};
