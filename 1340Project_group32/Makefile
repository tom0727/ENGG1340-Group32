user.o : user.cpp
	g++ -c $^

financial_report.o : financial_report.cpp
	g++ -c $^

record.o : record.cpp
	g++ -c $^

helper_function.o : helper_function.cpp
	g++ -c $^

main.o : main.cpp headerfile.h
	g++ -c -I . $<

full_function : user.o financial_report.o record.o helper_function.o main.o
	g++ -pedantic-errors -std=c++11 $^ -o $@
