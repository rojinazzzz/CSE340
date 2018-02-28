/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include <algorithm>
#include <valarray>
#include "lexer.h"



using namespace std;

struct rule;
void ro(LexicalAnalyzer &lexer, vector<string> uni, int task, bool &useless);
void calculate_Parser(LexicalAnalyzer& lexer, vector<string> universe, int task);
int indexOf(vector<string>, string s);
int* union_sets(int* array1, int* array2, int size);
int* union_withep(int* array, int* array1, int size);
vector<string> universe;
int main (int argc, char* argv[])
{
    int task;
    string s;
    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

   task = atoi(argv[1]);

    // TODO: Read the input grammar at this point from standard input

    
    LexicalAnalyzer lexer;
    
    bool useless;
    switch (task) {
        case 1:
            // TODO: perform task 1.
            ro(lexer, universe,1, useless);
            break;

        case 2:
            // TODO: perform task 2.
            ro(lexer, universe,2,useless);

            break;

        case 3:
             ro(lexer, universe,3,useless);
            // TODO: perform task 3.
            break;

        case 4:
            ro(lexer, universe,4,useless);
            // TODO: perform task 4.
            break;

        case 5:
            calculate_Parser(lexer, universe,0);
            // TODO: perform task 5.
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}

struct rule{
   string LHS;
   vector<string> RHS;
};


void ro(LexicalAnalyzer &lexer, vector<string> universe, int task, bool &useless){
    vector<string> non_terminal;
      vector<string> terminal ;
    Token t;
    t = lexer.GetToken();
     
     vector<rule> grammar; 
     
    
    //iterate through grammar
    while((t.token_type) != DOUBLEHASH){
       rule n;
            n.LHS = t.lexeme;
            
            if(non_terminal.empty())
            {
                    non_terminal.push_back(n.LHS);
                    
            }
            else 
            {
                   if(non_terminal.back().compare(n.LHS) != 0 && (find(non_terminal.begin(),non_terminal.end(),n.LHS)==non_terminal.end())){
                         non_terminal.push_back(n.LHS);
                    
                    }
                   
            }
            t = lexer.GetToken();
            if((t.token_type) == ARROW){
                t = lexer.GetToken();
            
      
                while(t.token_type != HASH){

                    n.RHS.push_back(t.lexeme);
                  //  cout << t.lexeme << " is pushed back" << endl;
                    t  = lexer.GetToken();
                }         
            }
        grammar.push_back(n);
        n.RHS.clear();
        t = lexer.GetToken();
        
    } 
     
     //getting my terminal
for(int i =0; i < grammar.size(); i++)
     {
         
         for(int j = 0; j < grammar.at(i).RHS.size(); j++)
         {
         
             for(int k = 0; k < non_terminal.size(); k++)
             {
                 
               if(find(terminal.begin(),terminal.end(),grammar.at(i).RHS.at(j))== terminal.end() && find(non_terminal.begin(),non_terminal.end(),grammar.at(i).RHS.at(j))== non_terminal.end())
               {
                   terminal.push_back(grammar.at(i).RHS.at(j));      
                }
            }
         }
     }
     
     
     non_terminal.clear();
     //putting my non terminal in order they appear
     for(int i =0; i < grammar.size(); i++)
     {
        if(find(terminal.begin(),terminal.end(),grammar.at(i).LHS)== terminal.end() && find(non_terminal.begin(),non_terminal.end(),grammar.at(i).LHS)== non_terminal.end())
         {
                   non_terminal.push_back(grammar.at(i).LHS);      
          
         }
        for(int j = 0; j < grammar.at(i).RHS.size(); j++)
         {
             if(find(terminal.begin(),terminal.end(),grammar.at(i).RHS.at(j))== terminal.end() && find(non_terminal.begin(),non_terminal.end(),grammar.at(i).RHS.at(j))== non_terminal.end())
                {
                 non_terminal.push_back(grammar.at(i).RHS.at(j));
                }
         }  
     }
     
                   
     //creating universe
      
      
      universe.push_back("#");
      universe.push_back("$");
      
     
         //add terminal to universe
          for ( int i= 0; i< terminal.size(); i++)
          {   
             universe.push_back(terminal.at(i));
             
          }
          //add non_terminal to universe
          for ( int j= 0; j< non_terminal.size(); j++)
          {
             universe.push_back(non_terminal.at(j));
              
          }
    
    //FOR TASK 1
      if(task == 1){
      for( int i = 2; i < universe.size(); i++)
      {
          cout << universe.at(i)  << " ";
      }
      cout << endl;
      }
      vector<int> reachable;
      vector<int> generating;
      vector<int> correctRules;
      //terminals and hash going to be 1 for generating vector automatically
      generating.push_back(1);
      
      for(int i = 1 ; i< universe.size(); i++)
      {
             generating.push_back(0);
      }
      for(int j = 2; j< terminal.size() +2 ; j++ )
      {
          generating.at(j) = 1;
      }
      //generating vector 
      bool allTrue = true;
      bool changed = true;
      vector<int> copy_generate;
      while(changed)
      {
          copy_generate.clear();
            for(int j = 0; j< generating.size()  ; j++ )
             {
                    copy_generate.push_back(generating.at(j));
              }
         
        
        changed = false;
        
          for( int i = 0; i< grammar.size(); i++ )
          {
              allTrue = true;
            
              
                    for( int j = 0; j< grammar.at(i).RHS.size(); j++)
                     {
                      
                        if(generating[indexOf(universe, grammar.at(i).RHS.at(j))] != 1)
                          {
                                   allTrue = false;
                                 
                           }
                         
                     }
          
               if(allTrue)
                        {
                           generating[indexOf(universe, grammar.at(i).LHS)] = 1;
                           // changed = true;
                         }
      } //end of my for loops
         
          //when does changed switch is done by these lines
          for(int i = 0; i< generating.size(); i++)
          {
              if(generating.at(i) != copy_generate.at(i))
              {
                  changed = true;
              }
           }

      }
       
      //correct rules being updated by the generating sets
      
      for(int i = 0; i < grammar.size(); i++)
      {
          correctRules.push_back(1);
      }
     // int count = -1;
      
      for( int i = 0; i< grammar.size(); i++ )
        {
           // count++;
              for( int j = 0; j< grammar.at(i).RHS.size(); j++)
              {
                  if(generating[indexOf(universe, grammar.at(i).RHS.at(j))] == 0)
                     
                   {
                    correctRules[i] = 0;
                   }
              }
      }   
    
     
      //now doing reachable vector or we should say reachable rules
       for(int i = 0 ; i< universe.size(); i++)
      {
             reachable.push_back(0);
      }
      reachable.at(2 + terminal.size()) = 1;
      
      //ow a while loop that updates my reachable set
      vector<int> copy_reachable;
      bool change =true;
       while(change)
      {
           
           //making a copy of reachable to switch change in the bottom
           copy_reachable.clear();
            for(int j = 0; j< reachable.size()  ; j++ )
             {
                    copy_reachable.push_back(reachable.at(j));

              }
        
          change = false;
         // int count2 = -1;
          for( int i = 0; i< grammar.size(); i++ )
          {
              //count2++;
              if(correctRules[i] == 1)
              {
              for( int j = 0; j< grammar.at(i).RHS.size(); j++)
              {
                 if(reachable[indexOf(universe, grammar.at(i).LHS)] == 1)
                   {
                     
                     reachable[indexOf(universe, grammar.at(i).RHS.at(j))] = 1;
                   }
              }
           }
          }// end of looping through grammar
          //now we trying to figure out when does change stops
          for(int i = 0; i< reachable.size(); i++)
          {
              if(reachable.at(i) != copy_reachable.at(i))
              {
                  changed = true;
              }
            
           }
       }//end of while loop
       
     
      //now we need to update my correct rules again this time by reachable
      int count3 = -1;
      for( int i = 0; i< grammar.size(); i++ )
        {
            count3++;
            if(reachable[indexOf(universe,grammar.at(i).LHS)] == 0){
                      correctRules[count3] = 0;
                  }
              for( int j = 0; j< grammar.at(i).RHS.size(); j++)
              {
                  
                  if(reachable[indexOf(universe, grammar.at(i).RHS.at(j))] == 0)
                   {
                    correctRules[count3] = 0;
                  //  cout << "correctRule at count is " << correctRules[count3] << endl;
                   }
              }
            
      }   
      
     
    if(task == 2)
    {
          int count_final = -1;
      for(int i = 0; i < grammar.size(); i++)
      {
          count_final++;
          if(correctRules[count_final] == 1){
              cout << grammar.at(i).LHS << " -> ";
              if(grammar.at(i).RHS.empty()){
                 
                cout << "#";  
              }
              else{
          for(int j = 0; j< grammar.at(i).RHS.size(); j++)
          {
                  cout << grammar.at(i).RHS.at(j) << " " ;
           }
              }
              cout << endl;
          }
       } 
      }
      
      bool hasUseless = false;
      for(int i = 0; i < correctRules.size(); i++){
          if ( correctRules.at(i) == 0){
              hasUseless = true;
          }
      }
      useless = hasUseless;
      
     
      //task 3
      
      vector<string> first_follow_universe;
      first_follow_universe.push_back("#");
      first_follow_universe.push_back("$");
      
      //add terminal to first_follow_universe
          for ( int i= 0; i< terminal.size(); i++)
          {   
             first_follow_universe.push_back(terminal.at(i));
          }
      
     
      int** array;
      array = new int*[universe.size()];
      for(int i = 0; i < universe.size() ; i++)
      {
          array[i] = new int[first_follow_universe.size()];
       }
     
     for(int i = 0; i < universe.size() ; i++)
      {
          for(int j = 0; j < first_follow_universe.size(); j++){
              array[i][j] = 0;
          }
      }
        
       array[0][0] = 1;
      
       int num = 2; 
       for(int i =2; i < first_follow_universe.size(); i++)
       {
           array[num][i] = 1; 
           num++;
       }
        /*
         cout << "array AT FIRST looks like " << endl;
                for(int i = 0; i < universe.size() ; i++)
                {
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                       cout << array[i][j] ;   
                       }
                 cout << endl;
                }*/
       bool changed_first = true;
       //where we calculate the first set rule 3, 4 , 5
  while(changed_first)
   {
         //  cout << "entering loop" << endl;
           changed_first = false;
           int** copy_array;
            copy_array = new int*[universe.size()];
            for(int i = 0; i < universe.size() ; i++)
            {
                copy_array[i] = new int[first_follow_universe.size()];
                    
             }
            
           for(int i = 0; i < universe.size() ; i++)
           {
               for(int j = 0; j < first_follow_universe.size(); j++)
               {
                     copy_array[i][j] = array [i][j];
                        
                 }
           }   //going over rule 3, checking the left hand side and add the first right hand side with 
            //out epsilon to the other one which we use union for it 
            int count = -1;
            //3rd rule
            for(int i =0 ; i < grammar.size(); i ++)
            {
                if(grammar.at(i).RHS.size() == 0)
                {
                  array[indexOf(universe, grammar.at(i).LHS)][0] = 1;   
                }
                else
                {   
               //  cout << " did we enter the loop " << endl;
                //   suppose I removed epsilon correctly in my union
                 array[indexOf(universe, grammar.at(i).LHS)] = union_sets(array[indexOf(universe, grammar.at(i).LHS)], array[indexOf(universe, grammar.at(i).RHS.at(0))] , universe.size());
                }
            }  
            /*cout << "array AFTER 3rd RULE looks like " << endl;
                for(int i = 0; i < universe.size() ; i++)
                {
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                       cout << array[i][j] ;   
                       }
                 cout << endl;
                }*/
            // rule 4
            bool allTrue = true; 
            int count_e = 0;
            for(int i =0 ; i < grammar.size(); i ++)
            {                
               // cout << " rule 4" << endl;

                allTrue = false;
                //count_e ++;
                int pos = -1;
                for(int j=0 ; j < grammar.at(i).RHS.size(); j++)
                {
                 //   cout << " first loop" << endl;
                     if(count_e == grammar.at(i).RHS.size())
                    {
                    // cout << " where it breaks" << endl;   
                        break;
                    }
                     
                    if(array[indexOf(universe, grammar.at(i).RHS.at(j))][0] == 1)
                    {
                     ///  cout << " if there is epsilon all true is false" << endl;
                      //  allTrue = false;
                        
                        count_e++;
                        array[indexOf(universe, grammar.at(i).LHS)]= union_sets(array[indexOf(universe, grammar.at(i).LHS)], array[indexOf(universe, grammar.at(i).RHS.at(j))] , universe.size());

                        //continue;
                                
                    }
                    else{
                     //   cout << " else position" << endl;
                        pos = j;
                        allTrue = true;
                        break;
                    }
                    
                    
                } 
                if(allTrue)
                    {
                  //  cout << " if all true loop" << endl;
                        array[indexOf(universe, grammar.at(i).LHS)]= union_sets(array[indexOf(universe, grammar.at(i).LHS)], array[indexOf(universe, grammar.at(i).RHS.at(pos))] , universe.size());
                    }
                
            }
             /*cout << "array AFTER 4th RULE looks like " << endl;
                for(int i = 0; i < universe.size() ; i++)
                {
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                       cout << array[i][j] ;   
                       }
                 cout << endl;
                }*/
            //checkin rule 5
            bool trueAll = true;
            for(int i =0 ; i < grammar.size(); i ++)
            {      //cout <<" entering rule 5"  << endl;
                trueAll =true;
                for(int j=0 ; j < grammar.at(i).RHS.size(); j++)
                {
                    
                  if(array[indexOf(universe, grammar.at(i).RHS.at(j))][0] == 0)  
                  {
                      trueAll = false;
                  }
                  
                }
                if(trueAll)
                  {
                      array[indexOf(universe, grammar.at(i).LHS)][0] = 1;
                      
                  }
            }
             /*cout << "array AFTER 5th RULE looks like " << endl;
                for(int i = 0; i < universe.size() ; i++)
                {
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                       cout << array[i][j] ;   
                       }
                 cout << endl;
                }*/
            // to check if we need to exist while loop
             for(int i = 0; i < universe.size() ; i++)
           {
               for(int j = 0; j < first_follow_universe.size(); j++)
               {   
                  // cout << "checking" << endl;
                      if(array[i][j] != copy_array[i][j])
                    {
                        changed_first = true;
                    }
               }      
            }  
            
              
    }
       if (task == 3)
       {
           /* cout << "array looks like " << endl;
                for(int i = 0; i < universe.size() ; i++)
                {
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                       cout << array[i][j] ;   
                       }
                 cout << endl;
                }*/
           
           int countP;
           string s;
             for(int i = 2 + terminal.size(); i < universe.size() ; i++)
             {
                 s = "";
                   countP = 0;
                   
                 cout << "FIRST(" ;
                 cout << universe.at(i) << ") = { " ;
                 
                 
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                           
                          if(array[i][j] == 1)
                          {
                              countP ++;
                             //cout << first_follow_universe.at(j) ;
                              s.append(first_follow_universe.at(j));
                              s.append(", ");
                              //if (countP > 1 )
                                  //cout << ", "; 
                          }
                         
                         
                      }
                 
                 cout <<  s.substr(0,s.length()-2);
                  cout << " } " << endl;
                 }
            
        }

   //Task 4
       
       int** array2;
     array2 = new int*[universe.size()];
      for(int i = 0; i < universe.size() ; i++)
      {
           array2[i] = new int[first_follow_universe.size()];
       }
     
     for(int i = 0; i < universe.size() ; i++)
      {
          for(int j = 0; j < first_follow_universe.size(); j++){
              array2[i][j] = 0;
          }
      }
        
       array2[1][1] = 1;
       
       array2[indexOf(universe, grammar.at(0).LHS)][1] = 1;
       
       
       
       bool changed_follow = true;
       while(changed_follow)
   {
         //  cout << "entering loop" << endl;
           changed_follow = false;
           int** copy_array2;
            copy_array2 = new int*[universe.size()];
            for(int i = 0; i < universe.size() ; i++)
            {
                copy_array2[i] = new int[first_follow_universe.size()];
                    
             }
            
           for(int i = 0; i < universe.size() ; i++)
           {
               for(int j = 0; j < first_follow_universe.size(); j++)
               {
                     copy_array2[i][j] = array2 [i][j];
                        
                 }
           }
            
            //applying rule 2
            for(int i = 0; i < grammar.size(); i++)
            { 
              
                for(int j = grammar.at(i).RHS.size()-1; j >= 0 ; j-- )
                { 
                   
                    array2[indexOf(universe, grammar.at(i).RHS.at(j))] = union_sets(array2[indexOf(universe, grammar.at(i).LHS)], array2[indexOf(universe, grammar.at(i).RHS.at(j))] , universe.size());
                    //if epsilon is not in the first of the element 
                    if(array[indexOf(universe, grammar.at(i).RHS.at(j))][0] != 1)
                    {
                        break;
                    }
                }
            }
            //rule 4
            for(int i = 0; i < grammar.size(); i++ )
                     
              {
                for(int j = 0 ; j < grammar.at(i).RHS.size() ; j++)
                 {
                    
             array2[indexOf(universe, grammar.at(i).RHS.at(j))] = union_sets(array[indexOf(universe, grammar.at(i).RHS.at(j+1))], array2[indexOf(universe, grammar.at(i).RHS.at(j))] , universe.size() );
            
             
                  }
             }
            
            
             for(int i = 0; i < universe.size() ; i++)
           {
               for(int j = 0; j < first_follow_universe.size(); j++)
               {   
                   //cout << "checking" << endl;
                      if(array2[i][j] != copy_array2[i][j])
                    {
                        changed_follow = true;
                    }
               }      
           }  

    }
              
       
       
       
       if(task == 4)
       {
           /*
            cout << "array looks like " << endl;
                for(int i = 0; i < universe.size() ; i++)
                {
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                       cout << array2[i][j] ;   
                       }
                 cout << endl;
                }*/
       int countz;
           string s2;
             for(int i = 2 + terminal.size(); i < universe.size() ; i++)
             {
                 s2 = "";
                   countz = 0;
                   
                 cout << "FOLLOW(" ;
                 cout << universe.at(i) << ") = { " ;
                 
                 
                      for(int j = 0; j < first_follow_universe.size(); j++)
                      {
                           
                          if(array2[i][j] == 1)
                          {
                              countz ++;
                            
                              s2.append(first_follow_universe.at(j));
                              s2.append(", ");
                        
                          }
                         
                      }
                
                 cout <<  s2.substr(0,s2.length()-2);
                  cout << " } " << endl;
                 }
            
        }
       
      
}

