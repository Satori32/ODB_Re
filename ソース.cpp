#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>
#include <algorithm>

class ObjectDatabase {
public:
	struct Parson{
		std::string ID;
		std::map < std::string, std::string> P;
		
		bool Add(const std::string& ID, const std::string& D) {
			P[ID] = D;
			return true;
		}
		bool Erase(const std::string& ID) {
			P.erase(ID);
			return true;
		}
		std::map < std::string, std::string>::iterator begin() {
			return P.begin();
		}
		std::map < std::string, std::string>::iterator end() {
			return P.end();
		}

	};
	typedef std::shared_ptr<Parson> SharedParson;
	struct Relation
	{
		struct Arrow
		{
			std::shared_ptr<Parson> To;
			std::intmax_t Weight = 0;
			std::string Origin;
			bool SetOrigin(const std::string& In) {
				Origin = In;	
			}
			bool SetWeight(std::intmax_t In) {
				Weight = In;
			}

		};
		std::vector<Arrow> R;
		bool PushArrow(std::shared_ptr<Parson> P, std::intmax_t W) {
			R.push_back({ P,W });
			return true;
		}



		bool PopArrow(Arrow A) {
			for (auto i = R.begin(); i != R.end(); i++) {
				if (i->To == A.To) {
					R.erase(i);
					return true;
				}
			}
			return false;
		}

		std::vector<Arrow>::iterator begin() {
			return R.begin();
		}
		std::vector<Arrow>::iterator end() {
			return R.end();
		}
	};

	struct Info
	{
		std::string Info;
		std::map < std::string, std::string > Data;
	};

	struct ParsonalData//what are you need the one page.
	{
		std::shared_ptr<Parson> P;
		std::map<std::string, Info> Info;
		Relation R;		
	};
	
	typedef std::shared_ptr<ParsonalData> SharedParsonData;

	bool New(const std::string& ID) {
		SharedParson P = std::make_shared<Parson>();
		P->ID = ID;
		return this->Push(P);
	}

	bool Push(std::shared_ptr<Parson> P) {
		for (auto i = D.begin(); i != D.end(); i++) {
			if (i->get()->P->ID == P->ID) {
				return false;
			}
		}

		//SharedParsonData X{ P,{}, {} };//where is to memorylize? ah null? bakayarou!

		SharedParsonData Z = std::make_shared<ParsonalData>(P, Info(),ObjectDatabase::Relation());

		D.push_back(Z);

		return true;
	}
	bool Erase(std::shared_ptr<Parson> P) {
		for (auto i = D.begin(); i != D.end(); i++) {
			if (P->ID == i->get()->P->ID) {
				D.erase(i);
				return true;
			}
		}

		return false;
	}


	SharedParsonData Find(std::string ID) {
		for (auto& o : D) {
			if (o->P->ID == ID) { return o; }
		}
		return nullptr;
	}
	SharedParsonData Find(SharedParson P) {
		for (auto& o : D) {
			if (o->P->ID == P->ID) { return o; }
		}
		return nullptr;
	}

	std::vector<SharedParsonData>::iterator begin() {
		return D.begin();
	}

	std::vector<SharedParsonData>::iterator end() {
		return D.end();
	}
	SharedParsonData& operator[](const std::size_t& In) {
		return D[In];
	}

protected:

	std::vector<SharedParsonData> D;
};

int main() {
	ObjectDatabase ODB;
	ObjectDatabase::SharedParson P=std::make_shared<ObjectDatabase::Parson>();

	P->Add("Hoge", "X");
	P->Add("hage", "baru");

	ODB.Push(P);

	for (auto& o : *P) {
		std::cout << o.first << ':' << o.second << std::endl;
	}
}