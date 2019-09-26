#include<bits/stdc++.h>

using namespace std;

int isKeyword(string buffer){
    char new_buffer[buffer.size() + 1];
	strcpy(new_buffer, buffer.c_str());
    char keywords[51][13] = {"abstract","assert", "boolean", "break",
                            "byte",	"case",	"catch", "char",
                            "class","const","continue","default",
                            "do","double","else","enum","extends",
                            "final","finally","float","for","goto",
                            "if","implements","import","instanceof",
                            "int","interface","long","native","new",
                            "package","private","protected","public",
                            "return","short","static","strictfp","super",
                            "switch","synchronized","this","throw",
                            "throws","transient","try","void","volatile","while", "String"};
    int i, flag = 0;

    for(i = 0; i < 51; ++i){
        if(strcmp(keywords[i], new_buffer) == 0){
            flag = 1;
            break;
        }
    }
 return flag;
}

int isInteger(string buffer){
    int flag = 1;
    int sz = buffer.size();
    for (int i = 0; i < sz; i++){
        int number = buffer[i] - 48;
        if(number < 0 || number > 9){
            flag = 0;
        }
    }
    return flag;
}

char ch, operators[] = "+-*/%=", parenthesis[] = "()", logic_operator[] = "^&|";
string buffer = "";
int line = 1, col = 1, pos = 1, cnt = 0;
int main(){
    ifstream fin("program1.txt");
    int i;

    if(!fin.is_open()){
        cout<<"error while opening the file\n";
        exit(0);
    }
    while(!fin.eof()){
        ch = fin.get();
        int flag = 0;
        for(i = 0; i < 6; ++i){
            if (ch == operators[i] && ch == '/'){
                char next = fin.get();
                if (next == '/'){
                    pos++;
                    string com;
                    getline(fin, com);
                    pos += com.size();
                    line++;
                    col = 1;
                    break;
                }
            }
            if(ch == operators[i]){
                cout<<ch<<" is operator   " << "Line " << line << ", Col " << col << ", Pos " << pos << "\n";
                col++;
                pos++;
                flag = 1;
                break;
            }
        }
        for (i = 0; i < 3; i++){
            if(ch == logic_operator[i]){
                cout<<ch<<" is logic operator  " << "Line " << line << ", Col " << col << ", Pos " << pos << "\n";
                flag = 1;
                col++;
                pos++;
            }
        }

        if(isalnum(ch) || ch == '.'){
            buffer += ch;
            col++, pos++, cnt++;
        }
        else if((ch == ' ' || ch == '\n' || ch == '(' || ch == ')' || ch == ';' || ch == ',' || flag == 1) && buffer.size() != 0){
            if (isInteger(buffer) == 1){
                cout<<buffer<<" is integer " << "Line " << line << ", Col " << col - cnt << ", Pos " << pos - cnt << "\n";
                cnt = 0;
            }
            else if(isKeyword(buffer) == 1){
                cout<<buffer<<" is keyword " << "Line " << line << ", Col " << col - cnt<< ", Pos " << pos - cnt << "\n";
                cnt = 0;
            }
            else{
                cout<<buffer<<" is identifier " << "Line " << line << ", Col " << col - cnt << ", Pos " << pos - cnt << "\n";
                cnt = 0;
            }
            buffer = "";
        }

        for (i = 0; i < 2; ++i){
            if (ch == parenthesis[i]){
                cout<<ch<<" is parenthesis  " << "Line " << line << ", Col " << col << ", Pos " << pos << "\n";
                col++;
                pos++;
            }
        }
        if (ch == '\n'){
            line++;
            col = 1;
        }
        if (ch == ' '){
            col++;
            pos++;
        }
    }
    fin.close();
    return 0;
}