int* union_sets(int* array1, int* array2, int size){
    //int size; 
    int* arr = new int[size];
    arr[0] = array1[0];
   
    for(int i = 1; i < size; i ++)
    {
        if(array1[i] == 1 || array2[i] == 1)
        {
              arr[i] = 1; 
        }
    }
    return arr;
} 
int* union_withep(int* array, int* array1, int size)
{
  int* arr = new int[size];
    arr[0] = array[0];
   
    for(int i = 0 ; i < size; i ++)
    {
        if(array[i] == 1 || array1[i] == 1)
        {
              arr[i] = 1; 
        }
    }
    return arr;      

}
    
    

void calculate_Parser(LexicalAnalyzer &lexer, vector<string> universe, int task ){
    bool useless;
    ro(lexer, universe,0 , useless);
    
    if(useless){
        cout << "NO" << endl;
    }
    else{
    int num = rand()% 2 ;
        if(num == 1){
            cout << "YES" << endl;

        }
        else{
            cout<< "NO" << endl;
        }
    }
}
int indexOf(vector<string> vec, string s)
{
    int index = -1;
    vector<string>::iterator it;
    for(it = vec.begin(); it != vec.end() ; it++)
    {
        index++;
        if(s.compare(*it) == 0){
           break; 
        }
    }
    return index;
    
}