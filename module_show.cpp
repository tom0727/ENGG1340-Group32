void show(Record *&recordList,int &length_recordList)
{
  int page,count=0,currentpage=1;
  page = (length_recordList-1)/10+1;  //-1 is for when len=10;And page start from 1
  bool nextpage = true;
  while (nextpage==true && currentpage<=page) 
  {
    for (int i=0;i<10,count<length_recordList;i++,count++){
      cout<<i<<" "<<(recordList[count]).amount<<" "<<(recordList[count]).time<<" "<<(recordList[count]).type<<" "<<(recordList[count]).method<<" "<<(recordList[count]).remark<<" "<<endl;  //row_number amount time type method remark
    }
    cout << "Page " << currentpage << endl;
    cout << "To delete record 0, please enter d0, To edit record 0, please enter e0, otherwise enter 0" << endl;
    string choice;
    cin >> choice;
    if (isValidChoice(choice))
    {
      if (choice[0]=="0");
      else if (choice[0]=="d") {record_delete();}  //waiting for completion
      else if (choice[0]=="e") {record_edit();} //waiting for completion
    }
    //Questions:
    //1.How to delete or edit several records at the same page?
    //2.How to re-calculate the page and row_number after the deleted record?
    //3.Remember to edit the total income and expense!

    currentpage++;
    if (count<length_recordList)
    {
      cout << "To view next page, please enter 1, otherwise enter 0" << endl;
      cin >> nextpage;
    }
    else
    {
      cout << "--------The end of record--------" << endl;
      break;
    }
  }
}

bool isValidChoice(string &choice)
{
  if (choice.size()==1 && choice == "0") {return true;}
  else if (choice.len()==2 && (choice[0]=="d" or choice[0]=="e") && choice[1].isdigit()){return true;}
  // don't know if "isdigit()" function exist?
  else {return false;}
}

