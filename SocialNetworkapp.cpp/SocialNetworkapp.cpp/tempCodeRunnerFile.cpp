#include<iostream>
#include<fstream>
using namespace std;
class object;
class posts;
class controller;
class pages;
class user;
class date;
class activity;
class postcontent;
class comments;
class memory;
class helper;
class helper {
public:
	static int stringlength(const char* str) {
		int stringlength = 0;
		for (const char* temp = str; *temp != '\0'; temp++) {
			stringlength++;
		}
		return stringlength;
	}
	static void stringcopy(char*& dest, const char* src) {
		char* tempdest = dest;
		for (const char* tempsrc = src; *tempsrc != '\0'; tempsrc++) {
			*tempdest++ = *tempsrc;
		}
		*tempdest = '\0';
	}
	static char* getstringfrombuffer(const char* buffer) {
		int strlen = stringlength(buffer);
		char* str = 0;
		if (strlen > 0) {
			str = new char[strlen + 1];
			stringcopy(str, buffer);
		}
		return str;
	}
	static int comparestring(const char* cstring1, const char* cstring2) {
		while (*cstring1 != '\0' && *cstring2 != '\0') {
			char c1 = *cstring1;
			char c2 = *cstring2;
			if (c1 >= 'a' && c1 <= 'z') {
				c1 += 32;
			}
			if (c2 >= 'a' && c2 <= 'z') {
				c2 += 32;
			}
			if (c1 < c2)
				return -1;
			if (c1 > c2)
				return 1;
			cstring1++;
			cstring2++;
		}
		if (*cstring1 == '\0' && *cstring2 != '\0') {
			return -1;
		}
		if (*cstring1 != '\0' && *cstring2 == '\0') {
			return 1;
		}
		return 0;
	}
};
class date
{
	int day;
	int month;
	int year;
public:
	static const int currentday;;
	static const int currentmonth;;
	static const int currentyear;;
	void currentdate() {
		cout << currentday << "/" << currentmonth << "/" << currentyear;
	}
	int getday() {
		return day;
	}
	int getmonth() {
		return month;
	}
	int getyear() {
		return year;
	}
	~date() {

	}
	void setdate(int d, int m, int y) {
		day = d;
		month = m;
		year = y;
	}
	void setday(int d) {
		day = d;
	}
	void setmonth(int m) {
		month = m;
	}
	void setyear(int y) {
		year = y;
	}
};
const int date::currentday = 17;
const int date::currentmonth = 4;
const int date::currentyear = 2024;


class object {
	char* id;
	const int maxsize = 10;
protected:
	posts** timeline;
	int index;
public:
	object() {
		id = nullptr;
		timeline = new posts * [maxsize];
		for (int i = 0; i < maxsize; i++) {
			timeline[i] = nullptr;
		}
		index = 0;
	}
	virtual char* getid() {
		return id;
	}
	virtual void printinfo() {

	}
	virtual void addtotimeline(posts*) {
	}
	virtual void printname() {

	}
	~object() {
		if (id)
			delete[] id;
		if (timeline)
			delete[] timeline;
	}
};

