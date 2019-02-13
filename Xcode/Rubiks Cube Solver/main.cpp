#include <iostream>

#include "CubeDetector.hpp"
#include "CubeParser.hpp"
#include "FaceletCube.hpp"
#include "RubiksCube.hpp"
#include "Solver.hpp"

using namespace std;
using namespace cv;

/**
 *F\F’\F2：不变；
 *L\L’\L2：不变；
 *B\B’\B2：L和R不变，F<->B，D<->U；
 *R\R’\R2：F和B不变，D<->U，L<->R；
 *U\U’\U2：F和B不变，R->U->L->D->R   status = 1
 *          或L和R不变，B->U->F->D->B    status = -1；
 *D\D’\D2：F和B不变，R->D->L->U->R   status = 1
 *          或L和R不变，B->D->F->U->B   status = -1；
 * @param answer
 * @return Reordered Answer
 */

//char changeCenter(char last, char orig, int status){
//    char curr;
//    if(last == 'F'){
//        curr = orig;
//    }else if(last == 'L'){
//        curr = orig;
//    }else if(last == 'U'){
//        if(status == 1){
//            switch (orig){
//                case 'U':
//                    curr = 'L';
//                    break;
//                case 'R':
//                    curr = 'U';
//                    break;
//                case 'L':
//                    curr = 'D';
//                    break;
//                case 'D':
//                    curr = 'R';
//                    break;
//                case 'F':
//                    curr = 'F';
//                    break;
//                case 'B':
//                    curr = 'B';
//                    break;
//            }
//        }else if(status == -1){
//            switch (orig){
//                case 'U':
//                    curr = 'F';
//                    break;
//                case 'R':
//                    curr = 'R';
//                    break;
//                case 'L':
//                    curr = 'L';
//                    break;
//                case 'D':
//                    curr = 'B';
//                    break;
//                case 'F':
//                    curr = 'D';
//                    break;
//                case 'B':
//                    curr = 'U';
//                    break;
//            }
//        }
//    }else if(last == 'D') {
//        if (status == 1) {
//            switch (orig) {
//                case 'U':
//                    curr = 'R';
//                    break;
//                case 'R':
//                    curr = 'D';
//                    break;
//                case 'L':
//                    curr = 'U';
//                    break;
//                case 'D':
//                    curr = 'L';
//                    break;
//                case 'F':
//                    curr = 'F';
//                    break;
//                case 'B':
//                    curr = 'B';
//                    break;
//            }
//        } else if (status == -1) {
//            switch (orig) {
//                case 'U':
//                    curr = 'B';
//                    break;
//                case 'R':
//                    curr = 'R';
//                    break;
//                case 'L':
//                    curr = 'L';
//                    break;
//                case 'D':
//                    curr = 'F';
//                    break;
//                case 'F':
//                    curr = 'U';
//                    break;
//                case 'B':
//                    curr = 'D';
//                    break;
//            }
//        }
//    }else if(last == 'B'){
//        switch (orig){
//            case 'U':
//                curr = 'D';
//                break;
//            case 'R':
//                curr = 'R';
//                break;
//            case 'L':
//                curr = 'L';
//                break;
//            case 'D':
//                curr = 'U';
//                break;
//            case 'F':
//                curr = 'B';
//                break;
//            case 'B':
//                curr = 'F';
//                break;
//        }
//    }else if(last == 'R'){
//        switch (orig){
//            case 'U':
//                curr = 'D';
//                break;
//            case 'R':
//                curr = 'L';
//                break;
//            case 'L':
//                curr = 'R';
//                break;
//            case 'D':
//                curr = 'U';
//                break;
//            case 'F':
//                curr = 'F';
//                break;
//            case 'B':
//                curr = 'B';
//                break;
//        }
//    }else{
//        cout<<"error in answer"<<endl;
//        return '0';
//    }
//    return curr;
//}

//string Reorder(string answer) {
//   answer = "D2B2UF2LFR'LD2R2BR2L2UD2L2U'DR2D";
//   string str = answer.substr(0, answer.size());
//   for(unsigned int i = 0; i<answer.length(); i++){
//       if(answer.at(i) == '\0' || answer.at(i) == '\'') break;
//       else{
//           for(unsigned int j = i + 1; j<answer.length(); j++){
//               if(answer.at(j) == '\0' || answer.at(j) == '\'') break;
//               else{
//                   str.at(j) = changeCenter(answer.at(j), str.at(j), #STATUS#);
//               }
//           }
//       }
//   }
//   return str;
//}

int main(int argc, char *argv[]) {

    CubeDetector cubeDetector;
    string fileName = "/home/top/Desktop/7.jpg";
    cubeDetector.separate(fileName);
    string str = cubeDetector.this_face_color(cubeDetector.right, 1);
    cout<<str<<endl;

//
//    string faceletStrings[6] = {
//            "U:ROBYORORG", "D:GWWGRBBYR", "F:YWOOWOYGG", "B:WGWYYRBBY", "L:GRBGGBRYR", "R:YBOWBOOWW"
//    };
//
//    unsigned int status;
//
////    Parse the input and initialize FaceletCube
//    FaceletCube faceletCube;
//    CubeParser cubeParser;
//    if ((status = cubeParser.parseFacelets(faceletStrings, faceletCube)) != CubeParser::VALID) {
//        cout << cubeParser.ErrorText(status) << endl;
//        return 1;
//    }
//
//    // Validate the FaceletCube
//    RubiksCube cube;
//    if ((status = faceletCube.Validate(cube)) != FaceletCube::VALID) {
//        cout << faceletCube.ErrorText(status) << endl;
//        return 1;
//    }
//
//    // Cube is in a valid configuration at this point
//
//    // Initialize tables and solve
//    Solver solver;
//    solver.InitializeTables();
//    solver.Solve(cube);
//    //solver.answer为20步的答案
    return 0;
}	
