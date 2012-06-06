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

public class A_connect implements Runnable {
	public static void main(String[] args) {
		new Thread(new A_connect()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("connect.in"));
			out = new PrintWriter(new File("connect.out"));

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
	private int[] component;
	private boolean[] used;
	private int componentNumber;
	
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
				edges.get(secondP).add(firstP);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			/*
			for (LinkedList<Integer> list: edges) {
				for (Integer point : list) {
					out.print(point + 1);
					out.print(" ");
				}
				out.println();
			}*/
			out.println(componentNumber);
			
			for (int i = 0; i < n; i++) {
				out.print(component[i]);
				out.print(" ");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		component = new int[n];
		used = new boolean[n];

		for (int i = 0; i < n; i++)
			used[i] = false;
		
		int curComponentNumber = 1;
		for (int i = 0; i < n; i++) {
			if (used[i])
				continue;
			dfs(i, curComponentNumber);
			curComponentNumber++;
		}
		componentNumber = curComponentNumber - 1;
	}
	
	private void dfs(int i, int curComponentNumber) {
		if (used[i])
			return;

		used[i] = true;
		component[i] = curComponentNumber;
		
		for (Integer connectedVertex : edges.get(i)) {
			dfs(connectedVertex, curComponentNumber);
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