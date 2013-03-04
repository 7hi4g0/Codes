using System;
using System.Linq;

class Read {
	static void Main() {
		string entrada = Console.ReadLine();
		//char[] separadores = new char[] {' '};
		string[] split =  entrada.Split();//separadores);
		
		int num = 0;

		var numeros = from s in split
			where int.TryParse(s, out num)
			select num;
		
		foreach (int n in numeros) {
			Console.WriteLine(n);
		}
	}
}
