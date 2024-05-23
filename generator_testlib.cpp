#include "testlib.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <utility>
#include <fstream>
#define TOGGLE(x, y) arr[x][y] = !arr[x][y]
#define ON(x, y) arr[x][y] = true
// #include <Bits.h>
// #include <bits/stdc++.h>

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


int adjacency(int x, int y, int direction, int dimensions, vector<vector<char>>& arr){
    int count = 0;
    if(x == dimensions-1 || y == dimensions-1 || x == 0 || y == 0){
        return 0;
    }

    for(int i=-1;i<=1;i++){
        if(arr[x+directions[(direction+i+8)%8].first][y+directions[(direction+i+8)%8].second]){
            // printf("This is why %d %d %d", direction, x+directions[(direction+i+8)%8].first, y+directions[(direction+i+8)%8].second);
            return 0;
        }

        if(direction%2==1){
            if(arr[x+directions[(direction+2+8)%8].first][y+directions[(direction+2+8)%8].second] && !arr[x+directions[(direction+3+8)%8].first][y+directions[(direction+3+8)%8].second]){
                return 0;
            }
            if(arr[x+directions[(direction+-2+8)%8].first][y+directions[(direction-2+8)%8].second] && !arr[x+directions[(direction-3+8)%8].first][y+directions[(direction-3+8)%8].second]){
                return 0;
            }

            
        }
    }
    if(arr[x][y]==7 && (arr[x+1][y-1]==7 || arr[x-1][y-1]==7)){
        // printf("HEREEEE!");
        
    }

    // for(int i=0;i!=8;i++){
    //     if(arr[x+directions[i].first][y+directions[i].second] !=0){
    //         if(direction==((i+1)%8) || (direction+1)%8 == i){
    //             return 0;
    //         }

    //     }
    // }
    return 1;
    // for(int i=-1;i!=1;i++){
    //     for(int j=-1;j!=1;j++){
    //         if(i==0 && j==0){
    //             continue;
    //         }
    //         if(arr[x+i][y+j]){
    //             if(std::find(directions.begin(), directions.end(), make_pair(i, j)) != directions.end()){
    //                 count +=1;
    //             }
    //         }
    //     }
    // }
}


// bool adjacent_to(int x, int y, int dimensions, vector<vector<char>>& arr){
//     int count = 0;
//     if(x == dimensions-1 || y == dimensions-1 || x == 0 || y == 0){
//         return true;
//     }

//     for(int i=-1;i!=1;i++){
//         for(int j=-1;j!=1;j++){
//             if(i==0 && j==0){
//                 continue;
//             }
//             if(arr[x+i][y+j]){
//                 count +=1;
//             }
//         }
//     }
//     // printf("%d\n", count);

//     return count > 1;
//     // if(x > 0 && arr+x*(dimensions+2)+y){
//     //     return true;
//     // }
//     // if(x < dimensions-1 && arr[x+1][y]){
//     //     return true;
//     // }
//     // if(y > 0 && arr[x][y-1]){
//     //     return true;
//     // }
//     // if(y < dimensions-1 && arr[x][y+1]){
//     //     return true;
//     // }
//     // return false;
// }

void generate_node(vector<vector<char>>& arr, vector<bitset<8>> &bits_arr, int incoming_dir, int dimensions, int og_x, int og_y, int start_len, int end_len, int curr_iteration, int max_iteration){
    // int centre = (dimensions+1)/2;
    // ON(centre, centre);
    // int og_x = centre, og_y = centre;
    if(curr_iteration > max_iteration){
        return;
    }
    unsigned char rand_char = rnd.next(0, 255);
    std::bitset<8> bitset(rand_char); 

    int opposite_dir = (incoming_dir+4)%8;
    for(int i = 0;i!=8;i++){
        if(bitset[i] && i != opposite_dir){
            int x = og_x, y = og_y;
            int max_len = 0;
            while(adjacency(x+directions[i].first, y+directions[i].second, i, dimensions, arr)){
                x += directions[i].first;
                y += directions[i].second;
                max_len += 1;
            }
            if(max_len >= 3){
                x = og_x;
                y = og_y;
                int len=rnd.next(max(start_len, max_len), max(max_len, end_len));
                // int len=rnd.next(start_len, end_len);
                
                for(int j=0;j!=len;j++){
                    
                    if(!adjacency(x+directions[i].first, y+directions[i].second, i, dimensions, arr)){
                        // printf("Here");
                        break;
                    }
                    x += directions[i].first;
                    y += directions[i].second;
                    ON(x, y);
                }
                arr[x][y] = 1;//3 + curr_iteration;
                if(curr_iteration < max_iteration){
                    generate_node(arr, bits_arr, i, dimensions, x, y, start_len/2 -1, end_len/2 -1, curr_iteration+1, max_iteration);
                }
            }
            
        }
    }
    

}


