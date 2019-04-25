# ENGG1340-Group32
#### *Yang Yuezhi:3035603033 & Hu Zhenwei:3035533719* 

## Problem Statement and Project Ideas 
  
### Accounting system: (as referenced to TA Shumin’s idea)

Learning how to manage our financial status is an important lesson for all of us. More and more people choose to use digital tools to manage their wealth efficiently. In this idea, we target to build an accounting system to help people keep track of their income and expense. 
The system roughly include following functions:

### 1)    Multiuser management functionality:
This accounting system is designed for the use of multiple users. Each user could register for their own account and set their password according to the specific format. Then, they would have to log in to use the rest function of this system.<br><br>
**Assumption1:**  User could only access to this system via program **terminal**, they could not access to the user-information text file and programming code file of this system.<br><br>
**Assumption2:**  There is **no limit** on the total number of users and number of records owned by each user.<br><br>
**Assumption3:**  Each user would have a unique **username**. Creating accounts with the same username would be prohibited by the system.
<br><br>

### 2)    Discontinuous operating time:
When users log in to his account, his information will be **loaded** from his account file and stored in variables in the program. <br><br> Every time the user modifies his information, the system would modify the variables instead of the account file. <br><br> Whenever the user wants to log out, the information would then be **written** into the account file. This could avoid frequent access to the file which may cause low efficiency and long processing time.<br><br>**Assumption:** users will sign out and terminate the program after each operation.
<br><br>
### 3)    add records of income and expenses:
Users could add many attributes of each income or expenses record.<br><br>Attributes include basic information such as **amount, date, type, remarks**, etc.<br><br>This information will be stored inside the users' specific file after the program terminates and would be extracted from the file when program reactivate.<br><br>
The records could be **deleted and edited** at any time and file stored corresponding information would be updated accordingly.<br><br>
Users could view their records by **date, type, and account**; They could search for each **record** by its **date, type, account**, and other attributes.<br><br>Users may also provide incomplete information about each attribute and still able to search for records.
<br><br>
### 4) User Interface:
A total of **two** line user interfaces will be displayed during the execution of the program.<br><br>The first one is the login interface where users would input **username and password** to log in to the system. They can also **register** their account in this interface.<br><br>The second interface is the main **functionality displace interface** where users would choose to execute different functions of this system.<br><br> Assumption: users may input invalid input during their operation, which requires an input-protected system to block those invalid input and ask users to **re-enter** their input.<br><br>
The system would provide a **statistical report** of users’ financial state (e.g. monthly income and expenses, percentage of food expenses). The report would also be shown in the form of graphs.<br><br> 
The accounting system allows **budget setting**. The user would be able to set maximum expense. When expenses reach the budget, there should be an alert from the system.
<br><br>
### 5) Some notes on operating this system:
1. At most of the time, the system could be stopped and returned to the menu by inputting nothing and pressing Enter(except for adding records). <br><br>
2. The system allows **NOT CHANGING** the record by entering 0 when editing the records. It also allows **Searching from/until the lower/upper bound** by entering 0 when searching records by **Amount/Date**.  <br><br>
3. When showing the records, if the type/method/remark is **TOO LONG** or there are **TOO MANY** kinds of them, there might be problems in output formatting. In this project, we assume the users would not input too long or too many kinds of records.

