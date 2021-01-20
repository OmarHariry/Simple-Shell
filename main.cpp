#include <iostream>
#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h>
#include<cstdio>
using namespace std;
char directory[100];

void writeToLog(int n)
{
ofstream log("LogFile.txt",ios_base::app|ios_base::out);
log<<"Child Process Was Terminated"<<endl;
}
int main()
{
       string command="";
       do{
       cout << "Enter Your Command"<<endl;
       getline(cin,command);

       vector<string>tokens;
        stringstream check1(command);
   string s;
   while(getline(check1,s,' '))
   {
     tokens.push_back(s);
   }
   const char* arr[100];
   for(int i=0;i<tokens.size();++i){
    if(tokens[i].size()>1)
        arr[i] = tokens[i].c_str();
    else
        arr[i]= NULL;
   }
   if(tokens[0].compare("exit")==0){
    cout<<"Exit Successfully!";
           exit(0);
   }
     bool hasAnd = false;
  if(command.find("&")!=string::npos){
    hasAnd=true;
    command = command.substr(0,command.find("&")-1);
  }

     pid_t pid = fork();
    if(pid<0){
        cout<<"Fork Failed"<<endl;
    }
    else{
     if(pid ==0){

        if(command.find("cd")!=string::npos){
            if(tokens[1].size() > 1)
                chdir(arr[1]);
            else
                chdir("..");
        cout<<getcwd(directory,100)<<endl;
      }
      else{
       execvp(arr[0],(char*const*)arr);
      }
     }
     else{
      if(hasAnd == false){
        signal(SIGCHLD,writeToLog);
        wait(NULL);
    }
     }
}
    }while(command!="0");
    return 0;
}
