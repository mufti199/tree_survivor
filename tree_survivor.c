/* Solution to COMP20005 Assignment 2, May - 2018
   Program made by Gazi Mufti Mahmood. Student ID - 884041
   Moto - Programming is Fun! */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TREES 52    /* Max number of trees (also max size of data arrays)*/
#define X_AXIS 70       /* Max value of the x-axis */
#define Y_AXIS 60       /* Max value of the x-axis */
#define SF 1            /* Stress Factor */

/* Function Prototypes */
int mygetchar(void);
void readlines(void);
void conflicts(void);
void ploter(int stage);
void graph_points(void);
void check(void);
int reaper(float rainfall);
void print_array(void);

/* Structres */
struct {
    char tree[MAX_TREES];
    double xloc[MAX_TREES];
    double yloc[MAX_TREES];
    int liters[MAX_TREES];
    double rootrad[MAX_TREES];
    int key;
    double tsf;
} data;

struct {
    char points[Y_AXIS/2][X_AXIS];
    double sd[Y_AXIS/2][X_AXIS];    /* Storing distance between points */
    double sr[Y_AXIS/2][X_AXIS];    /* Storing radius of trees */
} graph_data;

struct {
    int new[MAX_TREES];
} area;

/* Main program holds it all together */
int
main(int argc, char *argv[]){
    /* Stage 1 */
    readlines();
    printf("\n");

    /* Stage 2 */
    conflicts();
    printf("\n");

    /* Stage 3 */
    ploter(3);
    printf("\n\n");

    /* Stage 4 */
    /* Checks to see if the command line has correct number of arguments */
    if (argc != 2){
        printf("Invalid number of arguments.\n");
        return 1;
    }
    /* Outputs annual rainfall retrieved from the command line */
    float rainfall;
    rainfall = atof(argv[1]);
    printf("S4: rainfall amount = %.1f\n", rainfall);
    /* Computes the trees that will die in order of death */
    while (reaper(rainfall) != 0){
        graph_points();
    }
    printf("\n");
    /* Graphs reamining trees */
    ploter(4);

    /* Program executed successfully! */
    return 0;
}

/* Stores useful data and prints the output for Stage 1 */
void
readlines(){
    char c;
    int l, line = 0;
    double x, y, rr, megal = 0;
    /* Skipping the first two lines */
    while ((c = mygetchar()) != EOF){
        if (c == '\n'){
            line ++;
        }
        if (line == 1){
            line = 0;
            break;
        }
    }
    /* Storing data into respective arrays */
    while (scanf(" %c%lf%lf%d%lf", &c, &x, &y, &l, &rr) != EOF){
        data.tree[line] = c;
        data.xloc[line] = x;
        data.yloc[line] = y;
        data.liters[line] = l;
        data.rootrad[line] = rr;
        megal += l;
        line ++;
    }
    /* Key of the arrays */
    data.key = line - 1;
    /* Converting megal from liters to megaliters and output for Stage 1 */
    megal = megal/1000000;
    printf("S1: total data lines    = %5d trees\n", line);
    printf("S1: total water needed  = %1.3f magalitres per year\n", megal);
}

/* Compares distance between each tree and their roots to find tress with
   conflicting roots */
void
conflicts(){
    int i, j;
    double d, x1, x2, y1, y2;
    /* Setting each coordinate as (x1, y1) */
    for (i = 0; i <= data.key; i++){
        x1 = data.xloc[i];
        y1 = data.yloc[i];
        printf("S2: tree %c is in conflict with", data.tree[i]);
        /*  Setting each coordinate as (x2, y2) for each value of (x1, y1) */
        for (j = 0; j <= data.key; j++){
            x2 = data.xloc[j];
            y2 = data.yloc[j];
            /* Calculating distance between (x1, y1) and (x2, y2)*/
            d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
            /* Printing trees with conflicing roots */
            if (d == 0){
            } else if (d < (data.rootrad[i] + data.rootrad[j])){
                printf(" %c", data.tree[j]);
            }
        }
        printf("\n");
    }
}

