#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum troll_type{LeftTroll, RightTroll, Other};

struct user_data {
	int userId;
	vector<int> tweetIds;
	map<int, int> attrs;
	troll_type result;
};

struct tweet_data {
	int tweetId, userId;
	map<int, int> attrs;
	troll_type result;
	
	tweet_data(int tweetId, int userId) {
		this->tweetId = tweetId;
		this->userId = userId;
	}
};

vector<string> attrs;

// User data set: user_id -> user_data
map<int, user_data> userData;

// All tweet data
vector<tweet_data> tweetData;

string stmp;

void getAttrs() {
	int commaCount = 0, i;
	for (i = 0; ; i ++) {
		if (stmp[i] == ',') commaCount++;
		if (commaCount == 2) break;
	}
	int lastComma = i;
	for (i = i + 1; i < stmp.size(); i ++) {
		if (stmp[i] == ',') {
			string attr;
			for (int j = lastComma + 1; j < i; j ++) {
				attr += stmp[j];
			}
			lastComma = i;
			attrs.push_back(attr);
		}
	}
}

void readData() {
	char ctmp;
	cin>>stmp;
	getAttrs();
	
	int tweetId, userId;
	while (cin>>tweetId>>ctmp) {
		cin>>userId>>ctmp;
		userData[userId].tweetIds.push_back(tweetId);
		tweet_data newData(tweetId, userId);
		for (int i = 0; i < attrs.size(); i ++) {
			int value;
			// Read value and a comma
			cin>>value>>ctmp;
			newData.attrs[i] = value;
			userData[userId].attrs[i] += value;
		}
		
		string result;
		cin>>result;
		newData.result = result == "Other" ? Other : result == "LeftTroll" ? LeftTroll : RightTroll;
		
		tweetData.push_back(newData);
		userData[userId].result = newData.result;
	}
}

void outputData() {
	cout<<stmp<<endl;
	for (int i = 0; i < tweetData.size(); i ++) {
		tweet_data data = tweetData[i];
		cout<<data.tweetId<<","<<data.userId<<',';
		for (int j = 0; j < attrs.size(); j ++)
			cout<<userData[data.userId].attrs[j]<<',';
		switch (userData[data.userId].result) {
			case LeftTroll: cout<<"LeftTroll"<<endl; break;
			case RightTroll: cout<<"RightTroll"<<endl; break;
			case Other: cout<<"Other"<<endl; break;
		}
	}
}

int main() {
	freopen("test-best200-header.csv", "r", stdin);
	freopen("test-best200-header-after.csv", "w", stdout);
	ios::sync_with_stdio(false);

	readData();
	outputData();
	
	return 0;
}
