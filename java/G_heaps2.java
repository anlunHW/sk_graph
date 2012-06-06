import java.io.*;
import java.util.HashMap;
import java.util.HashSet;
import java.util.StringTokenizer;

//CLASS_NAME
//FILE_NAME

public class G_heaps2 implements Runnable {
	public static void main(String[] args) {
		new Thread(new G_heaps2()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("heaps2.in"));
			out = new PrintWriter(new File("heaps2.out"));

			reading();
			work();
			writing();

		} catch (Exception e) {
			e.printStackTrace();

		} finally {
			if (out != null) {
				out.flush();
				out.close();
			}
		}
	}

	private int k;
	private int[] a;
	private int minA;
	
	private int m;
	private int[] n_size;
	private int maxN;
	
	HashMap<Integer, Integer> alreadyCalculated;

	private void reading() {
		try {
			k = nextInt();
			minA = 1000001;
			a = new int[k];
			for (int i = 0; i < k; i++) {
				a[i] = nextInt();
				if (a[i] < minA)
					minA = a[i];
			}
			
			m = nextInt();
			maxN = 0;
			n_size = new int[m];
			for (int i = 0; i < m; i++) {
				n_size[i] = nextInt();

				if (n_size[i] > maxN)
					maxN = n_size[i];
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			for (int i = 0; i < m; i++)
				if (alreadyCalculated.get(n_size[i]) != 0)
					out.println("First");
				else
					out.println("Second");

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		alreadyCalculated = new HashMap<Integer, Integer>();

		for (int i = 0; i < Math.min(minA, maxN); i++)
			alreadyCalculated.put(i, 0);
		
		for (int i = 0; i < m; i++) {
			func(n_size[i]);

			if ((i + 1) % 120 == 0)
				System.gc();
		}
	}

	private int func(int n) {
		if (alreadyCalculated.containsKey(n))
			return alreadyCalculated.get(n);

		HashSet<Integer> curSet = new HashSet<Integer>();

		for (int i = 0; i < k; i++) {
			if (n - a[i] >= 0) {
				curSet.add(func(n - a[i]));
			}
		}

		for (int i = 0; ; i++) {
			if (!curSet.contains(i)) {
				alreadyCalculated.put(n, i);
				return i;
			}
		}
	}

	private String nextToken() throws IOException {
		while (st == null || !st.hasMoreTokens()) {
			st = new StringTokenizer(in.readLine());
		}
		return st.nextToken();
	}

	private int nextInt() throws NumberFormatException, IOException {
		return Integer.parseInt(nextToken());
	}

	private long nextLong() throws NumberFormatException, IOException {
		return Long.parseLong(nextToken());
	}

	private double nextDouble() throws NumberFormatException, IOException {
		return Double.parseDouble(nextToken());
	}

	private StringTokenizer st;
	private BufferedReader in;
	private PrintWriter out;
}