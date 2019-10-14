import java.io.*;
import java.util.*;

public class PrincessCheck {
	static class Princess {
		int B, I, R, i;
	}

	static void update(int[] fenwick, int i, int r){
		while (i < fenwick.length){
			fenwick[i] = Math.max(fenwick[i], r);
			i |= i + 1;
		}
	}

	static int query(int[] fenwick, int i){
		int max = 0;
		while (i >= 0){
			max = Math.max(max, fenwick[i]);
			i &= i + 1;
			i--;
		}
		return max;
	}

	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfPrincesses = Integer.parseInt(br.readLine());
		Princess[] princesses = new Princess[numOfPrincesses];

		for (int i = 0; i < numOfPrincesses; i++) {
			princesses[i] = new Princess();
		}

		StringTokenizer st = new StringTokenizer(br.readLine());
		for (int i = 0; i < numOfPrincesses; i++) {
			princesses[i].B = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < numOfPrincesses; i++) {
			princesses[i].I = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < numOfPrincesses; i++) {
			princesses[i].R = Integer.parseInt(st.nextToken());
		}

		Arrays.sort(princesses, (p, q) -> q.I - p.I);
		for (int i = 0, j = 0; i < numOfPrincesses; i++){
			princesses[i].i = i + 1 < numOfPrincesses && princesses[i+1].I == princesses[i].I ? j : j++;
		}

		Arrays.sort(princesses, (p, q) -> q.B - p.B);
		int[] fenwick = new int[numOfPrincesses];
		int count = 0;

		for (int i = 0, j; i < numOfPrincesses; i=j){
			for(j=i; j<numOfPrincesses && princesses[j].B == princesses[i].B; j++){
				if (query(fenwick, princesses[j].i - 1) > princesses[j].R){
					count++;
				}
			}
			for (j=i; j < numOfPrincesses && princesses[j].B == princesses[i].B; j++){
				update(fenwick, princesses[j].i, princesses[j].R);
			}

		}

		System.out.println(count);


	}
}
