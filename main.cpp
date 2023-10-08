#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <list>
#include <limits>
#include <map>
#include <cmath>
#include <sstream>
#include <deque>
#include <utility>
#include <functional>
#include <fstream>
#include <cctype>
#include <limits>


using namespace std;

bool isStringDigits(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false; 
        }
    }
    return true; 
}

double StandardDeviation(const vector<double>& values, const double& average) {
    if (values.empty()) {
        return 0.0; 
    }
    vector<double> squaredDifferences(values.size());
    for (int i = 0; i < values.size(); ++i) {
        squaredDifferences[i] = pow(values[i] - average, 2);
    }

    double meanOfSquaredDifferences =accumulate(squaredDifferences.begin(), squaredDifferences.end(), 0.0) / squaredDifferences.size();

    double standardDeviation =sqrt(meanOfSquaredDifferences);

    return standardDeviation;
}


double datedifference(double end, double start, const vector<int>& endDate, const vector <int>& startDate){   //one or two days interval 
	//each vector three elements month/day/year
    double days;
	if (endDate.size() == 0){
        if (end == start)return 0.02;
		days = end - start;
        return days;
	}
	if (endDate[2] > startDate[2] || endDate[1] > startDate[1] || endDate[0] > startDate[0]){       //calling during midnight             
		days = end + 1 - start; 

		return days;
	}


	if (end == start) return 0.2;
    days = end - start;
    return days;  //in unit of per day 
}

double COS_datedifference(double end, double start, const vector<int>& endDate, const vector <int>& startDate){  //remember use hours 
    double days;
    if ((int)(end*10-start*10) % 10 < 1) return max(sin(M_PI*2*start - M_PI/2),0.01);
    if (endDate.size() == 0){
        days = max(sin(M_PI*2*start - M_PI/2),0.01);
        return days;
    }
    if (endDate[2] > startDate[2] || endDate[1] > startDate[1] || endDate[0] > startDate[0]){       //calling during midnight             
        days = max(cos(M_PI*2*(end +1) - M_PI / 2 ) - cos(M_PI*2 * start  - M_PI / 2 ),0.1); 

        return days;
    }


    if (end == start) return max(sin(M_PI*2*start - M_PI/2),0.01);
    days = max(cos(M_PI*2  * end  - M_PI / 2 ) - cos(M_PI*2*5 * start - M_PI / 2 ),0.01);
    return days;

}


double finaloutput(const double& lambda, const double& average, const double& endTime, const double& startTime, const vector <int> endDay, const vector <int> startDay ){
    //use the lambda 
    // y(start, end) =avg*time + lamda * integral(sin(x*2*pie/10 - pie/2 )) ends-start
    //               =avg*time - lambda *  2/pie * (cos(pie2x-pie/2)
    double x = average * datedifference(endTime,startTime,endDay,startDay) + lambda * (2/M_PI) * COS_datedifference(endTime,startTime,endDay,startDay);
    if (x>=0)return x;
    return 1;
}



