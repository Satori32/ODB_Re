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

	struct Data
	{
		std::shared_ptr<Parson> P;
		Relation R;

		
	};

	bool New(const std::string& ID) {
		SharedParson P = std::make_shared<Parson>();
		P->ID = ID;
		return this->Push(P);
	}

	bool Push(std::shared_ptr<Parson> P) {
		bool F = false;
		for (auto i = D.begin(); i != D.end(); i++) {
			if (i->P->ID == P->ID) {
				return false;
			}
		}

		this->P.push_back(P);

		Data DD{ P,{} };
		D.push_back(DD);

		return true;
	}
	bool Erase(std::shared_ptr<Parson> P) {
		for (auto i = D.begin(); i != D.end(); i++) {
			if (P->ID == i->P->ID) {
				D.erase(i);
				return true;
			}
		}

		return false;
	}

	std::vector<std::shared_ptr<Parson>>& getParsons() {
		return P;
	}
	std::size_t ParsonSize() {
		return P.size();
	}

	std::vector<Data>& getData() {
		return D;
	}

	std::vector<Data>::iterator begin() {
		return D.begin();
	}

	std::vector<Data>::iterator end() {
		return D.end();
	}
	Data& operator[](const std::size_t& In) {
		return D[In];
	}

protected:
	std::vector<std::shared_ptr<Parson>> P;
	std::vector<Data> D;
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