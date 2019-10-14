import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Matchstick {
    static int[] tmax, tmin;
    static void build (int i, int l, int r, int[] sticks){
        if (r-l == 1){
            tmax[i] = tmin[i] = sticks[l];
            return;
        }
        int m = (l + r)/2;
        int il = i * 2 + 1;
        int ir = i * 2 + 2;
        build(il, l, m, sticks);
        build(ir, m, r, sticks);
        tmax[i] = Math.max(tmax[il], tmax[ir]);
        tmin[i] = Math.min(tmin[il], tmin[ir]);
    }

    static int query (int i, int l, int r, int finall, int finalr, boolean max){
        if(finalr <= l || finall >= r){
            return max ? 0 : Integer.MAX_VALUE;
        }
        if(finall <= l && finalr >= r){
            return max ? tmax[i] : tmin[i];
        }
        int m = (l + r)/2;
        int il = i * 2 + 1;
        int ir = i * 2 + 2;
        int t1 = query(il, l, m, finall, finalr, max);
        int t2 = query(ir, m, r, finall, finalr, max);
        return max ? Math.max(t1, t2) : Math.min(t1, t2);
    }


    public static void main (String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int numOfSticks = Integer.parseInt(br.readLine());
        StringTokenizer st = new StringTokenizer(br.readLine());
        int[] sticks = new int[numOfSticks];
        for( int i = 0; i < numOfSticks; i++){
            sticks[i] = Integer.parseInt(st.nextToken());
        }
        int[] maxFromLeft = new int [numOfSticks];
        int[] maxFromRight = new int [numOfSticks];
        maxFromLeft[0] = sticks[0];
        for(int i = 1; i < numOfSticks; i++){
            maxFromLeft[i] = Math.max(sticks[i], maxFromLeft[i-1]);
        }
        maxFromRight[numOfSticks-1] = sticks[numOfSticks-1];
        for(int i = numOfSticks-2; i >=0; i--){
            maxFromRight[i] = Math.max(sticks[i], maxFromRight[i+1]);
        }
        int sticksClosestSquare = 1;
        while (sticksClosestSquare < numOfSticks){
            sticksClosestSquare *= 2;
        }
        tmax = new int[sticksClosestSquare * 2];
        tmin = new int[sticksClosestSquare * 2];
        build(0, 0, numOfSticks, sticks);
        int numOfBurns = Integer.parseInt(br.readLine());
        while(numOfBurns-- > 0){
            st = new StringTokenizer(br.readLine());
            int l = Integer.parseInt(st.nextToken());
            int r = Integer.parseInt(st.nextToken()) + 1;
            int leftMax = l > 0 ? maxFromLeft[l - 1] : 0;
            int rightMax = r < numOfSticks ? maxFromRight[r] : 0;
            int minInSet = query(0, 0, numOfSticks, l, r, false);
            int maxInSet = query(0, 0, numOfSticks, l, r, true);
            double ans = minInSet + Math.max(Math.max(leftMax, rightMax), (maxInSet - minInSet)/2.0);
            System.out.printf("%.1f\n", ans);
        }

    }
}
