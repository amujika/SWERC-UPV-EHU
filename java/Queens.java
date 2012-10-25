/*************************************************************************
 *  SOURCE: http://introcs.cs.princeton.edu/java/23recursion/Queens.java.html
 *  Compilation:  javac Queens.java
 *  Execution:    java Queens N
 *  
 *  Solve the 8 queens problem using recursion and backtracing.
 *  Prints out all solutions.
 *
 *  Limitations: works for N <= 25, but slows down considerably
 *  for larger N.
 *
 *  Remark: this program implicitly enumerates all N^N possible
 *  placements (instead of N!), but the backtracing prunes off
 *  most of them, so it's not necessarily worth the extra
 *  complication of enumerating only permutations.
 *
 *
 *  % java Queens 3
 *
 *  % java Queens 4
 *  * Q * * 
 *  * * * Q 
 *  Q * * * 
 *  * * Q * 
 *
 *  * * Q * 
 *  Q * * * 
 *  * * * Q 
 *  * Q * * 
 *
 *  % java Queens 8
 *  Q * * * * * * * 
 *  * * * * Q * * * 
 *  * * * * * * * Q 
 *  * * * * * Q * * 
 *  * * Q * * * * * 
 *  * * * * * * Q * 
 *  * Q * * * * * * 
 *  * * * Q * * * * 
 *
 *  ...
 *
 *************************************************************************/

public class Queens {

   /***********************************************************************
    * Return true if queen placement q[n] does not conflict with
    * other queens q[0] through q[n-1]
    ***********************************************************************/
    public static boolean isConsistent(int[] q, int n) {
        for (int i = 0; i < n; i++) {
            if (q[i] == q[n])             return false;   // same column
            if ((q[i] - q[n]) == (n - i)) return false;   // same major diagonal
            if ((q[n] - q[i]) == (n - i)) return false;   // same minor diagonal
        }
        return true;
    }

   /***********************************************************************
    * Print out N-by-N placement of queens from permutation q in ASCII.
    ***********************************************************************/
    public static void printQueens(int[] q) {
        int N = q.length;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (q[i] == j) System.out.print("Q ");
                else           System.out.print("* ");
            }
            System.out.println();
        }  
        System.out.println();
    }


   /***********************************************************************
    *  Try all permutations using backtracking
    ***********************************************************************/
    public static void enumerate(int N) {
        int[] a = new int[N];
        enumerate(a, 0);
    }

    public static void enumerate(int[] q, int n) {
        int N = q.length;
        if (n == N) printQueens(q);
        else {
            for (int i = 0; i < N; i++) {
                q[n] = i;
                if (isConsistent(q, n)) enumerate(q, n+1);
            }
        }
    }  


    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        enumerate(N);
    }

}