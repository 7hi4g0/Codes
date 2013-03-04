using Gtk;
using System;

class Hello {
	static void Main() {
		Application.Init();
		
		Window window = new Window("Hello World");
		window.Show();
		
		Application.Run();
	}
}
