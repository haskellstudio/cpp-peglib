/*
csv.cc
MIT License kangjoni76@gmail.com
*/
#include <peglib.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <fstream>

int col,row;
std::vector<std::string> a;
void push(std::string m){

    a.push_back(m);
}
void failClue(int col){
std::cout << "failed at col "<<col<<" row "<<row<<"\nError token:";
    for (int ss=0;ss<a.size();++ss){
        std::cout << a.at(ss);
    }
    std::cout <<std::endl; 
    for (int c=0;c<col;++c){
        std::cout <<" ";
        if (c==(col-1)){
            std::cout <<"^";
        }
    }
}
int main(int argc, const char** argv)
{

 if (argc < 2 || std::string("--help") == argv[1]) {
        std::cout << "usage: "<<argv[0]<<" [input]" << std::endl;
        return 1;
    }
    std::string line,content;
    std::ifstream file(argv[1]); 
    auto syntax = R"(
    FILE <- HDR ROW+
    HDR <- ROW 
    ROW <- QUOTED STRING QUOTED  (COMMA   QUOTED STRING QUOTED)* _?
    _     <-  ' ' / '\t' / '\r' / [ \t\r\n]+
    STRING <- < [ a-z,-_.A-Z0-9]+ > 
    COMMA <- ','
    QUOTED <- '"'
)";
row=0;
peglib::peg pg(syntax); 
pg["FILE"] = []( const std::vector<peglib::any>& v){  
};
pg["ROW"] = [](const char *s,size_t l, const std::vector<peglib::any>& v) mutable{  
    ++row;
    col=l;
    push(std::string(s,l));
};
    if (!file.is_open()) {
        perror("error while opening file");  file.close();
    }
    while(std::getline(file, line)) {
        content+=line;
    }

auto ret = pg.parse(content.c_str()); 
std::cout <<std::boolalpha << ret<<"\n";
if (!ret){ 
    failClue(col);
}
file.close();
return 0;
}

file.csv

"04.1.00003","Da2d3d1,2","DAD.02"
"04.2.00003","D a2d3d12","DAD_.,0-3"
"04.3.00003","Da2d 3d1,2","DAD02"
I hope this can be useful for other poeple for starting point.
