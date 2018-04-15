/**
 * Homework Assignment #4: Percolation
 *
 * - PercolationStats for simulation of percolation
 *
 * @ Student ID : 20145810
 * @ Name       : Hyun-Do Park
 **/

import java.util.Random;

public class PercolationStats {

    private int mT;             // number of experiments to run
    private double mMean;       // mean of percolation threshold
    private double mStddev;     // standard deviation of percolation threshold

    private final double[] pThreshold;   // array to save percolation threshold   

    // perform T independent experiments on an N-by-N grid
    public PercolationStats(int N, int T) {

        if (N <= 0 || T <= 0)
            throw new java.lang.IllegalArgumentException(
                            "N and T must be greater than 1");
        mT = T;

        pThreshold = new double[mT]; 

        Random random = new Random(System.currentTimeMillis());
        int i, j, iter, countStep;  
        double mStddev2 = 0;

        for (iter = 0; iter < mT; iter++) {             // for performing T
            // initailize variable to count percolates into zero
            countStep = 0;
            // Create percolation                                
            Percolation percolation = new Percolation(N); 
            // Until do not percolates 
            while (!percolation.percolates()) { 
                countStep++;        // count step             
                do { 
                    i = random.nextInt(N) + 1;      // save random number into i 
                    j = random.nextInt(N) + 1;      // save random number into j 
                } while (percolation.isOpen(i, j)); // until open sites(i,j) 
                percolation.open(i, j);             // open site(i, j) 
            } 
            pThreshold[iter] = 1.0 * countStep / (N * N);   // save p*  
            mMean += pThreshold[iter] / mT;                 // plus mean                    
 
        }

        for (iter = 0; iter < mT; iter++) {
            // temporary save stdandard deviation of percolation threshold 
            double temp = pThreshold[iter] - mMean;  
            mStddev2 += (temp * temp); 
        }

        mStddev2 /= (mT - 1);
        // finally save standard deviation of p* 
        mStddev = Math.sqrt(mStddev2);
    }

    // sample mean of percolation threshold
    public double mean() {
        return mMean;
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return mStddev;
    }

    // low  endpoint of 95% confidence interval
    public double confidenceLo() {
        return mMean - 1.96 * mStddev / Math.sqrt(mT);
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return mMean + 1.96 * mStddev / Math.sqrt(mT);
    }

    public static void main(String[] args)    // test client(described below)
    {
        PercolationStats percStats;
        int N = 0;
        int T = 0;
        long start = System.currentTimeMillis();
        double time;

        // you must get two inputs N and T
        if (args.length > 0) {
            try {
                N = Integer.parseInt(args[0]);  // get N
                T = Integer.parseInt(args[1]);  // get T
            } catch (NumberFormatException e) {
                System.err.println("Argument" + args[0] + " and " 
                                            + args[1] + " must be integers.");
                return;
            }
        }

        // run experiment
        percStats = new PercolationStats(N, T);

        // print result
        System.out.println("mean                    = " + percStats.mean());
        System.out.println("stddev                  = " + percStats.stddev());
        System.out.println("95% confidence interval = "
                + percStats.confidenceLo() + ", " + percStats.confidenceHi());

        time = (System.currentTimeMillis() - start) / 1000.0;
        System.out.printf("total time = %f sec (N = %d, T = %d)\n", time, N, T);
    }
}

