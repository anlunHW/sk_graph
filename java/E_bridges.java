import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

//CLASS_NAME
//FILE_NAME

public class E_bridges implements Runnable {
	public static void main(String[] args) {
		new Thread(new E_bridges()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("bridges.in"));
			out = new PrintWriter(new File("bridges.out"));

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
	private ArrayList<ArrayList<Edge>> edges;
	private boolean[] used;
	private int[] inTime;
	private int[] minTime;
	private PriorityQueue<Integer> bridges;
	private int timer;
	private HashMap<Edge, Integer> bridgeOrder;

	private class Edge {
		Edge(int start, int end) {
			this.start = start;
			this.end = end;
		}

		int start;
		int end;
	}

	private void reading() {
		/*
		ArrayList<Integer> a = new ArrayList<Integer>(10);
		System.out.println(a.size());
		a.add(10);
		System.out.println(a.size());
		*/
		
		try {
			n = nextInt();
			m = nextInt();

			//edges = new ArrayList<LinkedList<Edge>>();
			edges = new ArrayList<ArrayList<Edge>>(n);
			for (int i = 0; i < n; i++) {
				//edges.add(new LinkedList<Edge>());
				edges.add(new ArrayList<Edge>(m / 1000));
			}

			bridgeOrder = new HashMap<Edge, Integer>(m);

			for (int i = 0; i < m; i++) {
				Integer firstP = nextInt() - 1;
				Integer secondP = nextInt() - 1;

				Edge curEdge = new Edge(firstP, secondP);
				
				edges.get(firstP).add(curEdge);
				edges.get(secondP).add(curEdge);

				bridgeOrder.put(curEdge, i);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			out.println(bridges.size());
			while (!bridges.isEmpty()) {
				out.println(bridges.poll() + 1);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		used = new boolean[n];
		inTime = new int[n];
		minTime = new int[n];
		bridges = new PriorityQueue<Integer>();

		timer = 0;
		
		for (int i = 0; i < n; i++)
			if (!used[i])
				dfs(i, -1);
	}

	private void dfs(int vertex, int parent) {
		used[vertex] = true;
		inTime[vertex] = timer;
		minTime[vertex] = timer;
		timer++;
		
		for (Edge curEdge : edges.get(vertex)) {
			int connectedVertex = curEdge.start;
			if (connectedVertex == vertex)
				connectedVertex = curEdge.end;

			if (connectedVertex == parent)
				continue;

			if (used[connectedVertex]) {
				minTime[vertex] = Math.min(minTime[vertex], inTime[connectedVertex]);
			} else {
				dfs(connectedVertex, vertex);
				minTime[vertex] = Math.min(minTime[vertex], minTime[connectedVertex]);
				if (minTime[connectedVertex] > inTime[vertex]) {
					bridges.add(bridgeOrder.get(curEdge));
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