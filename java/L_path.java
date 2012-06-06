import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.StringTokenizer;

//CLASS_NAME
//FILE_NAME

public class L_path implements Runnable {
	public static void main(String[] args) {
		new Thread(new L_path()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("path.in"));
			out = new PrintWriter(new File("path.out"));

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
	private int m;
	private ArrayList<LinkedList<Integer>> edges;
	private ArrayList<Integer> bestPath;
	private int[] func;
	
	private int bestDepth;

	private void reading() {
		try {
			n = nextInt();
			m = nextInt();

			edges = new ArrayList<LinkedList<Integer>>();
			for (int i = 0; i < n; i++) {
				edges.add(new LinkedList<Integer>());
			}

			for (int i = 0; i < m; i++) {
				Integer firstP = nextInt() - 1;
				Integer secondP = nextInt() - 1;

				edges.get(firstP).add(secondP);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			out.println(bestPath.size() - 1);
			for (int i = bestPath.size() - 1; i >= 0; i--) {
				out.print((bestPath.get(i) + 1) + " ");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		func = new int[1 << (n + 2)];
		
		bestDepth = 0;
		bestPath = new ArrayList<Integer>();
		bestPath.add(0);

		for (int i = 0; i < n; i++) {
			ArrayList<Integer> curResult = go(0, i);
			if (curResult.size() > bestPath.size())
				bestPath = curResult;
		}
	}

	private ArrayList<Integer> go(int set, int vertex/*, int depth*/) {
		if ((func[set] & (1 << vertex)) != 0)
			return new ArrayList<Integer>();
		func[set] |= 1 << vertex;

		set |= 1 << vertex;

		ArrayList<Integer> result = null;

		for (int connectedVertex : edges.get(vertex)) {
			if ((set & (1 << connectedVertex)) == 0) {
				ArrayList<Integer> curResult =
						go(set | (1 << connectedVertex), connectedVertex/*, depth + 1*/);
				if (result == null || curResult.size() > result.size()) {
					result = curResult;
				}
			}
		}

		if (result == null) {
			result = new ArrayList<Integer>();
			result.add(vertex);
			return result;
		}

		result.add(vertex);
		return result;
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