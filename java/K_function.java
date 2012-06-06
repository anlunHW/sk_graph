import java.io.*;
import java.util.HashMap;
import java.util.StringTokenizer;

//CLASS_NAME
//FILE_NAME

public class K_function implements Runnable {
	public static void main(String[] args) {
		new Thread(new K_function()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("function.in"));
			out = new PrintWriter(new File("function.out"));

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

	private long n;
	private long result;
	private HashMap<Long, Long> alreadyCalculated;
	private long module;

	private void reading() {
		try {
			n = nextLong();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			out.println(result);

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		alreadyCalculated = new HashMap<Long, Long>();
		alreadyCalculated.put(new Long(0), new Long(1));
		alreadyCalculated.put(new Long(1), new Long(1));
		alreadyCalculated.put(new Long(2), new Long(1));
		
		module = (long) Math.pow(2, 32);
		result = func(n);
	}

	private long func(long n) {
		if (alreadyCalculated.containsKey(n)) {
			return alreadyCalculated.get(n);
		}
		
		if (n <= 2)
			return 1;
		
		if (n % 2 == 1) {
			Long curResult = new Long(
					(func(6 * n / 7) + func(2 * n / 3)) % module
			);
			alreadyCalculated.put(n, curResult);
			return curResult;
			
		} else {
			Long curResult = new Long(
					(func(n - 1) + func(n - 3)) % module
			);
			alreadyCalculated.put(n, curResult);
			return curResult;
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