class comments {
	char* id;
	object* commentby;
	char* text;
	posts* postid;
public:
	comments() {
		id = nullptr;
		commentby = nullptr;
		text = nullptr;
		postid = nullptr;
	}
	void display() {
		cout << commentby->getid() << "\t" << text;
	}
	void setid(char* id) {
		id = helper::getstringfrombuffer(id);
	}
	void setcommentby(object* commentor) {
		commentby = commentor;
	}
	void settext(const char* mytext) {
		text = helper::getstringfrombuffer(mytext);
		text[helper::stringlength(mytext)] = '\0';
	}
	object* getcommentby() {
		return commentby;
	}
	char* gettext() {
		return text;
	}
	void setpostid(posts* ptr) {
		postid = ptr;
	}
	~comments() {
		delete[] id;
		delete[] text;
	}
};
class activity {
	int type;
	char* value;
	char** activities;
public:
	activity() {
		activities = new char* [4];
		activities[0] = helper::getstringfrombuffer("is feeling");
		activities[1] = helper::getstringfrombuffer("is thinking about");
		activities[2] = helper::getstringfrombuffer("is making");
		activities[3] = helper::getstringfrombuffer("is celebrating");
		type = 0;
		value = nullptr;
	}
	void settype(int t) {
		type = t;
	}
	void setvalue(const char* v) {
		value = helper::getstringfrombuffer(v);
		value[helper::stringlength(v)] = '\0';
	}
	int gettype() {
		return type;
	}
	char* getvalue() {
		return value;
	}
	char* getactivity()
	{
		return activities[type - 1];
	}
	void printactivity() {
		if (type == 1)
		{
			cout << "\nfeeling " << value << " : ";
		}
		else if (type == 2)
		{
			cout << "\nthinking about " << value << " : ";
		}
		else if (type == 3)
		{
			cout << "\nmaking " << value << " : ";
		}
		else if (type == 4)
		{
			cout << "\ncelebrating " << value << " : ";
		}
		else return;
	}
	~activity() {
		if (value) {
			delete[] value;
		}
		for (int i = 0; i < 4; ++i) {
			delete[] activities[i];
		}
		delete[] activities;
	}
};
class postcontent {
	comments** comment;
	int count;
	activity* activities;
public:
	postcontent() {
		activities = new activity();
		activities = 0;
		comment = new comments * [10];
		for (int i = 0; i < 10; i++) {
			comment[i] = nullptr;
		}
		count = 0;
	}
	void showcomments() {
		for (int i = 0; i < count; i++) {
			comment[i]->display();
		}
	}
	void showactivity() {
		activities->printactivity();
	}
	void addcomment(comments* ptr) {
		comment[count] = ptr;
		count++;
		cout << "the value of count " << count;
	}
	~postcontent() {
		for (int i = 0; i < count; ++i) {
			delete comment[i];
		}

		delete[] comment;
	}
};

class posts {
	char* id;
	char* title;
	object* sharedby;
	object** likedby;
	char* text;
	const int max = 10;
	int day;
	int month;
	int year;
	postcontent* content;
	activity* activities;
	comments** allcomments;
	int commentcount;
public:
	date* shareddate;
	void printdate()
	{
		cout << day << "/" << month << "/" << year;
	}
	posts() {
		id = nullptr;
		sharedby = nullptr;
		likedby = new object * [max];
		for (int i = 0; i < max; i++) {
			likedby[i] = nullptr;
		}
		allcomments = nullptr;
		text = nullptr;
		sharedby = 0;
		day = 17;
		month = 4;
		year = 2021;
		shareddate = 0;
		content = new postcontent;
		commentcount = 0;
	}
	void readdatafromfile(ifstream& fin) {
		char tempid[10];
		fin >> tempid;
		id = helper::getstringfrombuffer(tempid);
		fin.ignore();
		if (shareddate == nullptr)
		{
			shareddate = new date;
		}
		fin >> day;
		shareddate->setday(day);
		fin >> month;
		shareddate->setmonth(month);
		fin >> year;
		shareddate->setyear(year);
		fin.ignore();
		char temppost[100];
		fin.getline(temppost, 99);
		text = helper::getstringfrombuffer(temppost);
	}
	void setsharedby(object*& ptr) {
		sharedby = ptr;
	}
	object* getsharedby() {
		return sharedby;
	}
	char* gettext() {
		return text;
	}
	void setlikedby(object*& ptr)
	{
		if (likedby == 0)
		{
			likedby = new object * [12];
			for (int i = 0; i < 12; i++)
			{
				likedby[i] = nullptr;
			}
		}
		int i = 0;
		while (likedby[i] != nullptr)
			i++;
		likedby[i] = ptr;
	}
	void displaydate()
	{
		if (day == date::currentday && month == date::currentmonth && year == date::currentyear)
			cout << " (1h)\n";
		else if (day == date::currentday - 1 && month == date::currentmonth && year == date::currentyear)
			cout << " (1d)\n";
		else if (day == date::currentday - 2 && month == date::currentmonth && year == date::currentyear)
			cout << " (2d)\n";
		else if (day == date::currentday - 3 && month == date::currentmonth && year == date::currentyear)
			cout << " (3d)\n";
		else
			cout << " (" << day << "/" << month << "/" << year << ")\n";
	}


