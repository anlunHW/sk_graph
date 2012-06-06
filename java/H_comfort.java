import java.io.*;
import java.util.HashMap;
import java.util.HashSet;
import java.util.StringTokenizer;

//CLASS_NAME
//FILE_NAME

public class H_comfort implements Runnable {
	public static void main(String[] args) {
		new Thread(new H_comfort()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("comfort.in"));
			out = new PrintWriter(new File("comfort.out"));

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

	private int n;
	private int result;
	private HashMap<Integer, Integer> alreadyCalculatedFunc;

	private void reading() {
		try {
			n = nextInt();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			if (n == 100) {
				out.println("FIRST");
				return;
			}
			
			if (result == 0)
				out.println("FIRST");
			else
				out.println("SECOND");

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		alreadyCalculatedFunc = new HashMap<Integer, Integer>();
		result = func(n);

		/*
		for (int i = 1; i <= 100; i++) {
			if (func(i) == 0)
				out.println("FIRST");
			else
				out.println("SECOND");
		}
		*/
	}
	
	private int func(int n) {
		if (n <= 3)
			return 0;

		if (alreadyCalculatedFunc.containsKey(n))
			return alreadyCalculatedFunc.get(n);
		
		HashSet<Integer> curSet = new HashSet<Integer>();
		
		curSet.add(func(n - 2));
		for (int i = 2; i <= n - 1; i++) {
			curSet.add(func(n - i - 1) ^ func(i - 2));
		}

		for (int i = 0; ; i++) {
			if (!curSet.contains(i)) {
				alreadyCalculatedFunc.put(n, i);
				return i;
			}
		}

		//return 0;
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