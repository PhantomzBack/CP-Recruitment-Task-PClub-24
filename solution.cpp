#include <vector>
#include <iostream>
#include <fstream>

#define OPP(dir) ((dir+4)%8)

using namespace std;

enum direction{
    U,
    UL,
    L,
    DL,
    D,
    DR,
    R,
    UR
};
vector<pair<int,int>> directions = {make_pair(0, -1), make_pair(-1, -1), make_pair(-1, 0), make_pair(-1, 1), make_pair(0, 1), make_pair(1, 1), make_pair(1, 0), make_pair(1, -1)};


bool check_line_along(vector<vector<char>>& arr, int x, int y, int dir){
    bool line = true;
        for(int j=1;j<=3;j++){
            if(arr[x+j*directions[dir].first][y+j*directions[dir].second] == '0'){
                line = false;
                // printf("Broke at %d", i);
                break;
            }
            else{
                // printf("It is %d %d %d\n", arr[x+j*directions[i].first][y+j*directions[i].second],x+j*directions[i].first, y+j*directions[i].second);
            }
        }
    return line;
}

/*This function is used to tell use whether or not a point has lines originating from it. We use the criteria of a line being atleast 4px long, and it must be present in more than two unique directions*/
bool detect_originating_point(vector<vector<char>>& arr, int x, int y){
    if (!arr[x][y]){
        return false;
    }
    int dir[4] = {0,0,0,0}, num_unique = 0, num_total = 0;
    for(int i = 0; i != 8 ; i++){
        
        bool line = check_line_along(arr, x, y, i);
        if(arr[x+1*directions[i].first][y+1*directions[i].second] != '0'){
            num_total+=1;
        }
        if(line){
            // num_total += 1;
            num_unique += 1-dir[i%4]; // this expression is non zero only the first time.
            dir[i%4] = 1; // Directions incremented by 4 are opposite to each other   
        }
    }
    // printf("%d %d", num_unique, num_total);
    if(num_unique>1 || (num_unique==1 && num_total==1)){
        
        return true;
    }
    return false;
}


long long moves(vector<vector<char>>& arr, int x, int y, int dir){
    // cout << "In moves with " << x << " " << y << " " << dir << "\n";
    int t;
    // cin >> t;
    /* Moves is the function to calculate number of chances it takes to travel along a certain direction */
    if (dir == -1)
    {
        long long moves_this = 0;
        int num_dirs = 1, num_unique_dirs = 1;
        int dirs[8] = {0,0,0,0,0,0,0,0};
        int unique_dirs[4] = {0, 0, 0, 0};

        for(int i = 0; i!=8;i++){
            if(1){
                int t_x = x, t_y = y;
                if(check_line_along(arr, t_x, t_y, i)){
                    if(i==0){
                        moves_this-=1;
                    }  
                    t_x += directions[i].first;
                    t_y += directions[i].second;
                    while(!detect_originating_point(arr, t_x, t_y)){
                        t_x += directions[i].first;
                        t_y += directions[i].second;
                    }
                    num_dirs += 1;
                    if(unique_dirs[i%4] == 0){
                        
                        moves_this+=3+moves(arr,  t_x, t_y, i);
                        // printf("Shosh: %d %d %d %d\n", moves(arr,  t_x, t_y, i),t_x, t_y, i);
                        num_unique_dirs++;
                        unique_dirs[i%4]=1;
                    }
                    else{
                        moves_this+=1+moves(arr,  t_x, t_y, i);
                    }
                    dirs[i] = 1;
                }
            }
            
        }

        return moves_this;
        
    }
    else{
        /*Here we are starting from origin and hence we need to check out all directions except dir*/
        long long moves_this = 1;
        int num_dirs = 1, num_unique_dirs = 1;
        int dirs[8] = {0,0,0,0,0,0,0,0};
        int unique_dirs[4] = {0, 0, 0, 0};
        
        dirs[OPP(dir)] = 1;
        unique_dirs[dir%4] = 1;
        for(int pl = 0; pl!=8;pl++){
            if(pl!=OPP(dir)){
                int t_x = x, t_y = y;
                
                if(check_line_along(arr, t_x, t_y, pl)){
                    int m;
                    
                    // scanf("%d", &m);
                    t_x += directions[pl].first;
                    t_y += directions[pl].second;
                    while(!detect_originating_point(arr, t_x, t_y)){
                        t_x += directions[pl].first;
                        t_y += directions[pl].second;
                    }
                    // printf("%d %d %d %d\n", t_x, t_y,pl);
                    num_dirs += 1;
                    if(pl!=dir){
                        if(unique_dirs[pl%4] == 0){
                            
                            moves_this+=3+moves(arr,  t_x, t_y, pl);
                            num_unique_dirs++;
                            unique_dirs[pl%4]=1;
                            
                        }
                        else{
                            // cout << "Here it is " << t_x << ", " << t_y << "\n";
                            moves_this+=1+moves(arr,  t_x, t_y, pl);
                        }
                        
                        dirs[pl] = 1;
                    }
                    else{
                        moves_this+=1+moves(arr,  t_x, t_y, pl);
                    }
                }
            }
            
            
        }
        if(num_dirs==1){
            return 1;
        }
        else{
            return moves_this;
        }
        // for(int i=0;i!=4;i++){
        //     if(dir%4!=i){
        //         moves+=
        //     }
        //     else{

        //     }
        // }



        

        
        
    }
    


}


int main(){
    int n;
    cin >> n;
    // fstream file("test9.txt");
    n=2*n+1;
    string text;
    vector<vector<char>> arr(n+2, vector<char>(n+2, '0'));
    vector<string> strarrarr(n+2, "");
    int i=0;
    for(int i=0;i!=n;i++){
            cin >> text;
            for(int j=0 ; j!=n ; j++){
                arr[j+1][i+1] = text[j];
            }
    }
    // printf("%d\n", (int)detect_originating_point(arr, 107, 92));
    // printf("%d\n", (int)detect_originating_point(arr, 107, 91));
    // printf("%d\n", (int)detect_originating_point(arr, 107, 90));
    // printf("It is %c haha and it is %ld", arr[0][0], moves(arr, (n+1)/2, (n+1)/2 ,-1)); moves(arr, 14, 28 ,direction::DL);//
    cout << moves(arr, (n+1)/2, (n+1)/2, -1);
    // cout  << "Dis it" << moves(arr, 14, 28 ,direction::DL) << "sd" << moves(arr, 39, 28 ,direction::R) << "sd" << moves(arr, 1, 28 ,direction::L) << "sd" << moves(arr, 25, 39 ,direction::DR) << "sd";
    // printf("It is %c haha and it is %ld", arr[0][0], moves(arr, 39, 28 ,direction::DL));

}