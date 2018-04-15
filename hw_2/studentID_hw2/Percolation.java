/**
 * Homework Assignment #4: Percolation
 *
 *  - Percolation data structure
 *
 * @ Student ID : 20145810
 * @ Name     : Hyun-Do Park
 **/

import java.util.Scanner;
import java.io.File;

public class Percolation {

    private static final boolean SITE_BLOCKED = false;
    private static final boolean SITE_OPEN = true;
    private boolean[] sites;          // sites[i] = state of site i
    private int mN;                   // remember the input N
    private int topIdx;               // idx of the special top
    private int bottomIdx;            // idx of the speical bottom
    private WeightedQuickUnionUF uf;
    private int sizeOfGrid;                         // Total size of N-by-N Grid 
    private static final int[][] neighborSites = {  // Above, Below, Left, Right site  
        { 1, 0 },                                   // Below site                                      
        { 0, -1 },                                  // Left site
        { -1, 0 },                                  // Above site 
        { 0, 1 }                                    // Right site
    }; 

    // create N-by-N grid, with all sites blocked
    public Percolation(int N) {
        if (N <= 0)
            throw new IllegalArgumentException("N must be >0");
        mN = N;

        this.sizeOfGrid = mN * mN + 2;  // Total size of N-by-N Grid 
        this.uf = new WeightedQuickUnionUF(sizeOfGrid);
        this.bottomIdx = mN*mN+1;   // bottomIdx is the last index of sites
        this.topIdx = 0;            // topIdx is the first index of sites                                        

        sites = new boolean[sizeOfGrid];    // Initialize sites array  
        sites[topIdx] = SITE_OPEN;          // Virtual top site is opened
        sites[bottomIdx] = SITE_OPEN;                      

        // all sites is blocked except for top, bottom
        for (int i = 1; i < sizeOfGrid; i++) {            
            sites[i] = SITE_BLOCKED; 
        } 

    }

    // open site(row i, column j) if it is not open already
    public void open(int i, int j) {

        // Check Index
        checkIndex(i, j);

        if (!isOpen(i, j)) {
            // site(i,j) open 
            sites[xyTo1D(i, j)] = true;
            // loop neighborSites and initailize array in int[] neighborSite
            // First turn : below, Second turn : left 
            // Third turn : above, Fourth turn : right 
            for (int[] neighborSite : neighborSites) {
                // Check if input(i,j) is valid and is opened
                // Then, Run union Func with the value(above, below, left, right point)                 
                if (isValid(i + neighborSite[0], j + neighborSite[1]) && isOpen(i + neighborSite[0], j + neighborSite[1])) {
                    this.uf.union(xyTo1D(i, j), xyTo1D(i + neighborSite[0], j + neighborSite[1])); 
                }
                // when checking 4 sides, if exceed N-by-N grid sites 
                else { 
                    if (i + neighborSite[0] < 1) {
                        // connect topIdx 
                        this.uf.union(xyTo1D(i, j), topIdx); 
                    } 
                    if (i + neighborSite[0] > mN) {
                        // connect bottomIdx 
                        this.uf.union(xyTo1D(i, j), bottomIdx); 
                    } 
                } 
            } 
        } 
        else { 
            return; 
        }

    }

    public boolean isOpen(int i, int j) {
        // check param
        checkIndex(i, j);                   
        // change the value to open into true
        return sites[xyTo1D(i, j)];         
    }

    public boolean isFull(int i, int j) {
        // check param
        checkIndex(i, j);
        // If open AND connected, true 
        // otherwise, false
        return isOpen(i, j) && this.uf.connected(topIdx, xyTo1D(i, j));
    }

    public boolean percolates() {
        // By checking if the sites connect from top to bottom
        // Can know if the sites are percolates 
        return this.uf.connected(topIdx, bottomIdx); 
    }

    // test client(optional)
    public static void main(String[] args)
    {
        Scanner in;
        int N = 0;
        long start = System.currentTimeMillis();

        try {
            // get input file from argument
            in = new Scanner(new File(args[0]), "UTF-8");
        } catch (Exception e) {
            System.out.println("invalid or no input file ");
            return;
        }

        N = in.nextInt();         // N-by-N percolation system
        System.out.printf("N = %d\n", N);

        // repeatedly read in sites to open and draw resulting system
        Percolation perc = new Percolation(N);

        while (in.hasNext()) {
            int i = in.nextInt();   // get i for open site (i,j)
            int j = in.nextInt();   // get j for open site (i,j)
            perc.open(i, j);        // open site (i,j)
            System.out.printf("open(%d, %d)\n", i, j);
        }

        if (perc.percolates()) {
            System.out.println("This system percolates");
        } 
        else {
            System.out.println("This system does NOT percolate");
        }

        in.close(); // close scanner

        double time = (System.currentTimeMillis() - start) / 1000.0;
        System.out.println("running time = "+ time + " sec");
    }

    private boolean isValid(int i, int j) {
        // when checking 4 sides in open()
        // check if the params is valid   
        return (i >= 1 && i <= mN && j >= 1 && j <= mN); 
    } 

    private void checkIndex(int i, int j) {
        if (i < 1 || i > mN)
            throw new IndexOutOfBoundsException("row index i out of bounds");
        if (j < 1 || j > mN)
            throw new IndexOutOfBoundsException("column index j out of bounds");
    }

    private int xyTo1D(int i, int j) {
        // change the param(row, column) into index
        return (i-1) * mN + j;
    }

}