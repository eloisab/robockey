//
//  mrf_lib.c
//  
//
//  Created by Jesus Gallegos  on 11/23/15.
//
//

int state(int testing)
{

    //int state = buffer[0];
    int a;
    
    switch(testing) {
        case 160:
            a = 1;
            break;
        case 161:
            a = 2;
            break;
        case 162:
            a = 3;
            break;
        case 163:
            a = 4;
            break;
        case 164:
            a = 5;
            break;
        case 166:
            a = 6;
            break;
        case 167:
            a = 7;
            break;
    }
    return a;
}
