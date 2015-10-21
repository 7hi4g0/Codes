#! /usr/bin/env ruby

class Tree
	attr_accessor :children, :node_name

	def initialize(struct)
		@node_name = struct.keys[0]
		@children = struct[@node_name].collect {|n, c| self.class.new({ n => c }) }
	end

	def visit_all(&block)
		visit &block
		children.each {|c| c.visit_all &block}
	end

	def visit(&block)
		block.call self
	end
end

ruby_tree = Tree.new({
	"Ruby" => {
		"Reia" => {},
		"McRuby" => {}
	}
})

puts "visiting a node"
ruby_tree.visit {|node| puts node.node_name}
puts

puts "visiting entire tree"
ruby_tree.visit_all {|node| puts node.node_name}
