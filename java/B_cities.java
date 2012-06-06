import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;

//CLASS_NAME
//FILE_NAME

public class B_cities implements Runnable {
	public static void main(String[] args) {
		new Thread(new B_cities()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("bfsrev.in"));
			out = new PrintWriter(new File("bfsrev.out"));

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

	final int INFINITY_COST = 10000000;
	
	private int n;
	private int s;
	private int m;

	private ArrayList<LinkedList<Integer>> edges;
	private int[] journeyCost;

	private void reading() {
		try {
			n = nextInt();
			s = nextInt() - 1;
			m = nextInt();

			edges = new ArrayList<LinkedList<Integer>>();
			for (int i = 0; i < n; i++) {
				edges.add(new LinkedList<Integer>());
			}

			for (int i = 0; i < m; i++) {
				// разворачиваем вектора,
				// так как будем решать обратную задачу
				Integer secondP = nextInt() - 1;
				Integer firstP = nextInt() - 1;

				edges.get(firstP).add(secondP);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			 for (int i = 0; i < n; i++) {
				 if (journeyCost[i] != INFINITY_COST)
				    out.print(journeyCost[i]);
				 else
					out.print(-1);

				 out.print(" ");
			 }
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		journeyCost = new int[n];
		for (int i = 0; i < n; i++)
			journeyCost[i] = INFINITY_COST;
		journeyCost[s] = 0;

		bfs();
	}

	private void bfs() {
		// 3 - just in case
		ArrayBlockingQueue<Integer> queue = new ArrayBlockingQueue<Integer>(n * 3);
		queue.add(s);
		journeyCost[s] = 0;

		while (!queue.isEmpty()) {
			int curElem = queue.poll();

			for (int vertex : edges.get(curElem)) {
				if (journeyCost[vertex] == INFINITY_COST) {
					journeyCost[vertex] = journeyCost[curElem] + 1;
					queue.add(vertex);
				}
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