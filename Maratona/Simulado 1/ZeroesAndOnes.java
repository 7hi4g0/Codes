import java.util.Arrays;
import java.util.Scanner;

public class ZeroesAndOnes {
	static int nBits, k;
	static long[][][] dp = new long[65][65][101];

	public static long go(int zeroes, int ones, int mod) {
		if (zeroes + ones > nBits)
			return 0;
		else if (dp[zeroes][ones][mod] != -1)
			return dp[zeroes][ones][mod];
		else
			return dp[zeroes][ones][mod] = go(zeroes + 1, ones, (mod << 1) % k)
					+ go(zeroes, ones + 1, ((mod << 1) % k + 1) % k);
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int cc = 1;
		int TC = in.nextInt();
		while (TC-- > 0) {
			long res = 0;
			nBits = in.nextInt();
			k = in.nextInt();
			for (int i = 0; i < dp.length; i++)
				for (int j = 0; j < dp[i].length; j++)
					Arrays.fill(dp[i][j], -1);
			dp[nBits / 2][nBits / 2][0] = 1;
			if (k > 0 && nBits % 2 == 0)
				res = go(0, 1, 1 % k);
			System.out.println("Case " + (cc++) + ": " + res);
		}
	}
}