/* Plots gold */
void
ploter(int stage){
    graph_points();
    int x, y;
    for (y = Y_AXIS/2; y >= -2; y--){
        printf("S%d: ", stage);
        if (y % 5 == 0){
            printf("%2d +", y*2);   /* Because y was divided by 2*/
        } else if (y < 0){
            printf("    ");
        } else {
            printf("   |");
        }
        for (x = 0; x <= X_AXIS; x++){
            if ((y >= 0) && (y != Y_AXIS/2)){
                printf("%c", graph_data.points[y+1][x]);
            }
            /* Making the X- axis */
            if (y == -1){
                if (x % 10 == 0){
                    printf("+");
                } else {
                    printf("-");
                }
            } else if (y == -2){
                if (x == 0){
                    printf("0");
                } else if (x % 10 == 0){
                    printf("%2d",x);
                } else if(x % 10 == 1){
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}


/* Calculates coordinates of the points and stores them in the 2d array */
void
graph_points(){
    char cc;
    int xs, ys, z;
    double x1, y1, radius, d, x, y;
    /* Initializing the 2d array in graph_data to single spaces*/
    for (y = Y_AXIS - 1; y > 0; y = y - 2){
        for (xs = 0.5; xs <= X_AXIS; xs++){
            ys = round(y/2);
            graph_data.points[ys][xs] = ' ';
        }
    }
    /* Storing the coordinates of the trees in the 2d array in descending order
       of trees */
    for (z = data.key; z >= 0; z--){
        cc = data.tree[z];
        for (y = Y_AXIS - 1; y > 0; y = y - 2){
            x1 = data.xloc[z];
            y1 = data.yloc[z];
            radius = data.rootrad[z];
            for (x = 0.5; x <= X_AXIS; x++){
                /* Caculating the distance of each point from the center
                   of the each the current tree */
                d = sqrt(pow((x1 - x), 2) + pow((y1 - y), 2));
                ys = round(y/2);
                xs = x - 0.5;
                /* Storing the 1st tree's (in descending order) distance and
                   radius as the shortest distance and radius, yet */
                if (z == data.key){
                    graph_data.sd[ys][xs] = d;
                    graph_data.sr[ys][xs] = radius;
                }
                /* Storing the trees (nanmes) in the appropriate coordinates */
                if ((d < radius) && ((d <= graph_data.sd[ys][xs]) ||
                (graph_data.sr[ys][xs] < graph_data.sd[ys][xs]))){
                    graph_data.points[ys][xs] = cc;
                    graph_data.sd[ys][xs] = d;
                    graph_data.sr[ys][xs] = radius;
                }
            }
        }
    }
}


/* Finds the trees that will dies in order of their death */
int
reaper(float rainfall){
    /* Storing the conflicted areas */
    char t;
    int i, n, x, xs, y, ys, a, b;
    double need, get, max_sf, temp_sf;
    /* Counting the number of cells for each tree */
    for (i = 0; i <= data.key; i++){
        n = 0;
        t = data.tree[i];
        for (y = Y_AXIS - 1; y > 0; y = y - 2){
            for (x = 0.5; x <= X_AXIS; x++){
                ys = round(y/2);
                xs = x - 0.5;
                if (t == graph_data.points[ys][xs]){
                    n++;
                }
            }
        }
        /* Multiplyting the cell number by 2 to get the 'active' area of the
           tree's roots */
        area.new[i] = 2*n;
    }
    /* Calculating the stress factor of each tree */
    a = b = max_sf =0;
    for (i = 0; i <= data.key; i++){
        need = data.liters[i];
        get = area.new[i]*rainfall;
        temp_sf = need/get;
        if (temp_sf > max_sf){
            max_sf = temp_sf;
            b = i;
        }
    }
    /* Output of death of the tree with the lowest shear factor */
    if(SF < max_sf){
        printf("S4: tree %c has stress factor %.2f and dies next\n",
        data.tree[b], max_sf);
        data.tree[b] = ' ';
        data.xloc[b] = 0;
        data.yloc[b] = 0;
        data.liters[b] = 0;
        data.rootrad[b] = 0;
        a = 1;
    }
    return a;
}

/* Gets characters. Function made by Alister Moffat*/
int
mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
	}
	return c;
}