	void printlikedby()
	{
		cout << "post liked by:" << endl;
		for (int i = 0; likedby[i] != nullptr; i++)
		{
			likedby[i]->printinfo();
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	const char* getid() {
		return id;
	}
	int getday() {
		return day;
	}
	int getmonth() {
		return month;
	}
	int getyear() {
		return year;
	}
	void printcomments()
	{
		if (!allcomments) {
			return;
		}
		for (int i = 0; allcomments[i] != nullptr; i++)
		{
			allcomments[i]->getcommentby()->printname();
			cout << allcomments[i]->gettext() << endl;
		}
	}
	void setactivity(activity* ptr) {
		activities = ptr;
	}
	void printactivity() {
		if (!activities)
			return;
		cout << " " << activities->getactivity() << activities->getvalue() << " ";
	}
	void addcontent(comments* p) {
		content->addcomment(p);
	}
	void addcomment(comments* ptr) {
		if (allcomments == 0)
		{
			allcomments = new comments * [11];
			for (int i = 0; i < 11; i++)
			{
				allcomments[i] = nullptr;
			}
		}
		int i = 0;
		while (allcomments[i] != nullptr)
		{
			i++;
		}
		if (i == 10)
		{
			cerr << "no more comments can be added to the post!" << endl;
		}
		else
			allcomments[i] = ptr;
	}
	void postcomment(object* obj, const char* content)
	{
		cout << "\n--------------------------------------------------------------------------\n\n";
		cout << "command:\tpostcomment(" << id << ", " << content << ")\n";
		bool commentexists = false;
		for (int i = 0; i < commentcount; i++) {
			if (allcomments[i] != nullptr && helper::comparestring(allcomments[i]->gettext(), content) == 0 && allcomments[i]->getcommentby() == obj) {
				commentexists = true;
				break;
			}
		}
		if (commentexists) {
			return;
		}
		int index = -1;
		for (int i = 0; i < max; i++) {
			if (allcomments[i] == nullptr) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			allcomments[index] = new comments;
			allcomments[index]->settext(content);
			allcomments[index]->setcommentby(obj);
			commentcount++;
		}
		else {
			cout << "\ncomments list is full. cannot add more comments.\n";
		}
	}

	void printpost()
	{
		cout << endl;
		if (allcomments == nullptr)
		{
			cout << "no comments" << endl;
			return;
		}
		sharedby->printinfo();
		cout << " ";
		cout << text;
		displaydate();
		for (int i = 0; allcomments[i] != nullptr; i++)
		{
			allcomments[i]->getcommentby()->printname();
			cout << " : " << allcomments[i]->gettext() << endl;
		}

		cout << endl;
	}
	void settext(const char* ch) {
		if (text == 0) {
			text = new char[helper::stringlength(ch) + 1];
		}
		else {
			delete[] text;
			title = new char[helper::stringlength(ch) + 1];
		}
		helper::stringcopy(text, ch);
		text[helper::stringlength(ch)] = '\0';
	}
	virtual ~posts() {
		if (id)
			delete[] id;
		if (text)
			delete[] text;
	}
};
class memory :public posts {
	posts* obj;
public:
	memory(const char* ch, posts* o) {
		obj = o;
		this->settext(ch);
	}
	posts* getpostobj() {
		return obj;
	}
	~memory() {
		delete obj;
	}
};
class pages :public object {
	char* id;
	char* title;
protected:
	posts** timeline;
public:
	pages() {
		id = nullptr;
		title = nullptr;
		timeline = nullptr;
	}
	char* gettitle() {
		return title;
	}
	char* getid() {
		return id;
	}
	void addtotimeline(posts* p)
	{
		if (timeline == nullptr)
		{
			timeline = new posts * [11];
			for (int i = 0; i < 11; i++)
			{
				timeline[i] = nullptr;
			}
		}
		int index = 0;
		while (timeline[index] != nullptr)
		{
			index++;
		}
		if (index == 10)
		{
			cerr << "no more posts can be added to the timeline!" << endl;
		}
		else
			timeline[index] = p;
	}
	posts** gettimeline() {
		return timeline;
	}
	void printname()
	{
		cout << "\t\t" << title;
	}
	void viewtimeline()
	{
		cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
		cout << title << endl;
		for (int i = 0; timeline[i] != nullptr; i++)
		{
			cout << title;
			timeline[i]->printactivity();
			timeline[i]->displaydate();
			cout << "\t\"" << timeline[i]->gettext() << "\"" << endl;
			timeline[i]->printcomments();
			cout << endl;
		}
	}
	void readdatafromfile(ifstream& fin) {
		char tempid[10];
		char temptitle[100];
		fin >> tempid;
		fin.getline(temptitle, 99);
		id = helper::getstringfrombuffer(tempid);
		title = helper::getstringfrombuffer(temptitle);

	}
	void printinfo()
	{
		cout << id << " - " << title << endl;
	}
	~pages() {
		delete[] title;

	}
};
class user : public object {
	char* id;
	char* fname;
	char* lname;
	user** friendlist;
	pages** pagelist;
	memory** memories;
protected:
	posts** timeline;
public:
	user() {
		id = nullptr;
		fname = nullptr;
		lname = nullptr;
		friendlist = nullptr;
		pagelist = nullptr;
		timeline = nullptr;
		memories = nullptr;
	}
	void addtotimeline(posts* p)
	{
		if (timeline == 0)
		{
			timeline = new posts * [11];
			for (int i = 0; i < 11; i++)
			{
				timeline[i] = nullptr;
			}
		}
		int index = 0;
		while (timeline[index] != nullptr)
		{
			index++;
		}
		if (index == 10)
		{
			cerr << "no more posts can be added to the timeline!" << endl;
		}
		else
			timeline[index] = p;
	}
	void printheader() {
		cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
		cout << fname << " " << lname << " - timeline:" << endl << endl;
	}

	void printmemories() {
		if (memories != nullptr) {
			for (int i = 0; memories[i] != nullptr; i++) {
				printmemoryinfo(memories[i]);
			}
		}
	}

	void printmemoryinfo(memory* m) {
		cout << "--- " << m->getsharedby() << " shared a memory --- ";
		cout << "(";
		m->displaydate();
		cout << ")" << endl;
		cout << "\t\"" << m->gettext() << "\"" << endl;
		cout << "\t--- ";

		m->displaydate();
		cout << " ago";

		cout << " ~~~" << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
		cout << m->getsharedby();
		m->printactivity();
		cout << endl;
		cout << "shared date: ";
		m->displaydate();
		cout << "\t\"" << m->gettext() << "\"" << endl;
		m->printcomments();
		cout << endl;
		cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl;
	}

	void printregularposts() {
		for (int i = 0; timeline[i] != nullptr; i++) {

			if (timeline[i]->getsharedby() != nullptr)
			{
				timeline[i]->getsharedby()->printname();
			}
			timeline[i]->printactivity();
			cout << endl;
			cout << "shared date: ";
			timeline[i]->displaydate();
			cout << "\t\"" << timeline[i]->gettext() << "\"" << endl;
			timeline[i]->printcomments();
			cout << endl;
		}
	}
	void viewtimeline() {
		if (timeline == nullptr) {
			cout << fname << " " << lname << " has no posts!" << endl;
			return;
		}
		printheader();
		printmemories();
		printregularposts();

		cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	}
	void printinfo()
	{
		cout << id << " - \t" << fname << " " << lname << endl;
	}
	char* getid() {
		return id;
	}
	const char* getfname() {
		return fname;
	}
	const char* getlname() {
		return lname;
	}
	void printname() {
		cout << "\t\t" << fname << " " << lname;
	}
	void readdatafromfile(ifstream& fin) {
		char tempid[10];
		char tempfname[20];
		char templname[20];
		fin >> tempid;
		fin >> tempfname;
		fin >> templname;
		id = helper::getstringfrombuffer(tempid);
		fname = helper::getstringfrombuffer(tempfname);
		lname = helper::getstringfrombuffer(templname);
	}
	void sharememory(posts* ptr, const char* buffer)
	{
		if (memories == 0)
		{
			memories = new memory * [11];
			for (int i = 0; i < 11; i++)
			{
				memories[i] = nullptr;
			}
			int i = 0;
			for (i = 0; memories[i] != nullptr; i++)
				;
			if (i >= 10)
			{
				cerr << "no more memories can be shared!" << endl;
			}
			memories[i] = new memory(buffer, ptr);
		}
	}
	void addfriend(user* frienduser) {
		if (friendlist == nullptr) {
			friendlist = new user * [2];
			friendlist[0] = frienduser;
			friendlist[1] = nullptr;
		}
		else {
			int currentsize = 0;
			while (friendlist[currentsize] != nullptr) {
				currentsize++;
			}
			user** newfriendlist = new user * [currentsize + 2];
			for (int i = 0; i < currentsize; i++) {
				newfriendlist[i] = friendlist[i];
			}
			newfriendlist[currentsize] = frienduser;
			newfriendlist[currentsize + 1] = nullptr;
			delete[] friendlist;
			friendlist = newfriendlist;
		}
	}
	void likepage(pages* likedpage) {
		if (pagelist == nullptr) {
			pagelist = new pages * [2];
			pagelist[0] = likedpage;
			pagelist[1] = nullptr;
		}
		else {
			int currentsize = 0;
			while (pagelist[currentsize] != nullptr) {
				currentsize++;
			}
			pages** newpagelist = new pages * [currentsize + 2];
			for (int i = 0; i < currentsize; ++i) {
				newpagelist[i] = pagelist[i];
			}
			newpagelist[currentsize] = likedpage;
			newpagelist[currentsize + 1] = nullptr;
			delete[] pagelist;
			pagelist = newpagelist;
		}
	}
	void viewfriendlist() {
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << fname << " " << lname << " - friend list" << endl << endl;
		if (friendlist == nullptr) {
			cout << "no friends in the list." << endl;
		}
		else {
			for (int i = 0; friendlist[i] != nullptr; i++) {
				cout << friendlist[i]->getid() << " - " << friendlist[i]->fname << " " << friendlist[i]->lname << endl;
			}
		}
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	}
	void likepageslist() {
		cout << "---------------------------------------------------------------------------------------------------------------" << endl;
		cout << fname << " " << lname << " - liked pages" << endl << endl;
		if (pagelist == nullptr) {
			cout << "no liked pages." << endl;
		}
		else {
			for (int i = 0; pagelist[i] != nullptr; ++i) {
				cout << pagelist[i]->getid() << " - " << pagelist[i]->gettitle() << endl;
			}
		}
		cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	}
	void viewhomepage()
	{
		int minrequiredday = date::currentday - 3;
		int maxrequiredday = date::currentday;
		int requiredmonth = date::currentmonth;
		int requiredyear = date::currentyear;
		cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
		cout << fname << " " << lname << " - Homepage" << endl
			<< endl;
		for (int i = 0; timeline[i] != nullptr; i++)
		{
			if (timeline[i]->shareddate->getday() <= maxrequiredday && timeline[i]->shareddate->getday() >= minrequiredday && timeline[i]->shareddate->getmonth() == requiredmonth && timeline[i]->shareddate->getyear() == requiredyear)
			{
				if (timeline[i]->getsharedby() != nullptr)
				{
					timeline[i]->getsharedby()->printname();
				}
				timeline[i]->printactivity();
				cout << endl;
				cout << "Shared Date: ";
				timeline[i]->displaydate();
				cout << "\t\"" << timeline[i]->gettext() << "\"" << endl;
				timeline[i]->printcomments();
				cout << endl;
			}
		}
		for (int i = 0; friendlist[i] != nullptr; i++)
		{
			for (int j = 0; friendlist[i]->timeline[j] != nullptr; j++)
			{
				posts* p = friendlist[i]->timeline[j];
				if (p->shareddate->getday() <= maxrequiredday && p->shareddate->getday() >= minrequiredday && p->shareddate->getmonth() == requiredmonth && p->shareddate->getyear() == requiredyear)
				{
					cout << friendlist[i]->fname << " " << friendlist[i]->lname;
					p->printactivity();
					cout << endl;
					cout << "Shared Date: ";
					p->displaydate();
					cout << "\t\"" << p->gettext() << "\"" << endl;
					p->printcomments();
					cout << endl;
				}
			}
		}
		for (int i = 0; pagelist[i] != nullptr; i++)
		{
			posts** ptr = pagelist[i]->gettimeline();
			if (ptr == nullptr)
			{
				continue;
			}
			for (int j = 0; ptr[j] != nullptr; j++)
			{
				if (ptr[j]->shareddate->getday() <= maxrequiredday && ptr[j]->shareddate->getday() >= minrequiredday && ptr[j]->shareddate->getmonth() == requiredmonth && ptr[j]->shareddate->getyear() == requiredyear)
				{
					cout << pagelist[i]->gettitle();
					ptr[j]->printactivity();
					cout << endl;
					cout << "Shared Date: ";
					ptr[j]->displaydate();
					cout << "\t\"" << ptr[j]->gettext() << "\"" << endl;
					ptr[j]->printcomments();
					cout << endl;
				}
			}
		}
		cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	}
	posts** gettimeline()
	{
		return timeline;
	}
	/*void viewmemories() {
		posts** p = this->gettimeline();
		int postcount = 0;
		while (p[postcount] != nullptr) {
			postcount++;
		}
		for (int i = 0; i < postcount - 1; i++) {
			for (int j = 0; j < postcount - i - 1; j++) {
				if (p[j]->shareddate->getyear() == p[i]->getyear()&& {
					posts* temp = p[j];
						p[j] = p[j + 1];
						p[j + 1] = temp;
				}
			}
		}
		cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
		cout << "we hope you enjoy looking back and sharing your memories on facebook, from the most recent to those long ago." << endl;
		for (int i = 0; i < postcount; i++) {
			cout << "\non this day" << endl;
			int daysdiff = date::currentday - p[i]->shareddate->getday();
			int monthsdiff = date::currentmonth - p[i]->shareddate->getmonth();
			int yearsdiff = date::currentyear - p[i]->shareddate->getyear();

			if (yearsdiff > 0) {
				cout << yearsdiff << " year";
				if (yearsdiff != 1)
					cout << "s";
				cout << " ago" << endl;
			}
			else if (monthsdiff > 0) {
				cout << monthsdiff << " month";
				if (monthsdiff != 1)
					cout << "s";
				cout << " ago" << endl;
			}
			else if (daysdiff > 0) {
				cout << daysdiff << " day";
				if (daysdiff != 1)
					cout << "s";
				cout << " ago" << endl;
			}
			else {
				cout << "1h ago" << endl;
			}
			cout << fname << " " << lname;
			p[i]->printactivity();
			cout << endl;
			cout << "\t\"" << p[i]->gettext() << "\"" << endl;
			p[i]->printcomments();
			cout << endl;
		}
		cout << "--------------------------------------------------------------------------------------------------------------" << endl;
	}*/

	~user() {
		delete[] fname;
		delete[] lname;
		delete[] friendlist;
		delete[] pagelist;
	}
};

class controller {
	user** allusers;
	pages** allpages;
	posts** allposts;
	activity** activities;
	comments** allcomments;
	int totalusers;
	int totalpages;
	int totalposts;
	int totalactivities;
	int totalcomments;
public:
	controller() {
		allusers = nullptr;
		allpages = nullptr;
		allposts = nullptr;
		allcomments = nullptr;
		totalusers = 0;
		totalpages = 0;
		totalposts = 0;
		totalactivities = 0;
	}
	void loadallusers() {
		int total;
		ifstream fin("users.txt");
		if (!fin.is_open()) {
			cerr << "there is an error in opening the file ";
			exit(1);
		}
		fin >> total;
		totalusers = total;
		allusers = new user * [total];
		for (int i = 0; i < total; i++) {
			allusers[i] = new user();
			allusers[i]->readdatafromfile(fin);
		}
	}
	void loadallpages() {
		int total;
		ifstream fin("pages.txt");
		if (!fin.is_open()) {
			cerr << "there is an error in opening the file";
			exit(1);
		}
		fin >> total;
		totalpages = total;
		allpages = new pages * [total];
		for (int i = 0; i < total; i++) {
			allpages[i] = new pages();
			allpages[i]->readdatafromfile(fin);
		}
	}
	user* searchuserbyid(const char* userid) {
		for (int i = 0; i < totalusers; i++) {
			if (helper::comparestring(allusers[i]->getid(), userid) == 0) {
				return allusers[i];
			}
		}
		return nullptr;
	}
	pages* searchpagebyid(const char* pageid) {
		for (int i = 0; i < totalpages; i++) {
			if (helper::comparestring(allpages[i]->getid(), pageid) == 0) {
				return allpages[i];
			}
		}
		return nullptr;
	}
	posts* searchpostbyid(const char* postid)
	{
		for (int i = 0; i < totalposts; i++)
		{
			if (helper::comparestring(allposts[i]->getid(), postid) == 0)
			{
				return allposts[i];
			}
		}
		return nullptr;
	}
	void linkusersandpages() {
		ifstream fin("usersfriendsandlikedpages.txt");
		if (!fin.is_open()) {
			cerr << "there is an error in opening the file ";
			exit(1);
		}
		char userid[10];
		while (fin >> userid) {
			if (helper::comparestring(userid, "-1") == 0) {
				break;
			}
			user* temp = searchuserbyid(userid);
			char friendid[10];
			while (fin >> friendid && helper::comparestring(friendid, "-1") != 0) {
				user* frienduser = searchuserbyid(friendid);
				if (frienduser != nullptr) {
					temp->addfriend(frienduser);
				}
			}
			char pageid[10];
			while (fin >> pageid && helper::comparestring(pageid, "-1") != 0) {
				pages* likedpage = searchpagebyid(pageid);
				if (likedpage != nullptr) {
					temp->likepage(likedpage);
				}
			}
		}
		fin.close();
	}
	void loadallposts() {
		ifstream fin("posts.txt");
		if (!fin.is_open()) {
			cerr << "error opening the file\n";
			exit(1);
		}
		fin >> totalposts;
		allposts = new posts * [totalposts];
		char tempid[10];
		const char* sharedby;
		for (int i = 0; i < totalposts; i++) {
			allposts[i] = new posts;
			allposts[i]->readdatafromfile(fin);
			fin >> tempid;
			sharedby = helper::getstringfrombuffer(tempid);
			object* ptr = searchuserbyid(tempid);
			if (!ptr)
				ptr = searchpagebyid(tempid);
			if (ptr != nullptr) {
				allposts[i]->setsharedby(ptr);
				ptr->addtotimeline(allposts[i]);
			}

			while (true) {
				fin >> tempid;
				if (helper::comparestring(tempid, "-1") == 0)
					break;
				ptr = searchuserbyid(tempid);
				if (!ptr) {
					ptr = searchpagebyid(tempid);
				}
				if (ptr != nullptr) {
					allposts[i]->setlikedby(ptr);
					ptr->addtotimeline(allposts[i]);
				}
			}
		}

		fin.close();
	}
	void loadallcomments() {
		ifstream fin("comments.txt");
		if (!fin.is_open()) {
			cerr << "therre is an error in opening the file ";
			exit(1);
		}
		fin >> totalcomments;
		if (allcomments == nullptr) {
			allcomments = new comments * [totalcomments + 1];
		}
		char buffer[100];
		int i = 0;
		for (i = 0; i < totalcomments; i++) {
			fin >> buffer;
			allcomments[i] = new comments;
			allcomments[i]->setid(buffer);
			fin >> buffer;
			posts* temp = searchpostbyid(buffer);
			allcomments[i]->setpostid(temp);
			fin >> buffer;
			object* temp2 = nullptr;
			temp2 = searchuserbyid(buffer);
			if (temp2 == nullptr)
			{
				temp2 = searchpagebyid(buffer);
			}
			allcomments[i]->setcommentby(temp2);
			fin.getline(buffer, 99);
			allcomments[i]->settext(buffer);
			temp->addcomment(allcomments[i]);
		}
		allcomments[i] = nullptr;

	}
	void loadallactivities() {
		ifstream fin("activities.txt");
		if (!fin.is_open()) {
			cerr << "there is an error in opening the file ";
		}
		int type = 0;
		char pid[10];
		int total;
		fin >> total;
		totalactivities = total;
		for (int i = 0; i < total; i++) {
			activity* ptr = new activity();
			fin >> pid;
			posts* postptr = searchpostbyid(pid);
			fin >> type;
			ptr->settype(type);
			char temp[100];
			fin.getline(temp, 99);
			ptr->setvalue(temp);
			postptr->setactivity(ptr);
		}
	}
	void loadalldata() {
		loadallusers();
		loadallpages();
		linkusersandpages();
		loadallposts();
		loadallcomments();
		loadallactivities();
	}
	~controller() {
		if (allpages != nullptr) {
			for (int i = 0; i < totalpages; i++) {
				delete allpages[i];
			}
			delete[] allpages;
		}
		if (allusers != nullptr) {
			for (int i = 0; i < totalusers; i++) {
				delete allusers[i];
			}
			delete[] allusers;
		}
		delete[] allposts;
	}

	void run() {
		loadalldata();
		const char* currentuserid = "u7";
		user* currentuser = searchuserbyid(currentuserid);
		if (currentuser != nullptr) {
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "set current system date ";
			date currentdate;
			currentdate.currentdate();
			cout << "\n-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "command :\t set current user " << currentuserid << endl;
			cout << currentuser->getid() << " successfully set as current user \n\n" << endl;
			cout << "command : view friend list " << endl;
			currentuser->viewfriendlist();
			cout << "command: view liked pages" << endl;
			currentuser->likepageslist();
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << "command\t\t\tview timeline\n";
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			cout << currentuser->getfname() << " " << currentuser->getlname() << "-timeline" << "\n";
			currentuser->viewtimeline();
			posts* post = searchpostbyid("post5");
			cout << "command:\tviewlikedlist (" << post->getid() << ")\n\n";
			post->printlikedby();
			cout << "command:\t\tlikepost(" << post->getid() << ")\n";
			cout << "command:\t\tviewlikedlist(" << post->getid() << ")\n\n";
			object* ptr = currentuser;
			post->setlikedby(ptr);
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			post->printlikedby();
			const char* pageid = "p1";
			cout << "command:\t\tviewpage(" << pageid << ")";
			pages* currentpage = searchpagebyid(pageid);
			currentpage->viewtimeline();
			cout << "--------------------------------------------------------------------------------------------------------------" << endl;
			cout << "command:\t\tview home" << endl;
			cout << "--------------------------------------------------------------------------------------------------------------" << endl;
			currentuser->viewhomepage();
			const char* postid = "post5";
			posts* currentpost = searchpostbyid(postid);
			const char* commenttobeadded = "good luck for your result";
			int viewpost1 = 3;
			posts* post2 = allposts[viewpost1];
			post2->postcomment(currentuser, "good luck for your result");
			post2->printpost();
			int viewpost2 = 7;
			posts* post3 = allposts[viewpost2];
			post3->postcomment(currentuser, "thanks for the wishes");
			post3->printpost();
			cout << "-------------------------------------------------------------------------------------------------------------" << endl;
			//currentuser->viewmemories();
			int viewpost3 = 9;
			posts* post4 = allposts[viewpost3];

			memory* memoryptr = new memory("never thought i will be specialist in this field", post4);

			currentuser->addtotimeline(memoryptr);

			currentuser->viewtimeline();

			delete[] memoryptr;

		}
		else {
			cout << "error: user with id \"" << currentuserid << "\" not found!" << endl;
		}
	}
};
int main() {
	controller mainapp;
	mainapp.run();
}