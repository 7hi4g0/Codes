#! /usr/bin/env ruby

module ActsAsCsv
	def self.included(base)
		base.extend ClassMethods
	end

	module ClassMethods
		def acts_as_csv
			include InstanceMethods
		end
	end

	module InstanceMethods

		class CsvRow
			attr_accessor :csv_file, :row

			def initialize(csv, row)
				@csv_file = csv
				@row = row
			end

			def method_missing name, *args
				index = @csv_file.headers.index name.to_s
				@row[index] if index
			end
		end

		def read
			@csv_contents = []
			filename = self.class.to_s.downcase + '.txt'
			file = File.new(filename)
			@headers = file.gets.chomp.split(', ')

			file.each do |row|
				@csv_contents << CsvRow.new(self, row.chomp.split(', '))
			end
		end

		def each(&block)
			csv_contents.each {|row| block.call row }
		end

		attr_accessor :headers, :csv_contents
		def initialize
			read
		end
	end
end

class RubyCsv
	include ActsAsCsv
	acts_as_csv
end

m = RubyCsv.new

m.each {|row| puts row.one}
