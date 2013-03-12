using System;

class Test {
	static void Main() {
		int x = 100000001;
		float y = (float)x;
		
		Console.WriteLine((int)y);
		
		byte b1 = 30;
		byte b2 = 40;
		
		b2 = (Byte)(b2 % b1);
		
		Console.WriteLine(b2);
		
		int a = Int32.MinValue;
		a--;
		
		Console.WriteLine(a == int.MaxValue);
		
		ulong b = (1UL << 32);
		
		// Console.WriteLine(checked((int)b)); System.OverflowException
		Console.WriteLine((int)b);
	}
}
