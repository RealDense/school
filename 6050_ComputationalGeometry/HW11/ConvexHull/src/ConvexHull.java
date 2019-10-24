import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class ConvexHull {

    static class Point{
        int x;
        int y;
        Point(int x, int y){
            this.x = x;
            this.y = y;
        }
    }

    static long cross(Point a, Point b, Point c){
       return (long) (b.x - a.x) * (c.y - a.y) - (long) (b.y - a.y)*(c.x - a.x);
    }

    static boolean isItOut(Point a, Point b, Point c, boolean upper){
        if(a == null || b == null) {
            return true;
        }
        if(upper && (a == b && a.y < c.y || cross(a,b,c) > 0)){
            return true;
        }
        if(!upper && (a == b && a.y > c.y || cross(a,b,c) < 0)){
            return true;
        }
        return false;
    }

    static void removePoint(TreeSet<Point> t, Point p, boolean right, boolean upper){
        Point a = right ? t.ceiling(p) : t.floor(p);
        if(a == null){
            return;
        }
        if(a.x == p.x){
            t.remove(a);
            a = right ? t.ceiling(p) : t.floor(p);
        }
        if(a == null){
            return;
        }
        Point b = right ? t.higher(a) : t.lower(a);
        int sign = upper ? 1 : -1;
        sign = right ? sign * 1 : sign * -1;
        while(b != null && cross(p, a, b) * sign >= 0){

            t.remove(a);
            a = b;
            b = right ? t.higher(a) : t.lower(a);

        }
    }

    public static void main (String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int q = Integer.parseInt(br.readLine());
        //upper hull
        TreeSet<Point> upper = new TreeSet<>((a,b) -> a.x - b.x);
        //lower hull
        TreeSet<Point> lower = new TreeSet<>((a,b) -> a.x - b.x);

        while(q > 0){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int t = Integer.parseInt(st.nextToken());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            Point p = new Point(x,y);
            Point ul = upper.floor(p);
            Point ur = upper.ceiling(p);
            Point ll = lower.floor(p);
            Point lr = lower.ceiling(p);

            boolean outupper = isItOut(ul, ur, p, true);
            boolean outlower = isItOut(ll, lr, p, false);

            if(t == 1){
                //add to convex hull
                if(outupper){
                    removePoint(upper, p, true, true);
                    removePoint(upper, p, false, true);
                    upper.add(p);
                }
                if(outlower){
                    removePoint(lower, p, true, false);
                    removePoint(lower, p, false, false);
                    lower.add(p);
                }

            }else{
                //see if in convex hull
                //is it right or left?
                System.out.println(outupper || outlower ? "NO" : "YES");
                //above top curve

                //below bottom curve

            }
            //Point[] up = upper.toArray();
            //System.out.printf("UPPER:  ");
            //for(int i = 0; i < up.length; i ++){
            //    System.out.printf("%d %d   ", up[i].x, up[i].y);
            //}

            //Object[] low = lower.toArray();
            //System.out.printf("\nLOWER:  ");
            //for(int i = 0; i < low.length; i ++){
            //    System.out.printf("%d %d   ", low[i].x, low[i].y);
            //}
            //System.out.println();

            q--;
        }

    }

}
