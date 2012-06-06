import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

//CLASS_NAME
//FILE_NAME

public class O_negcycle implements Runnable {
	public static void main(String[] args) {
		new Thread(new O_negcycle()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("negcycle.in"));
			out = new PrintWriter(new File("negcycle.out"));

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

	private class Edge {
		Edge(int start, int end, int cost) {
			this.start = start;
			this.end = end;
			this.cost = cost;
		}

		int start;
		int end;
		int cost;
	}
	
	private int n;
	private ArrayList<Edge> edges;
	private final int notExistedCost = 100000;
	private ArrayList<Integer> negativeCycle;

	private void reading() {
		try {
			n = nextInt();
			edges = new ArrayList<Edge>();

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					int curCost = nextInt();
					if (curCost >= notExistedCost)
						continue;
					edges.add(new Edge(i, j, curCost));
				}
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			if (negativeCycle.size() == 0) {
				out.print("NO");
				return;
			}

			out.println("YES");
			out.println(negativeCycle.size() - 1);
			for (int i = negativeCycle.size() - 1; i >= 1; i--) {
				out.print(negativeCycle.get(i) + 1);
				out.print(" ");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		int[] d = new int[n];
		int[] previous = new int[n];
		for (int i = 0; i < n; i++) {
			previous[i] = -1;
		}

		int changedCostVertex = -1;
		for (int i = 0; i < n; i++) {
			changedCostVertex = -1;
			for (Edge edge: edges) {
				if (d[edge.end] > d[edge.start] + edge.cost) {
					d[edge.end] = Math.max(-notExistedCost, d[edge.start] + edge.cost);
					previous[edge.end] = edge.start;
					changedCostVertex = edge.end;
				}
			}
		}

		negativeCycle = new ArrayList<Integer>();
		if (changedCostVertex != -1) {
			int startVertex = changedCostVertex;
			for (int i = 0; i < n; i++) {
				startVertex = previous[startVertex];
			}

			for (int curVertex = startVertex; ; curVertex = previous[curVertex]) {
				negativeCycle.add(curVertex);
				if ((curVertex == startVertex) && negativeCycle.size() > 1)
					break;
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