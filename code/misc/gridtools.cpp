#define MAXN 100
int g[MAXN][MAXN],vis[MAXN][MAXN];

/*
CHESS
0 - Horse
1 - Bishop
2 - Rook
3 - Queen
*/

int mod[] = {4,4,3};
vector<vector<int>> chessx = {
    {2, 2, 1, 1, -1, -1, -2, -2},
    {1, 1, -1, -1},
    {1, 0, -1, 0},
    {1, 0, -1, 0, 1, 1, -1, -1}
};

vector<vector<int>> chessy = {
    {1, -1, 2, -2, 2, -2, 1, -1},
    {1, -1, 1, -1},
    {0, 1, 0, -1},
    {0, 1, 0, -1, 1, -1, 1, -1}
};

/*
ROBOT
0 - Clockwise Spiral
1 - CounterClockWise Spiral
2 - Main Diagonal
*/

vector<vector<int>> dx = {
    {1,0,-1,0},
    {0,1,0,-1},
    {1,0,-1},
};

vector<vector<int>> dy = {
    {0,1,0,-1},
    {1,0,-1,0},
    {1,-1,0},
};



void robot_walk(int i,int j,int t){

    int dir = 0;

    while(!vis[i][j]){

        vis[i][j] = 1;

        if((vis[i+dy[t][dir]][j+dx[t][dir]] ||
        	(i+dy[t][dir] >= MAXN || i+dy[t][dir] < 0) ||
        	(j+dx[t][dir] >= MAXN || j+dx[t][dir] < 0))){
            dir++;
            dir %= dx[t].size();
        }

        i += dy[t][dir],j += dx[t][dir];

    }
}
