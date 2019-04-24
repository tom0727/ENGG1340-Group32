void print_graph (map <float,string> &datamap,float &income,float &expense,string x_header){
    cout<<"Income Percentage"<<endl;
    cout<<"A"<<endl;
    cout<<"I"<<endl;
    for (int j=19;j>=0;j--){
      cout<<"I";
      if (j%4==3){
        cout<<setw(3)<<(j+1)*5<<"%  ";
      }
      else{
        cout<<"      ";
      }
      for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
        if (itr->first<0){continue;}
        if ((itr->first/income)>=j*0.05){
          cout<<"**";
        }
        else{cout<<"  ";};
        cout<<"        ";
      }
      cout<<endl;
    }
   cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
   for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
      if (itr->first<0){continue;}
      cout<<setw(10)<<right<<itr->second;
   }



   cout<<endl;
   cout<<endl;
   cout<<"Expenditure Percentage"<<endl;
   cout<<"A"<<endl;
   cout<<"I"<<endl;
   for (int j=19;j>=0;j--){
     cout<<"I";
     if (j%4==3){
       cout<<setw(3)<<(j+1)*5<<"%  ";
     }
     else{
       cout<<"      ";
     }
     for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
       if (itr->first>0){continue;}
       if ((itr->first/income)<=j*0.05){
         cout<<"**";
       }
       else{cout<<"  ";};
       cout<<"        ";
     }
     cout<<endl;
   }
  cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
  for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
     if (itr->first>0){continue;}
     cout<<setw(10)<<right<<itr->second;
  }
  cout<<endl;
  cout<<endl;
}
