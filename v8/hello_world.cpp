#include "/home/thiago/src/v8/include/v8.h"
#include <iostream>

using namespace v8;

int main(int argc, char* argv[]) {
	// Get the default Isolate created at startup.
	Isolate* isolate = Isolate::GetCurrent();

	// Create a stack-allocated handle scope.
	HandleScope handle_scope(isolate);

	// Create a new context.
	Handle<Context> context = Context::New(isolate);

	// Here's how you could create a Persistent handle to the context, if needed.
	Persistent<Context> persistent_context(isolate, context);

	// Enter the created context for compiling and
	// running the hello world script. 
	Context::Scope context_scope(context);

	//std::cout << argv[1];
	// Create a string containing the JavaScript source code.
	Handle<String> source = String::New(argv[1]);

	// Compile the source code.
	Handle<Script> script = Script::Compile(source);

	// Run the script to get the result.
	Handle<Value> result = script->Run();

	// The persistent handle needs to be eventually disposed.
	persistent_context.Dispose();

	// Convert the result to an ASCII string and print it.
	String::AsciiValue ascii(result);
	std::cout << *ascii << std::endl;
	return 0;
}