int main(){
	/*
		Input Example:
		ID,Start Time Interval,End Time Interval,Start Date EST (For Calls & Email),End Date EST (For Email Only),Min of Queue Wait (s),Max of Queue Wait (s),Average of Queue Wait (s),Median of Queue Wait (s),Min of Call Duration (s),Max of Call Duration (s),Median of Call Duration (s),Average of Call Duration (s),Type,# of Calls / Emails
		0,0.69,0.25,4/19/2022,4/20/2022,826,826,826,826,,,,,EMAIL,1
		1,0.92,0.25,4/19/2022,4/20/2022,470,470,470,470,,,,,EMAIL,1
		2,0.96,0.25,4/19/2022,4/20/2022,400,400,400,400,,,,,EMAIL,1
		3,0.69,0.27,4/19/2022,4/20/2022,825,825,825,825,,,,,EMAIL,1
		4,0.75,0.27,4/19/2022,4/20/2022,765,765,765,765,,,,,EMAIL,1
		5,0.79,0.27,4/19/2022,4/20/2022,688,688,688,688,,,,,EMAIL,1
	*/

	//import phase

	vector <int> listid, listnumberOfCall, listminQueue, listmaxQueue, listavgQueue, listmedQueue, listminDuration, listmaxDuration, listmedianDuration, listavgDuration;
	vector <double> liststartTimeInterval, listendTimeInterval;
	vector <string> liststartDate, listendDate, listtype;

	//prediction cases
	vector <int> test_listid, test_listnumberOfCall, test_listminQueue, test_listmaxQueue, test_listavgQueue, test_listmedQueue, test_listminDuration, test_listmaxDuration, test_listmedianDuration, test_listavgDuration;
	vector <double> test_liststartTimeInterval, test_listendTimeInterval;
	vector <string> test_liststartDate, test_listendDate, test_listtype;


	const char* filename = R"(C:\Users\ziang\OneDrive\Desktop\data_participant.csv)";
	ifstream file(filename);



	if (! file.is_open()){
		cout << "Error" << endl;
	}

 	string line;
 	getline(file,line);

 	

    while (getline(file, line)) {
        string startDate, endDate, type, numberOfCall, id, minQueue, maxQueue, 
                avgQueue, medQueue, minDuration, maxDuration, medianDuration, avgDuration, startTimeInterval, endTimeInterval;

        stringstream ss(line);
        char comma; 

        getline(ss, id, ',');
        getline(ss, startTimeInterval, ',');
        getline(ss, endTimeInterval, ',');
        getline(ss, startDate, ',');
        getline(ss, endDate, ',');
        getline(ss, minQueue, ',');
        getline(ss, maxQueue, ',');
        getline(ss, avgQueue, ',');
        getline(ss, medQueue, ',');
        getline(ss, minDuration, ',');
        getline(ss, maxDuration, ',');
        getline(ss, medianDuration, ',');
        getline(ss, avgDuration, ',');
        getline(ss, type, ',');
        getline(ss, numberOfCall, ',');

        if(!numberOfCall.empty()){     //just need id startTime endtime startdate enddate type number      
	        listid.push_back(stoi(id));

            listnumberOfCall.push_back(stoi(numberOfCall));

	        liststartTimeInterval.push_back(stof(startTimeInterval));
	        listendTimeInterval.push_back(stof(endTimeInterval));


	        liststartDate.push_back(startDate);
	        listendDate.push_back(endDate);


	        listtype.push_back(type);
    	}else{

			test_listid.push_back(stoi(id));

            test_listnumberOfCall.push_back(0);

            test_liststartTimeInterval.push_back(stof(startTimeInterval));
            test_listendTimeInterval.push_back(stof(endTimeInterval));


            test_liststartDate.push_back(startDate);
            test_listendDate.push_back(endDate);


            test_listtype.push_back(type);

    	}
    }
 	file.close();

 	//organise                        call and email should be two models
 	//useful info

 	//turn date to list of month/day/year

 	vector<vector<int>> real_liststartDate;
    for (string a : liststartDate) {
        string time;
        vector<int> one;

        for (char b : a) {
            if (b == '/') {
                if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
                time = "";
            } else {
                time += b;
            }
        }
		if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
        real_liststartDate.push_back(one);
    }

    vector<vector<int>> real_listendDate;
    for (string a : listendDate) {
        string time;
        vector<int> one;

        for (char b : a) {
            if (b == '/') {
                if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
                time = "";
            } else {
                time += b;
            }
        }

       if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
        real_listendDate.push_back(one);
    }


    vector<vector<int>> real_test_liststartDate;
    for (string a : test_liststartDate) {
        string time;
        vector<int> one;

        for (char b : a) {
            if (b == '/') {
                if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
                time = "";
            } else {
                time += b;
            }
        }

       if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
        real_test_liststartDate.push_back(one);
    }


    vector<vector<int>> real_test_listendDate;
    for (string a : test_listendDate) {
        string time;
        vector<int> one;

        for (char b : a) {
            if (b == '/') {
              if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
                time = "";
            } else {
                time += b;
            }
        }

      if(isStringDigits(time)&& !time.empty())one.push_back(stoi(time));
        real_test_listendDate.push_back(one);
    }


    //start the modelling

    //statistic 
		//average of call 
	    //average of email
    	//the deviation of call
    	//the deviation of email

    vector <double> call_data; 
    vector <double> email_data; //in per 1 day 

    for(int i=0; i< listendTimeInterval.size(); i++){
    	if(listtype[i] == "CALL"){
        	double timeratio = (double) (listnumberOfCall[i]) / datedifference(listendTimeInterval[i], liststartTimeInterval[i], real_listendDate[i], real_liststartDate[i]) ;
        	call_data.push_back(timeratio);  

        
    	}else{
	    	double timeratio = (double) (listnumberOfCall[i]) / datedifference(listendTimeInterval[i], liststartTimeInterval[i], real_listendDate[i], real_liststartDate[i]) ;
	    	email_data.push_back(timeratio);
    	}
    }

    //average 
    double average_of_call_per_hour = accumulate(call_data.begin(), call_data.end(), 0.0) / call_data.size();

    double average_of_email_per_hour = accumulate(email_data.begin(), email_data.end(), 0.0) / email_data.size();

    //std 
    double std_of_call_per_hour = StandardDeviation(call_data, average_of_call_per_hour);
    double std_of_email_per_hour = StandardDeviation(email_data, average_of_email_per_hour);      //quite large

    //model based on mean, hot period additional plus

    // hot period modeling for email
    // hot period modeling for phone call   
    // potential:   Autoregressive Integrated Moving Average (ARIMA)  armadillo lib: pacman -S mingw-w64-x86_64-armadillo for msys2
    // day and night
    // the weight for this can be trained by existing data


    //by common sense, the phone call at noon will be busier 

    vector <double> lambda_call;        // y(start, end) =avg* time + lamda * integral(sin(x*2*pie - pie/2 )) ends-start
    vector <double> lambda_email;            //               =avg*time - lambda * 2/pie * (cos(pie2x-pie/2) - --------    )


    for(int i=0; i< listendTimeInterval.size(); i++){
        if(listtype[i] == "CALL"){
        double lambda = ((M_PI/2)*( average_of_call_per_hour*datedifference(listendTimeInterval[i], liststartTimeInterval[i], real_listendDate[i], real_liststartDate[i]) - (double)listnumberOfCall[i])) / COS_datedifference(listendTimeInterval[i], liststartTimeInterval[i], real_listendDate[i], real_liststartDate[i]);                                         
        lambda_call.push_back(lambda);
        //cout << listnumberOfCall[i] << " ";

        }else{
            double lambda = ((M_PI/2)*(average_of_email_per_hour*datedifference(listendTimeInterval[i], liststartTimeInterval[i], real_listendDate[i], real_liststartDate[i]) - (double)listnumberOfCall[i])) / COS_datedifference(listendTimeInterval[i], liststartTimeInterval[i], real_listendDate[i], real_liststartDate[i]);                              
            lambda_email.push_back(lambda);
       
            
        }
    }

        
    double final_lambda_call = accumulate(lambda_call.begin(), lambda_call.end(), 0.0) / lambda_call.size();
    double final_lambda_email = accumulate(lambda_email.begin(), lambda_email.end(), 0.0) / lambda_email.size();






    //outcome 


    const char* filePathout = R"(C:\Users\ziang\OneDrive\Desktop\data_output.csv)";                                                                                           //change here
    ofstream outputFile(filePathout);
    if (!outputFile.is_open()) {
        cerr << "Error output" << endl;
        return 1;
    }


    outputFile << "ID" <<","<< "# of Calls / Emails" << endl;


    //const double& lambda, const double& average, const double& endTime, const double& startTime, const vector <int> endDay, const vector <int> startDay
    for(int i = 0; i < test_listid.size();i++){
        if (listtype[i] == "EMAIL"){
            outputFile << i + listid.size() << "," << finaloutput(final_lambda_email, average_of_email_per_hour, test_listendTimeInterval[i],test_liststartTimeInterval[i],real_test_listendDate[i], real_test_liststartDate[i])<< endl;

        }
        if (listtype[i] == "CALL"){
            outputFile << i + listid.size() << finaloutput(final_lambda_call, average_of_call_per_hour, test_listendTimeInterval[i],test_liststartTimeInterval[i],real_test_listendDate[i], real_test_liststartDate[i]) << endl;
        }
    }


}