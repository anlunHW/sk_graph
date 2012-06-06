import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

//CLASS_NAME
//FILE_NAME

public class D_topsort implements Runnable {
	public static void main(String[] args) {
		new Thread(new D_topsort()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("topsort.in"));
			out = new PrintWriter(new File("topsort.out"));

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
	private boolean doesGraphHaveLoop;
	private int[] vertexColor;
	private boolean[] used;
	private Vector<Integer> order;

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
			if (doesGraphHaveLoop) {
				out.print(-1);
				return;
			}

			for (int i = n - 1; i >= 0; i--) {
				out.print(order.get(i) + 1);
				out.print(" ");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		// проверка на ацикличность
		doesGraphHaveLoop = false;
		
		vertexColor = new int[n];
		for (int i = 0; i < n; i++)
			vertexColor[i] = 0;

		for (int i = 0; i < n; i++)
			if (dfsLoopCheck(i))
				break;

		if (doesGraphHaveLoop)
			return;

		// выполнение сортировки
		used = new boolean[n];
		for (int i = 0; i < n; i++)
			used[i] = false;
		
		order = new Vector<Integer>();
		for (int i = 0; i < n;  i++)
			if (!used[i])
				dfsTopSort(i);
	}

	private void dfsTopSort(int i) {
		used[i] = true;

		for (int connectedVertex : edges.get(i)) {
			if (!used[connectedVertex])
				dfsTopSort(connectedVertex);
		}
		
		order.add(i);
	}

	private boolean dfsLoopCheck(int i) {
		vertexColor[i] = 1;

		for (int connectedVertex : edges.get(i)) {
			if (vertexColor[connectedVertex] == 0) {
				if (dfsLoopCheck(connectedVertex))
					return true;
			} else {
				if (vertexColor[connectedVertex] == 1) {
					doesGraphHaveLoop = true;
					return true;
				}
			}
		}

		vertexColor[i] = 2;
		return false;
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