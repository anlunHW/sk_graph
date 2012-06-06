import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

//CLASS_NAME
//FILE_NAME

public class F_connect implements Runnable {
	public static void main(String[] args) {
		new Thread(new F_connect()).start();
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
	private double[][] edgeCost;
	private ArrayList<String> resultEdges;
	private double resultLength;

	private class Point {
		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		public int x;
		public int y;
	}
	
	private void reading() {
		try {
			n = nextInt();

			Point[] points = new Point[n];
			for (int i = 0; i < n; i++) {
				Integer firstP = nextInt() - 1;
				Integer secondP = nextInt() - 1;

				points[i] = new Point(firstP, secondP);
			}

			edgeCost = new double[n][n];
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					edgeCost[i][j] = Math.sqrt(
							(points[i].x - points[j].x) * (points[i].x - points[j].x)
							+
							(points[i].y - points[j].y) * (points[i].y - points[j].y)
					);

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void writing() {
		try {
			out.println(resultLength);
			out.println(resultEdges.size());

			Collections.sort(resultEdges);
			for (String str : resultEdges) {
				out.println(str);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private class PointStr {
		public PointStr(int pointNum, int minStartPointNum, double minCost) {
			this.pointNum = pointNum;
			this.minStartPointNum = minStartPointNum;
			this.minCost = minCost;
		}

		public int pointNum;
		public int minStartPointNum;
		public double minCost;
	}
	
	private void work() {
		HashSet<PointStr> notConnectedPoints = new HashSet<PointStr>(n - 1);
		//0 - in our set
		for (int i = 1; i < n; i++) {
			notConnectedPoints.add(new PointStr(i, 0, edgeCost[i][0]));
		}

		resultEdges = new ArrayList<String>(n - 1);
		resultLength = 0;
		
		while (!notConnectedPoints.isEmpty()) {
			double minCost = 2000 * 2000 + 2000 * 2000; // constants from problem
			PointStr pointToRemove = new PointStr(-1, -1, -1);

			for (PointStr ps : notConnectedPoints) {
				if (ps.minCost < minCost) {
					minCost = ps.minCost;
					pointToRemove = ps;
				}
			}

			resultLength += minCost;

			//ADD EDGE!!!
			if (pointToRemove.pointNum < pointToRemove.minStartPointNum) {
				resultEdges.add(
						(pointToRemove.pointNum + 1) + " " +
								(pointToRemove.minStartPointNum + 1)
				);
			} else {
				resultEdges.add(
						(pointToRemove.minStartPointNum + 1) + " " +
								(pointToRemove.pointNum + 1)
				);
			}

			for (PointStr ps : notConnectedPoints) {
				if (edgeCost[pointToRemove.pointNum][ps.pointNum] < ps.minCost) {
					ps.minCost = edgeCost[pointToRemove.pointNum][ps.pointNum];
					ps.minStartPointNum = pointToRemove.pointNum;
				}
			}
			
			notConnectedPoints.remove(pointToRemove);
		}
		
	}
	
	/*
	private void work() {
		/*
		LinkedList<Integer> notConnectedPoints = new LinkedList<Integer>();
		LinkedList<Double> notConnectedPointsMinCost = new LinkedList<Double>();
		LinkedList<Integer> notConnectedPointsMinPoint = new LinkedList<Integer>();

		for (int i = 1; i < n; i++) {
			notConnectedPoints.add(i);
			//0 - first point in our tree

			notConnectedPointsMinCost.add(edgeCost[i][0]);
			notConnectedPointsMinPoint.add(0);
		}

		while (!notConnectedPoints.isEmpty()) {
			double minCost = notConnectedPointsMinCost.getFirst();
			int pointToAdd = notConnectedPoints.getFirst();

			Iterator itPoints = notConnectedPoints.iterator();
			Iterator itCosts = notConnectedPointsMinCost.iterator();
			Iterator itConnectedPoints = notConnectedPointsMinCost.iterator();

			Iterator minItPoints = notConnectedPoints.iterator();
			Iterator minItCosts = notConnectedPointsMinCost.iterator();
			Iterator minItConnectedPoints = notConnectedPointsMinCost.iterator();

			while (itPoints.hasNext()) {
			}
		}
		/**

	}
	*/

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