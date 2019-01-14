//
//  string_tools.cpp
//  Music Library Program
//
//  Created by Kim GT  on 14/01/2019.
//  Copyright © 2019 Kim GT . All rights reserved.
//

#include "string_tools.hpp"

int read_line(FILE *fp, char str[], int n){
    int ch, i = 0;
    while((ch=fgetc(fp)) != '\n' && ch != EOF)
        if(i<n-1)
            str[i++] = ch;
    str[i] = '\0' ;
    return i ;
}