void generate_test(int dimensions, int seed, vector<bitset<8>> &bits_arr, int max_iteration, int len_1, int len_2, std::string fname = "test.txt"){
    rnd.setSeed(seed);
    // ofstream file(fname);
    vector<vector<char>> arr(dimensions+2, vector<char>(dimensions+2, false));
    int centre = (dimensions+1)/2;
    ON(centre, centre);
    int og_x = centre, og_y = centre;
    
    for(int i = 0;i!=8;i++){
        if(bits_arr[0][i]){
            int x = og_x, y = og_y;
            int len=rnd.next(len_1, len_2);

            // printf("Length: %d\n", len);

            for(int j=0;j!=len;j++){
                x += directions[i].first;
                y += directions[i].second;
                if(!adjacency(x, y, i,dimensions, arr)){
                    // arr[x-di][y] = 5;
                    // printf("Here %d %d", x, y);
                    break;
                }
                
                ON(x, y);
                if(j==len-1){
                    // arr[x][y] = 3;
                }
            }
            generate_node(arr, bits_arr, i, dimensions, x, y, len_1/2, len_2/2, 1, max_iteration);
            
        }
    }
    arr[centre][centre] = 1;//2;
    printf("%d\n",(dimensions-1)/2);
    for(int i = 0;i!=dimensions;i++){
        for(int j = 0;j!=dimensions;j++){
            // file << (int)arr[i+1][j+1];;
            printf("%d", (int)arr[i+1][j+1]);
            // if(arr[i+1][j+1])
            //     printf("1");
            // else
            //     printf("0");
        }
        printf("\n");
    }
    


    // bool arr[dimensions+2][dimensions+2];
    // for(int i = 1; i < dimensions+1; i++){
    //     for(int j = 1; j < dimensions+1; j++){
    //         arr[i][j] = rnd.next(0, 1);
    //     }
    // }


}
    
int main(int argc, char *argv[]){
    registerGen(argc, argv, 1);
    startTest(4);
    auto arr = vector<bitset<8>>(1, bitset<8>("00011010"));
    generate_test(201, 7, arr, 6, 40, 80, "test3.txt");
    startTest(1);
    arr = vector<bitset<8>>(1, bitset<8>("10101010"));
    generate_test(21, 2398, arr, 0, 10, 20, "test9.txt");

    startTest(2);
    arr = vector<bitset<8>>(1, bitset<8>("10000000"));
    generate_test(41, 7, arr, 1, 5, 10, "test4.txt");
    startTest(3);
    arr = vector<bitset<8>>(1, bitset<8>("00000001"));
    generate_test(41, 7, arr, 0, 5, 10, "test5.txt");
    startTest(5);
    arr = vector<bitset<8>>(1, bitset<8>("10101100"));
    generate_test(201, 4, arr, 2, 25, 30, "test7.txt");
    startTest(6);
    arr = vector<bitset<8>>(1, bitset<8>("10101001"));
    generate_test(1001, 1245, arr, 20, 380, 400, "test8.txt");
    startTest(7);
    arr = vector<bitset<8>>(1, bitset<8>("10100101"));
    generate_test(1001, 5084, arr, 20, 440, 460, "test8.txt");
    startTest(8);
    arr = vector<bitset<8>>(1, bitset<8>("11111111"));
    generate_test(1001, 3095, arr, 20, 200, 210, "test8.txt");
    startTest(9);
    arr = vector<bitset<8>>(1, bitset<8>("10101111"));
    generate_test(1001, 1725, arr, 20, 440, 460, "test8.txt");

    startTest(10);
    arr = vector<bitset<8>>(1, bitset<8>("10101111"));
    generate_test(601, 2398, arr, 20, 440, 460, "test8.txt");


}