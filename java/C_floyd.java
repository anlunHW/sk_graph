import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;

//CLASS_NAME
//FILE_NAME

public class C_floyd implements Runnable {
	public static void main(String[] args) {
		new Thread(new C_floyd()).start();
	}

	public void run() {
		try {
			in = new BufferedReader(new FileReader("floyd.in"));
			out = new PrintWriter(new File("floyd.out"));

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
	private int[][] adjacencyMatrix;

	private void reading() {
		try {
			n = nextInt();
			adjacencyMatrix = new int[n][n];
			
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					adjacencyMatrix[i][j] = nextInt();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					out.print(adjacencyMatrix[i][j]);
					out.print(" ");
				}
				out.print("\n");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void work() {
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					if (adjacencyMatrix[k][j] + adjacencyMatrix[i][k]
							< adjacencyMatrix[i][j])
						adjacencyMatrix[i][j] =
								adjacencyMatrix[k][j] + adjacencyMatrix[i][k];
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